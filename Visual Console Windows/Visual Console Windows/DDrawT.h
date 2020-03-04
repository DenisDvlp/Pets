//DDrawT.h
#pragma once
#include "IDDraw.h"
#include "DSizable.h"
#include "DBiArray.h"

template<typename T>
class DDrawT
    : public IDDraw
    , public DSizable
{
public:
    void  fill(const DColor) override;
    void  drawRect(const DRect&, const DColor) override;
    void  drawText(const DRect&, const DString&, const DColor, const DAlign = DAlign::DEFAULT) override;
    void  drawText(const DRect&, const DStringList&, const DColor, const DAlign = DAlign::DEFAULT) override;
    DRect calcTextRect(const DString&) override;
    DRect calcTextRect(const DStringList&) override;
    T* raw();
    const T* raw() const;
    T* const* map();
    const T* const* map() const;
private:
    void resize(DSize&) override;
private:
    DBiArray<T> m_buffer;
};

template<typename T>
inline T* DDrawT<T>::raw()
{
    return m_buffer.raw();
}

template<typename T>
inline const T* DDrawT<T>::raw() const
{
    return m_buffer.raw();
}

template<typename T>
inline T* const* DDrawT<T>::map()
{
    return m_buffer.grid();
}

template<typename T>
inline const T* const* DDrawT<T>::map() const
{
    return m_buffer.grid();
}

template<typename T>
inline void DDrawT<T>::resize(DSize& size)
{
    m_buffer.size(size);
}
