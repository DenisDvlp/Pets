//Draw.h
#pragma once
#include "IDraw.h"
#include "BiArray.h"
#include "Sizable.h"

template<typename T>
class Draw
    : public IDraw
    , public Sizable
{
public:
    void clear(Color) override;
    void drawRect(Rect16, Color) override;
    void drawText(Rect16, const DString&, Color, Align) override;
    void drawImage(Point16, const Image&) override;
    Rect16 calcTextRect(const DString&) override;
    T* buffer();
private:
    void resize(Size&) override;
private:
    BiArray<T> m_biArray;
};

template<typename T>
T* Draw<T>::buffer()
{
    return m_biArray.raw();
}

template<typename T>
void Draw<T>::resize(Size& size)
{
    m_biArray.size(size);
}