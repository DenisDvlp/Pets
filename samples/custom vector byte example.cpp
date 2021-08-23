//=============================================================================
// Project       Visteon Infotainment HeadUnit
// (c) copyright 2015
// Company       Visteon Corporation
//               All rights reserved
// Secrecy Level STRICTLY CONFIDENTAL
//=============================================================================
/// @file        ByteBuffer.hpp
/// @ingroup     jci_ihu
/// @brief       Definition of an Array of Bytes

#ifndef INFRASTRUCTURE_BALI_BYTE_BUFFER_HPP
#define INFRASTRUCTURE_BALI_BYTE_BUFFER_HPP

#include <cstring>
#include "Infrastructure/Atoms/inc/BasicTypes.h"
#include "Infrastructure/Atoms/inc/StdMacros.h"
#include "Infrastructure/Bali/inc/String/ToString.hpp"
#include "Infrastructure/Debug/inc/Debug.hpp"

namespace JCI
{

/**
 *  @brief  Class for byte arrays.
 *
 *  ByteBuffers can be resized, while keeping their content.
 *  To make resizing more efficient, the ByteBuffer will allocate memory in blocks of a fixed size internally.
 */
class ByteBuffer
{
public:
    /**
     *  @brief  Constructor
     *  @param  size The size of the buffer.
     */
    ByteBuffer(U32 size = 0);

    /**
     *  @brief  Copy Constructor
     *  @param  other The buffer to copy.
     */
    ByteBuffer(const ByteBuffer& other);

    /**
     *  @brief  Destructor
     */
    virtual ~ByteBuffer();

    /**
     *  @brief  Get the size of the buffer.
     */
    U32 size() const;

    /**
     *  @brief  Resize the buffer.
     *  @param  size The new size for the buffer.
     *          The buffer will keep its content. (Up to the new size, if the size gets smaller.)
     */
    void resize(U32 size);

    /**
     *  @brief  Resize the buffer.
     *  @deprecated, use resize() instead.
     */
    void setSize(U32 size);

    /**
     *  @brief  Reserve space in the buffer.
     *  @param  size The space to reserve in the buffer. This must be greater than the current buffer size.
     */
    void reserve(U32 size);

    /**
     * @brief adds bytes to the buffer
     * @param numBytes number of bytes to add
     * @param addBytesAtBeginning if true the bytes will be added at the beginning
     */
    void addBytes(U32 numBytes, bool addBytesAtBeginning = false);

    /**
     * @brief removes bytes from the buffer
     * @param numBytes number of bytes to remove
     * @param removeBytesAtBeginning if true the bytes will be removed at the beginning
     */
    void removeBytes(U32 numBytes, bool removeBytesAtBeginning = false);

    /**
     *  @brief  Get pointer to the raw buffer.
     *  @return pointer to raw buffer. The pointer will change if the buffer is resized.
     */
    U8* data();

    /**
     *  @brief  Get const pointer to the raw buffer.
     *  @return const pointer to raw buffer. The pointer will change if the buffer is resized.
     */
    const U8* data() const;

    /**
     *  @brief  Get pointer to the raw buffer with an offset
     *  @param  offset Offset into the buffer.
     *  @return pointer to raw buffer. The pointer will change if the buffer is resized.
     */
    U8* data(U32 offset);

    /**
     *  @brief  Get const pointer to the raw buffer with an offset
     *  @param  offset Offset into the buffer.
     *  @return const pointer to raw buffer. The pointer will change if the buffer is resized.
     */
    const U8* data(U32 offset) const;

    /**
     *  @brief  Index operator
     */
    U8 operator[](U32 index) const;

    /**
     *  @brief  Function operator
     */
    U8* operator()(U32 index);

    /**
     *  @brief  Const function operator
     */
    const U8 * operator()(U32 index) const;

    /**
     *  @brief  Assignment operator
     */
    ByteBuffer& operator=(const ByteBuffer& rhs);

    /**
     *  @brief  Equal operator
     */
    bool operator==(const ByteBuffer& other) const;

    /**
     *  @brief  Not Equal operator
     */
    bool operator!=(const ByteBuffer& other) const;

private:
    U8* alloc(U32 size);

private:
    U8* mData;     // buffer pointer
    U32 mCapacity; // size of bytes allocated in buffer
    U32 mSize;     // bytes used in buffer
};

//=============================================================================
// inline class implementation
//=============================================================================

//-----------------------------------------------------------------------------
inline ByteBuffer::ByteBuffer(U32 size)
//-----------------------------------------------------------------------------
: mData(0)
, mCapacity(0)
, mSize(size)
{
    if (mSize > 0)
    {
        mData = this->alloc(mSize);
    }
}

//-----------------------------------------------------------------------------
inline ByteBuffer::ByteBuffer(const ByteBuffer& other)
//-----------------------------------------------------------------------------
: mData(0)
, mCapacity(0)
, mSize(other.mSize)
{
    if (mSize > 0)
    {
        mData = this->alloc(mSize);
        std::memcpy(mData, other.mData, mSize);
    }
}

//-----------------------------------------------------------------------------
inline ByteBuffer::~ByteBuffer()
//-----------------------------------------------------------------------------
{
    delete[] mData;
}

//-----------------------------------------------------------------------------
inline U32 ByteBuffer::size() const
//-----------------------------------------------------------------------------
{
    return mSize;
}

//-----------------------------------------------------------------------------
inline U8* ByteBuffer::alloc(U32 size)
//-----------------------------------------------------------------------------
{
    const U32 MIN_RESERVE = 128; // minimum allocation size
    const U32 MAX_RESERVE = 8 * 1024 * 1024; // if capacity is above this, we only increment by RESERVE_INC.
    const U32 RESERVE_INC = 128;

    // allocate at least size bytes, but try to allocated more (based on the last allocation.)
    // the actually allocated size is stored in mCapacity.

    U32 tmp = mCapacity;
    if (size > tmp)
    {
        // we have to increase
        if (tmp > MAX_RESERVE)
        {
            tmp = tmp + RESERVE_INC;
        }
        else
        {
            tmp = tmp * 2; // double the capacity.
        }
    }
    else
    {
        // we can decrease
        tmp = tmp / 2; // keep half the capacity.
    }

    if (tmp < MIN_RESERVE)
    {
        tmp = MIN_RESERVE;
    }

    mCapacity = (size < tmp) ? tmp : size;
    U8 *data = new (std::nothrow) U8[mCapacity];
    if (!data)
    {
        // try again with minimum required size
        mCapacity = size;
        data = new (std::nothrow) U8[mCapacity];
        CIA_ASSERT(data != 0, "Allocation failed!");
    }

    return data;
}

//-----------------------------------------------------------------------------
inline void ByteBuffer::reserve(U32 size)
//-----------------------------------------------------------------------------
{
    if ((size > mSize) && (size != mCapacity))
    {
        U8 *old = mData;
        mCapacity = size;
        mData = new (std::nothrow) U8[mCapacity];
        CIA_ASSERT(mData != 0, "Allocation failed!");

        if (old)
        {
            std::memcpy(mData, old, mSize);
            delete[] old;
        }
    }
    mSize = size;
}

//-----------------------------------------------------------------------------
inline void ByteBuffer::resize(U32 size)
//-----------------------------------------------------------------------------
{
    if ((size > mCapacity) || (size < (mCapacity / 4)))
    {
        U8 *old = mData;
        mData = this->alloc(size);

        if (old)
        {
            std::memcpy(mData, old, CIA_MIN(size, mSize));
            delete[] old;
        }
    }
    mSize = size;
}

//-----------------------------------------------------------------------------
inline void ByteBuffer::addBytes(U32 numBytes, bool addBytesAtBeginning)
//-----------------------------------------------------------------------------
{
    U32 size = mSize + numBytes;
    if (size > mCapacity)
    {
        U8 *old = mData;
        mData = this->alloc(size);

        if (old)
        {
            U8* dst = mData;
            if (addBytesAtBeginning)
            {
                dst += numBytes;
            }
            std::memcpy(dst, old, mSize);
            delete[] old;
        }
    }
    else if (addBytesAtBeginning)
    {
        std::memmove(mData + numBytes, mData, mSize);
    }
    mSize = size;
}

//-----------------------------------------------------------------------------
inline void ByteBuffer::removeBytes(U32 numBytes, bool removeBytesAtBeginning)
//-----------------------------------------------------------------------------
{
    CIA_ASSERT(mSize >= numBytes, "Out of bounds access!");

    U32 size = mSize - numBytes;
    if (size < (mCapacity / 4))
    {
        U8 *old = mData;
        mData = this->alloc(size);

        if (old)
        {
            U8* src = old;
            if (removeBytesAtBeginning)
            {
                src += numBytes;
            }
            std::memcpy(mData, src, size);
            delete[] old;
        }
    }
    else if (removeBytesAtBeginning)
    {
        std::memmove(mData, mData + numBytes, size);
    }
    mSize = size;
}

//-----------------------------------------------------------------------------
inline void ByteBuffer::setSize(U32 size)
//-----------------------------------------------------------------------------
{
    resize(size);
}

//-----------------------------------------------------------------------------
inline ByteBuffer& ByteBuffer::operator=(const ByteBuffer& rhs)
//-----------------------------------------------------------------------------
{
    if (&rhs != this)
    {
        mSize = rhs.mSize;
        if ((mSize > mCapacity) || (mSize < (mCapacity / 4)))
        {
            delete[] mData;
            mData = this->alloc(mSize);
        }

        if (mSize)
        {
            std::memcpy(mData, rhs.mData, mSize);
        }
    }
    return *this;
}

//-----------------------------------------------------------------------------
inline U8* ByteBuffer::data()
//-----------------------------------------------------------------------------
{
    return mData;
}

//-----------------------------------------------------------------------------
inline U8* ByteBuffer::data(U32 offset)
//-----------------------------------------------------------------------------
{
    CIA_ASSERT(offset < mSize, "Out of bounds access!");
    return mData + offset;
}

//-----------------------------------------------------------------------------
inline const U8* ByteBuffer::data() const
//-----------------------------------------------------------------------------
{
    return mData;
}

//-----------------------------------------------------------------------------
inline const U8* ByteBuffer::data(U32 offset) const
//-----------------------------------------------------------------------------
{
    CIA_ASSERT(offset < mSize, "Out of bounds access!");
    return mData + offset;
}

//-----------------------------------------------------------------------------
inline U8 ByteBuffer::operator[](U32 index) const
//-----------------------------------------------------------------------------
{
    CIA_ASSERT(index < mSize, "Out of bounds access!");
    return mData[index];
}

//-----------------------------------------------------------------------------
inline U8* ByteBuffer::operator()(U32 index)
//-----------------------------------------------------------------------------
{
    CIA_ASSERT(index < mSize, "Out of bounds access!");
    return mData + index;
}

//-----------------------------------------------------------------------------
inline const U8* ByteBuffer::operator()(U32 index) const
//-----------------------------------------------------------------------------
{
    CIA_ASSERT(index < mSize, "Out of bounds access!");
    return mData + index;
}

//-----------------------------------------------------------------------------
inline bool ByteBuffer::operator==(const ByteBuffer& other) const
//-----------------------------------------------------------------------------
{
    bool result = false;

    if (this == &other)
    {
        result = true;
    }
    else if (mSize == other.mSize)
    {
        result = (0 == std::memcmp(mData, other.mData, mSize));
    }
    return result;
}

//-----------------------------------------------------------------------------
inline bool ByteBuffer::operator!=(const ByteBuffer& other) const
//-----------------------------------------------------------------------------
{
    return !(*this == other);
}

//-----------------------------------------------------------------------------
template<> inline std::string toSingleLineString(const JCI::ByteBuffer& obj)
//-----------------------------------------------------------------------------
{
    return "TBD";
}

//-----------------------------------------------------------------------------
template<> inline std::string toMultiLineString(const JCI::ByteBuffer& obj, const std::string& indent)
//-----------------------------------------------------------------------------
{
    return "TBD";
}

}   // namespace JCI

#endif /* INFRASTRUCTURE_BALI_BYTE_BUFFER_HPP */
