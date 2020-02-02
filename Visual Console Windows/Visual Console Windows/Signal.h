//Signal.h
#pragma once
#include <vector>
#include <algorithm>
#include <cassert>
#include "Linkable.h"
#include "Function.h"
#include "DVector.h"

using Sender = void*;

template<typename... Args>
class Signal : Linkable
{
private:
    template<typename T>
    using Method = MethodMember<void, T, Args...>;
    using Func = void(*)(Args...);
    using SignalT = Signal<Args...>;
    using Callback = Function<void(Args...)>;

public:
    Signal() = default;
    Signal(const Signal&) = default;
    Signal(Signal&&) = default;
    ~Signal();
    Signal& operator=(const Signal&) = default;
    Signal& operator=(Signal&&) = default;
    template<typename T1, typename T2>
    void link(T1*, Method<T2>);
    template<typename Lambda>
    void link(Lambda);
    void link(Func);
    void link(SignalT*);
    void unlink(void*);
    void unlink();
    void operator()(Args...);
private:
    void link_helper(Callback);
    void unlink_helper(const Callback&);
    bool isLinkable(const Callback&);
private:
    DVector<Callback> m_callbacks;
};

template<typename... Args>
Signal<Args...>::~Signal()
{
    unlink();
}

template<typename... Args>
template<typename T1, typename T2>
void Signal<Args...>::link(T1* object, Method<T2> method)
{
    if(object && method)
    {
        static_assert(std::is_base_of_v<Linkable, T1>, "The object must be inherited from 'Linkable'");
        link_helper(Callback(object, method));
    }
}

template<typename... Args>
template<typename Lambda>
void Signal<Args...>::link(Lambda lambda)
{
    link_helper(Callback(std::move(lambda)));
}

template<typename... Args>
void Signal<Args...>::link(Func func)
{
    if(func)
    {
        link_helper(Callback(func));
    }
}

template<typename... Args>
void Signal<Args...>::link(SignalT* signal)
{
    link(signal, &Signal::operator());
}

template<typename... Args>
void Signal<Args...>::unlink(void* object)
{
    if(object)
    {
        m_callbacks.remove([this, object] (const auto& callback)
            {
                const auto isFound = callback.m_object == object;
                if(isFound)
                {
                    unlink_helper(callback);
                }
                return isFound;
            });
    }
}

template<typename... Args>
void Signal<Args...>::unlink()
{
    for(const auto& callback : m_callbacks)
    {
        unlink_helper(callback);
    }
    m_callbacks.clear();
}

template<typename... Args>
void Signal<Args...>::operator()(Args... args)
{
    for(auto& callback : m_callbacks)
    {
        callback(std::move(args)...);
    }
}

template<typename... Args>
void Signal<Args...>::link_helper(Callback callback)
{
    auto isNew = m_callbacks.find(callback) == m_callbacks.end();
    if(isNew)
    {
        m_callbacks.push(std::move(callback));
        if(isLinkable(callback))
        {
            static_cast<Linkable*>(callback.m_object)->link(this);
        }
    }
}

template<typename... Args>
void Signal<Args...>::unlink_helper(const Callback& callback)
{
    if(isLinkable(callback))
    {
        static_cast<Linkable*>(callback.m_object)->unlink(this);
    }
}

template<typename... Args>
bool Signal<Args...>::isLinkable(const Callback& callback)
{
    return
        callback.m_callType >= Callback::CallType::CLASS_METHOD_1 &&
        callback.m_callType <= Callback::CallType::CLASS_METHOD_4;
}
