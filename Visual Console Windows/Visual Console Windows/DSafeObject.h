#pragma once
#include <mutex>

template<typename T>
class DSafeObject
{
private:

    class DLockedObject
    {
        friend class DSafeObject;
    public:
        ~DLockedObject();
        T* operator->();
        T& operator*();
        const T& operator*() const;
    private:
        DLockedObject(T*, std::recursive_mutex&);
    private:
        std::recursive_mutex& m_mutex;
        T* m_object;
    };

public:
    template<typename... Args>
    DSafeObject(Args... args);
    DLockedObject operator->();
    DLockedObject getLocked();
    T& operator*();
    const T& operator*() const;
private:
    std::recursive_mutex m_mutex;
    T m_object;
};

template<typename T>
DSafeObject<T>::DLockedObject::DLockedObject(T* object, std::recursive_mutex& mutex)
    : m_mutex(mutex)
    , m_object(object)
{
    m_mutex.lock();
}

template<typename T>
DSafeObject<T>::DLockedObject::~DLockedObject()
{
    m_mutex.unlock();
}

template<typename T>
inline T* DSafeObject<T>::DLockedObject::operator->()
{
    return m_object;
}

template<typename T>
inline T& DSafeObject<T>::DLockedObject::operator*()
{
    return *m_object;
}

template<typename T>
inline const T& DSafeObject<T>::DLockedObject::operator*() const
{
    return *m_object;
}

template<typename T>
template<typename... Args>
DSafeObject<T>::DSafeObject(Args... args)
    : m_object(args...)
{}

template<typename T>
inline auto DSafeObject<T>::operator->() -> DLockedObject
{
    return getLocked();
}

template<typename T>
inline auto DSafeObject<T>::getLocked() -> DLockedObject
{
    return DLockedObject(&m_object, m_mutex);
}

template<typename T>
inline T& DSafeObject<T>::operator*()
{
    return getLocked();
}

template<typename T>
inline const T& DSafeObject<T>::operator*() const
{
    return getLocked();
}
