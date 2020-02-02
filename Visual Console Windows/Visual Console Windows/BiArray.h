//BiArray.h
#pragma once
#include "DSizable.h"
#include <vector>

template<typename T>
class BiArray
    : public DSizable
{
public:
    T* raw();
    const T* raw() const;
    T* const* grid();
    const T* const* grid() const;
    T* const operator[](int);
private:
    void resize(Size&) override;
protected:
    std::vector<T>  m_raw;
    std::vector<T*> m_grid;
};

template<typename T>
void BiArray<T>::resize(Size& newSize)
{
    if(size() != newSize)
    {
        auto height = newSize.height();
        auto width = newSize.width();
        auto square = newSize.square();

        if(size().square() != square)
        {
            m_raw.resize(square);
        }

        m_grid.resize(height);

        for(decltype(height) i = 0; i < height; ++i)
        {
            m_grid[i] = width > 0 ? &m_raw[i * width] : nullptr;
        }
    }
}

template<typename T>
inline T* const BiArray<T>::operator[](int index)
{
    return m_grid[index];
}

template<typename T>
inline T* BiArray<T>::raw()
{
    return m_raw.data();
}

template<typename T>
inline const T* BiArray<T>::raw() const
{
    return m_raw.data();
}

template<typename T>
inline T* const* BiArray<T>::grid()
{
    return m_grid.data();
}

template<typename T>
inline const T* const* BiArray<T>::grid() const
{
    return static_cast<const T* const*>(m_grid.data());
}