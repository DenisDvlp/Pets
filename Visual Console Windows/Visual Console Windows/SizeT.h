//SizeT.h
#pragma once

template<typename T>
class SizeT
{
public:
    SizeT() = default;
    SizeT(T, T);

    void set(T, T);

    T    width() const;
    void width(T);
    T    height() const;
    void height(T);

    bool isZero() const;
    bool isEmpty() const;
    void inc(T, T);

    T square() const;

    bool operator==(const SizeT&) const;
    bool operator!=(const SizeT&) const;

private:
    T m_width = 0;
    T m_height = 0;
};

////////////////impementation////////////////

template<typename T>
SizeT<T>::SizeT(T w, T h)
{
    set(w, h);
}

template<typename T>
void SizeT<T>::set(T w, T h)
{
    width(w);
    height(h);
}

template<typename T>
inline T SizeT<T>::width() const
{
    return m_width;
}

template<typename T>
void SizeT<T>::width(T width)
{
    m_width = width < 0 ? 0 : width;
}

template<typename T>
inline T SizeT<T>::height() const
{
    return m_height;
}

template<typename T>
void SizeT<T>::height(T height)
{
    m_height = height < 0 ? 0 : height;
}

template<typename T>
bool SizeT<T>::isZero() const
{
    return !(m_width | m_height);
}

template<typename T>
bool SizeT<T>::isEmpty() const
{
    return !m_width || !m_height;
}

template<typename T>
void SizeT<T>::inc(T dwidth, T dheight)
{
    set(m_width + dwidth, m_height + dheight);
}

template<typename T>
T SizeT<T>::square() const
{
    return m_width * m_height;
}

template<typename T>
bool SizeT<T>::operator==(const SizeT& size) const
{
    return m_width == size.m_width && m_height == size.m_height;
}

template<typename T>
bool SizeT<T>::operator!=(const SizeT& size) const
{
    return !operator==(size);
}