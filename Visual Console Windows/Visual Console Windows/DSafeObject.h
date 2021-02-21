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
    DSafeObject(const DSafeObject&);
    DSafeObject(DSafeObject&&);
    DSafeObject& operator=(const DSafeObject&);
    DSafeObject& operator=(DSafeObject&&);
    DLockedObject operator->();
    DLockedObject getLocked();
    void moveTo(T&);

    friend void swap(DSafeObject& object1, DSafeObject& object2)
    {
        std::scoped_lock lock(object1.m_mutex, object2.m_mutex);
        std::swap(object1.m_object, object2.m_object);
    }

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
DSafeObject<T>::DSafeObject(const DSafeObject& object)
{
    void(operator=(object));
}

template<typename T>
DSafeObject<T>::DSafeObject(DSafeObject&& object)
{
    void(operator=(std::move(object)));
}

template<typename T>
DSafeObject<T>& DSafeObject<T>::operator=(const DSafeObject& object)
{
    std::scoped_lock lock(m_mutex, object.m_mutex);
    m_object = object;
    return *this;
}

template<typename T>
DSafeObject<T>& DSafeObject<T>::operator=(DSafeObject&& object)
{
    std::scoped_lock lock(m_mutex, object.m_mutex);
    m_object = std::move(object);
    return *this;
}

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
inline void DSafeObject<T>::moveTo(T& object)
{
  std::unique_lock<std::recursive_mutex> guard(m_mutex);
  object = std::move(m_object);
}
