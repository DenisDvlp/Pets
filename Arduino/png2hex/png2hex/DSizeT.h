//DSizeT.h
#pragma once

template<typename T>
class DSizeT
{
public:
    DSizeT() = default;
    DSizeT(const T, const T);

    void set(const T, const T);

    T    width() const;
    void width(const T);
    T    height() const;
    void height(const T);

    bool isZero() const;
    bool isEmpty() const;

    void inc(const T, const T);
    void incWidth(const T);
    void incHeight(const T);

    T square() const;

    DSizeT  operator* (const double);
    DSizeT& operator*=(const double);
    DSizeT  operator/ (const double);
    DSizeT& operator/=(const double);
    bool    operator==(const DSizeT&) const;
    bool    operator!=(const DSizeT&) const;

private:
    T m_width = 0;
    T m_height = 0;
};

////////////////impementation////////////////

template<typename T>
DSizeT<T>::DSizeT(const T w, const T h)
    : m_width(w < 0 ? 0 : w)
    , m_height(h < 0 ? 0 : h)
{}

template<typename T>
void DSizeT<T>::set(const T w, const T h)
{
    width(w);
    height(h);
}

template<typename T>
inline T DSizeT<T>::width() const
{
    return m_width;
}

template<typename T>
void DSizeT<T>::width(const T width)
{
    m_width = width < 0 ? 0 : width;
}

template<typename T>
inline T DSizeT<T>::height() const
{
    return m_height;
}

template<typename T>
void DSizeT<T>::height(const T height)
{
    m_height = height < 0 ? 0 : height;
}

template<typename T>
bool DSizeT<T>::isZero() const
{
    return !(m_width | m_height);
}

template<typename T>
bool DSizeT<T>::isEmpty() const
{
    return !m_width || !m_height;
}

template<typename T>
void DSizeT<T>::inc(const T dwidth, const T dheight)
{
    set(m_width + dwidth, m_height + dheight);
}

template<typename T>
void DSizeT<T>::incWidth(const T dwidth)
{
    width(m_width + dwidth);
}

template<typename T>
void DSizeT<T>::incHeight(const T dheight)
{
    height(m_height + dheight);
}

template<typename T>
T DSizeT<T>::square() const
{
    return m_width * m_height;
}

template<typename T>
DSizeT<T> DSizeT<T>::operator*(const double value)
{
    return DSizeT<T>(*this) *= value;
}

template<typename T>
DSizeT<T>& DSizeT<T>::operator*=(const double value)
{
    width(m_width * value);
    height(m_height * value);
    return *this;
}

template<typename T>
DSizeT<T> DSizeT<T>::operator/(const double value)
{
    return DSizeT<T>(*this) /= value;
}

template<typename T>
DSizeT<T>& DSizeT<T>::operator/=(const double value)
{
    width(m_width / value);
    height(m_height / value);
    return *this;
}

template<typename T>
bool DSizeT<T>::operator==(const DSizeT& size) const
{
    return m_width == size.m_width && m_height == size.m_height;
}

template<typename T>
bool DSizeT<T>::operator!=(const DSizeT& size) const
{
    return !operator==(size);
}