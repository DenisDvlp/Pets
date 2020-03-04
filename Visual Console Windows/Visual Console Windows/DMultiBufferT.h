//DMultiBufferT.h
#pragma once
#include "DSizable.h"

template<typename T, byte NUMBER_OF_BUFFERS = 1>
class DMultiBufferT
    : public DSizable
{
    enum class BufferState : byte
    {
        Empty,
        Work,
        Full,
    };

    struct Buffer
    {
        T container;
        BufferState state;
    };

public:
    T* beginWrite();
    void endWrite(const T*);
    T* beginRead();
    void endRead(const T*);
    byte bufferCount() const;
private:
    T* findBufferAndChangeState(BufferState, BufferState);
    void setBufferStateByContainer(const T*, BufferState);
    void resize(DSize&) override;
private:
    Buffer m_buffers[NUMBER_OF_BUFFERS];
};

template<typename T, byte NUMBER_OF_BUFFERS>
T* DMultiBufferT<T, NUMBER_OF_BUFFERS>::beginWrite()
{
    auto result = findBufferAndChangeState(BufferState::Empty, BufferState::Work);

    if(!result)
    {
        result = findBufferAndChangeState(BufferState::Full, BufferState::Work);
    }

    return result;
}

template<typename T, byte NUMBER_OF_BUFFERS>
inline void DMultiBufferT<T, NUMBER_OF_BUFFERS>::endWrite(const T* container)
{
    setBufferStateByContainer(container, BufferState::Full);
}

template<typename T, byte NUMBER_OF_BUFFERS>
inline T* DMultiBufferT<T, NUMBER_OF_BUFFERS>::beginRead()
{
    return findBufferAndChangeState(BufferState::Full, BufferState::Work);
}

template<typename T, byte NUMBER_OF_BUFFERS>
inline void DMultiBufferT<T, NUMBER_OF_BUFFERS>::endRead(const T* container)
{
    setBufferStateByContainer(container, BufferState::Empty);
}

template<typename T, byte NUMBER_OF_BUFFERS>
inline byte DMultiBufferT<T, NUMBER_OF_BUFFERS>::bufferCount() const
{
    return NUMBER_OF_BUFFERS;
}

template<typename T, byte NUMBER_OF_BUFFERS>
auto DMultiBufferT<T, NUMBER_OF_BUFFERS>::findBufferAndChangeState(BufferState state, BufferState newState) -> T*
{
    T* result = nullptr;

    for(auto buffer : m_buffers)
    {
        if(buffer.state == state)
        {
            result = &(buffer.container);
            buffer.state = newState;
            break;
        }
    }

    return result;
}

template<typename T, byte NUMBER_OF_BUFFERS>
inline void DMultiBufferT<T, NUMBER_OF_BUFFERS>::setBufferStateByContainer(const T* container, BufferState state)
{
    if(container)
    {
        return;
    }

    for(auto buffer : m_buffers)
    {
        if(&(buffer.container) == container)
        {
            buffer.state = state;
            break;
        }
    }
}

template<typename T, byte NUMBER_OF_BUFFERS>
void DMultiBufferT<T, NUMBER_OF_BUFFERS>::resize(DSize& size)
{
    for(auto buffer : m_buffers)
    {
        buffer.container.size(size);
    }

    size = m_buffers[0].container.size();
}