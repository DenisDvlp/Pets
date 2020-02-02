//DrawBuffer.h
#pragma once
#include "IDrawBufferNative.h"
#include "Sizable.h"
#include "Draw.h"
#include <mutex>

template<typename T>
class DrawBuffer
    : public IDrawBufferNative<T>
    , public Sizable
{
public:
    bool swap()        override;
    IDraw* beginDraw() override;
    void endDraw()     override;
    T* buffer()        override;
private:
    void resize(Size&) override;
private:
    static const char NUMBER_OF_DRAWS = 2;
    bool m_isFirst = true;
    bool m_isFrameReady = false;
    std::mutex m_mutex;
    Draw<T> m_draw[NUMBER_OF_DRAWS];
};

template<typename T>
bool DrawBuffer<T>::swap()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_isFrameReady)
    {
        m_isFirst = !m_isFirst;
        m_isFrameReady = false;
        return true;
    }
    return false;
}

template<typename T>
IDraw* DrawBuffer<T>::beginDraw()
{
    m_mutex.lock();
    return m_draw + (m_isFirst ? 0 : 1);
}

template<typename T>
void DrawBuffer<T>::endDraw()
{
    m_mutex.unlock();
    m_isFrameReady = true;
}

template<typename T>
T* DrawBuffer<T>::buffer()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    return m_draw[m_isFirst ? 1 : 0].buffer();
}

template<typename T>
void DrawBuffer<T>::resize(Size& size)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_draw[0].size(size);
    m_draw[1].size(size);
    size = m_draw[0].size();
}