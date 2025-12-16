#pragma once
#include <string.h>

template<typename Return, typename... Args>
class Function;

template<typename Return, typename T, typename... Args>
using MethodMember = Return(T::*)(Args...);

template<typename Return, typename... Args>
using GlobalFunction = Return(*)(Args...);

class FakeForward;
class FakeBase {};
class FakeBase2 {};
class FakeSingle : FakeBase {};
class FakeMultiple : FakeBase, FakeBase2 {};
class FakeVirtual : FakeBase { virtual ~FakeVirtual() {} };

template<typename Return, typename... Args>
using FakeMethodSingleHelper = MethodMember<Return, FakeSingle, Args...>;
template<typename Return, typename... Args>
using FakeMethodMultipleHelper = MethodMember<Return, FakeMultiple, Args...>;
template<typename Return, typename... Args>
using FakeMethodVirtualHelper = MethodMember<Return, FakeVirtual, Args...>;
template<typename Return, typename... Args>
using FakeMethodForwardHelper = MethodMember<Return, FakeForward, Args...>;

template<int x, typename Return, typename... Args>struct CastMethodsHelper;
template<typename Return, typename... Args>struct CastMethodsHelper<0, Return, Args...> { using type = FakeMethodSingleHelper<Return, Args...>; };
template<typename Return, typename... Args>struct CastMethodsHelper<1, Return, Args...> { using type = FakeMethodMultipleHelper<Return, Args...>; };
template<typename Return, typename... Args>struct CastMethodsHelper<2, Return, Args...> { using type = FakeMethodVirtualHelper<Return, Args...>; };
template<typename Return, typename... Args>struct CastMethodsHelper<3, Return, Args...> { using type = FakeMethodForwardHelper<Return, Args...>; };

template<typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
};

template <class T, T x>
struct integral_constant {
  static constexpr T value = x;

  using valueTpe = T;
  using type = integral_constant;

  constexpr operator valueTpe() const noexcept {
    return value;
  }

  constexpr valueTpe operator()() const noexcept {
    return value;
  }
};

template <bool x>
using bool_constant = integral_constant<bool, x>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// STRUCT TEMPLATE remove_reference
template <class T>
struct remove_reference {
  using type = T;
  using _Const_thru_refTpe = const T;
};

template <class T>
struct remove_reference<T&> {
  using type = T;
  using _Const_thru_refTpe = const T&;
};

template <class T>
struct remove_reference<T&&> {
  using type = T;
  using _Const_thru_refTpe = const T&&;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

// STRUCT TEMPLATE is_lvalue_reference
template <class>
constexpr bool is_lvalue_reference_v = false; // determine whether type argument is an lvalue reference

template <class T>
constexpr bool is_lvalue_reference_v<T&> = true;

// FUNCTION TEMPLATE forward
template <class T>
constexpr T&& forward(
  remove_reference_t<T>& Arg) noexcept { // forward an lvalue as either an lvalue or an rvalue
  return static_cast<T&&>(Arg);
}

template <class T>
constexpr T&& forward(remove_reference_t<T>&& Arg) noexcept { // forward an rvalue as an rvalue
  static_assert(!is_lvalue_reference_v<T>, "bad forward call");
  return static_cast<T&&>(Arg);
}

// FUNCTION TEMPLATE move
template <class T>
constexpr remove_reference_t<T>&& move(T&& Arg) noexcept { // forward Arg as movable
  return static_cast<remove_reference_t<T>&&>(Arg);
}

template<typename Return, typename... Args>
class Function<Return(Args...)>
{
private:

    template<typename T>
    using Method = MethodMember<Return, T, Args...>;
    using GlobalFunction = ::GlobalFunction<Return, Args...>;

    using LambdaFunction = ::GlobalFunction<Return, void*, Args...>;
    using LambdaCreate = ::GlobalFunction<void*, const void*>;
    using LambdaDestroy = ::GlobalFunction<void, void*>;

    using FakeMethodSingle = FakeMethodSingleHelper<Return, Args...>;
    using FakeMethodMultiple = FakeMethodMultipleHelper<Return, Args...>;
    using FakeMethodVirtual = FakeMethodVirtualHelper<Return, Args...>;
    using FakeMethodForward = FakeMethodForwardHelper<Return, Args...>;

    template<int x>
    using CastMethods = CastMethodsHelper<x, Return, Args...>;

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

    using MethodPair = pair<MethodUnion, CallType>;

    template<typename T, int x = 0>
    static MethodPair method_cast(T method, false_type)
    {
        static_assert(x < 4, "Appropriate class method cast not found");
        using Method = typename CastMethods<x>::type;
        return method_cast<T, x + 1>(method, bool_constant<sizeof(T) == sizeof(Method)>());
    }

    template<typename T, int x>
    static MethodPair method_cast(T method, true_type)
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
        return pair<MethodUnion, CallType>{methodUnion, static_cast<CallType>(x - 1)};
    }

    template<typename T>
    static Return lambda_call(void* object, Args... args)
    {
        return (*reinterpret_cast<T*>(object))(forward<Args>(args)...);
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

    Return operator()(Args... args) const;

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
    assign(move(lambda));
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
    auto methodPair = method_cast(method, false_type());
    m_method = methodPair.first;
    m_callType = methodPair.second;
}

template<typename Return, typename... Args>
template<typename Lambda>
void Function<Return(Args...)>::assign(Lambda lambda)
{
    clear();
    m_object = reinterpret_cast<void*>(new Lambda(move(lambda)));
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
    assign(move(lambda));
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
    assign(move(function));
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
Return Function<Return(Args...)>::operator()(Args... args) const
{
    if(m_object)
    {
        switch(m_callType)
        {
            case CallType::CLASS_METHOD_1:
                return (reinterpret_cast<FakeSingle*>(m_object)->*m_method.method1)(forward<Args>(args)...);
                break;
            case CallType::CLASS_METHOD_2:
                return (reinterpret_cast<FakeMultiple*>(m_object)->*m_method.method2)(forward<Args>(args)...);
                break;
            case CallType::CLASS_METHOD_3:
                return (reinterpret_cast<FakeVirtual*>(m_object)->*m_method.method3)(forward<Args>(args)...);
                break;
            case CallType::CLASS_METHOD_4:
                return (reinterpret_cast<FakeForward*>(m_object)->*m_method.method4)(forward<Args>(args)...);
                break;
            case CallType::GLOBAL_FUNCTION:
                return reinterpret_cast<GlobalFunction>(m_object)(forward<Args>(args)...);
                break;
            case CallType::LAMBDA_FUNCTION:
                return (m_method.lambdaCall)(m_object, forward<Args>(args)...);
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