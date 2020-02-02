#pragma once

template<typename Return, typename... Args>
class Function;

template<typename Return, typename T, typename... Args>
using MethodMember = Return(T::*)(Args...);

template<typename Return, typename... Args>
using GlobalFunction = Return(*)(Args...);

template<typename Return, typename... Args>
class Function<Return(Args...)>
{
private:

    template<typename... Args> friend class Signal;

    template<typename T>
    using Method = MethodMember<Return, T, Args...>;
    using GlobalFunction = ::GlobalFunction<Return, Args...>;

    class FakeForward;
    class FakeBase {};
    class FakeBase2 {};
    class FakeSingle : FakeBase {};
    class FakeMultiple : FakeBase, FakeBase2 {};
    class FakeVirtual : FakeBase { virtual ~FakeVirtual(){} };

    using LambdaFunction = ::GlobalFunction<Return, void*, Args...>;
    using LambdaCreate = ::GlobalFunction<void*, const void*>;
    using LambdaDestroy = ::GlobalFunction<void, void*>;

    using FakeMethodSingle = Method<FakeSingle>;
    using FakeMethodMultiple = Method<FakeMultiple>;
    using FakeMethodVirtual = Method<FakeVirtual>;
    using FakeMethodForward = Method<FakeForward>;

    template<int>struct CastMethods;
    template<>struct CastMethods<0> { using type = FakeMethodSingle; };
    template<>struct CastMethods<1> { using type = FakeMethodMultiple; };
    template<>struct CastMethods<2> { using type = FakeMethodVirtual; };
    template<>struct CastMethods<3> { using type = FakeMethodForward; };

    union CalculateMethodMaxSize
    {
        FakeMethodSingle method1;
        FakeMethodMultiple method2;
        FakeMethodVirtual method3;
        FakeMethodForward method4;
        struct
        {
            LambdaFunction lambdaCall;
            LambdaCreate lambdaCreate;
            LambdaDestroy lambdaDestroy;
        };
    };

    static constexpr int MAX_UNION_SIZE = sizeof(CalculateMethodMaxSize);

    union MethodUnion
    {
        char raw[MAX_UNION_SIZE] = {0};
        FakeMethodSingle method1;
        FakeMethodMultiple method2;
        FakeMethodVirtual method3;
        FakeMethodForward method4;
        struct
        {
            LambdaFunction lambdaCall;
            LambdaCreate lambdaCreate;
            LambdaDestroy lambdaDestroy;
        };
    };

    enum class CallType : char
    {
        NONE = -1,
        CLASS_METHOD_1 = 0,
        CLASS_METHOD_2,
        CLASS_METHOD_3,
        CLASS_METHOD_4,
        GLOBAL_FUNCTION,
        LAMBDA_FUNCTION,
    };

    using MethodPair = std::pair<MethodUnion, CallType>;

    template<typename T, int x = 0>
    static MethodPair method_cast(T method, std::false_type)
    {
        static_assert(x < 4, "Appropriate class method cast not found");
        using Method = typename CastMethods<x>::type;
        return method_cast<T, x + 1>(method, std::bool_constant<sizeof(T) == sizeof(Method)>());
    }

    template<typename T, int x>
    static MethodPair method_cast(T method, std::true_type)
    {
        using Method = typename CastMethods<x - 1>::type;
        union
        {
            char raw[MAX_UNION_SIZE] = {0};
            Method method;
        } ptr;
        ptr.method = reinterpret_cast<Method>(method);
        MethodUnion methodUnion;
        memcpy(methodUnion.raw, ptr.raw, MAX_UNION_SIZE);
        return std::make_pair(methodUnion, static_cast<CallType>(x - 1));
    }

    template<typename T>
    static Return lambda_call(void* object, Args... args)
    {
        return (*reinterpret_cast<T*>(object))(args...);
    }

    template<typename T>
    static void* lambda_create(const void* object)
    {
        return reinterpret_cast<void*>(new T(*reinterpret_cast<const T*>(object)));
    }

    template<typename T>
    static void lambda_destroy(void* object)
    {
        delete reinterpret_cast<T*>(object);
    }

public:

    Function() = default;
    Function(const Function& function);
    Function(Function&& function);
    template<typename T1, typename T2>
    Function(T1 object, T2 method);
    template<typename Lambda>
    Function(Lambda lambda);
    Function(GlobalFunction func);

    ~Function();

    template<typename T1, typename T2>
    void assign(T1 object, T2 method);
    template<typename Lambda>
    void assign(Lambda lambda);
    void assign(GlobalFunction globalFunction);
    void assign(const Function& function);
    void assign(Function&& function);

    void clear();
    bool empty() const;

    template<typename Lambda>
    void operator=(Lambda lambda);
    void operator=(GlobalFunction globalFunction);
    void operator=(const Function& function);
    void operator=(Function&& function);

    bool operator==(const Function& function) const;
    bool operator!=(const Function& function) const;

    Return operator()(Args... args);

private:
    void reset();

private:

    void* m_object = nullptr;
    MethodUnion m_method;
    CallType m_callType = CallType::NONE;
};

template<typename Return, typename... Args>
Function<Return(Args...)>::Function(const Function& function)
    : m_object(function.m_object && CallType::LAMBDA_FUNCTION == function.m_callType ?
        function.m_method.lambdaCreate(function.m_object) : function.m_object)
    , m_method(function.m_method)
    , m_callType(function.m_callType)
{}

template<typename Return, typename... Args>
Function<Return(Args...)>::Function(Function&& function)
    : m_object(function.m_object)
    , m_method(function.m_method)
    , m_callType(function.m_callType)
{
    function.reset();
}

template<typename Return, typename... Args>
template<typename T1, typename T2>
Function<Return(Args...)>::Function(T1 object, T2 method)
{
    assign(object, method);
}

template<typename Return, typename... Args>
template<typename Lambda>
Function<Return(Args...)>::Function(Lambda lambda)
{
    assign(std::move(lambda));
}

template<typename Return, typename... Args>
Function<Return(Args...)>::Function(GlobalFunction func)
{
    assign(func);
}

template<typename Return, typename... Args>
Function<Return(Args...)>::~Function()
{
    clear();
}

template<typename Return, typename... Args>
template<typename T1, typename T2>
void Function<Return(Args...)>::assign(T1 object, T2 method)
{
    clear();
    m_object = object;
    auto methodPair = method_cast(method, std::false_type());
    m_method = methodPair.first;
    m_callType = methodPair.second;
}

template<typename Return, typename... Args>
template<typename Lambda>
void Function<Return(Args...)>::assign(Lambda lambda)
{
    clear();
    m_object = reinterpret_cast<void*>(new Lambda(std::move(lambda)));
    m_method.lambdaCall = lambda_call<Lambda>;
    m_method.lambdaCreate = lambda_create<Lambda>;
    m_method.lambdaDestroy = lambda_destroy<Lambda>;
    m_callType = CallType::LAMBDA_FUNCTION;
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::assign(GlobalFunction globalFunction)
{
    clear();
    m_object = globalFunction;
    m_callType = CallType::GLOBAL_FUNCTION;
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::assign(const Function& function)
{
    if(&function != this)
    {
        clear();
        m_object = function.m_object && CallType::LAMBDA_FUNCTION == function.m_callType ?
            function.m_method.lambdaCreate(function.m_object) : function.m_object;
        m_method = function.m_method;
        m_callType = function.m_callType;
    }
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::assign(Function&& function)
{
    if(&function != this)
    {
        clear();
        if(function.m_object)
        {
            m_object = function.m_object;
            m_method = function.m_method;
            m_callType = function.m_callType;
            function.reset();
        }
    }
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::clear()
{
    if(m_object && CallType::LAMBDA_FUNCTION == m_callType)
    {
        m_method.lambdaDestroy(m_object);
    }
    reset();
}

template<typename Return, typename... Args>
bool Function<Return(Args...)>::empty() const
{
    return !m_object;
}

template<typename Return, typename... Args>
template<typename Lambda>
void Function<Return(Args...)>::operator=(Lambda lambda)
{
    assign(std::move(lambda));
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::operator=(GlobalFunction globalFunction)
{
    assign(globalFunction);
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::operator=(const Function& function)
{
    assign(function);
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::operator=(Function&& function)
{
    assign(std::move(function));
}

template<typename Return, typename... Args>
bool Function<Return(Args...)>::operator==(const Function& function) const
{
    return m_object == function.m_object &&
        (!m_object || CallType::GLOBAL_FUNCTION == m_callType || !memcmp(m_method.raw, function.m_method.raw, MAX_UNION_SIZE)) ||
        CallType::LAMBDA_FUNCTION == m_callType && m_method.lambdaCreate == function.m_method.lambdaCreate;
}

template<typename Return, typename... Args>
bool Function<Return(Args...)>::operator!=(const Function& function) const
{
    return !operator==(function);
}

template<typename Return, typename... Args>
Return Function<Return(Args...)>::operator()(Args... args)
{
    if(m_object)
    {
        switch(m_callType)
        {
            case CallType::CLASS_METHOD_1:
                return (reinterpret_cast<FakeSingle*>(m_object)->*m_method.method1)(std::move(args)...);
                break;
            case CallType::CLASS_METHOD_2:
                return (reinterpret_cast<FakeMultiple*>(m_object)->*m_method.method2)(std::move(args)...);
                break;
            case CallType::CLASS_METHOD_3:
                return (reinterpret_cast<FakeVirtual*>(m_object)->*m_method.method3)(std::move(args)...);
                break;
            case CallType::CLASS_METHOD_4:
                return (reinterpret_cast<FakeForward*>(m_object)->*m_method.method4)(std::move(args)...);
                break;
            case CallType::GLOBAL_FUNCTION:
                return reinterpret_cast<GlobalFunction>(m_object)(std::move(args)...);
                break;
            case CallType::LAMBDA_FUNCTION:
                return (m_method.lambdaCall)(m_object, std::move(args)...);
                break;
        }
    }
    return Return();
}

template<typename Return, typename... Args>
void Function<Return(Args...)>::reset()
{
    if(m_object)
    {
        m_object = nullptr;
        m_method = MethodUnion();
        m_callType = CallType::NONE;
    }
}