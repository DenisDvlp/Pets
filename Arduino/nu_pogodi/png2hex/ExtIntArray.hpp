#pragma once

// ExtIntArray allows to read a plain bytes
// as if there was an arbitrary number of bits in each value.
// This allows to reduce occupied place. If you know the values wouldn't be larger
// then, say, 2000, which exactly fit in 11 bits, then you haven't to use regular 16 bits of `short`,
// you can represent the bytes as 11-bit-numbers instead.
//E.g.:
//   ExtIntArray<short, 11> exBytes(bytes);
//                        // ^ get and set the values as `short`
//   // 4th element starts from the 2nd bit of 5th byte (offset is 3 * 11 = 33 bits).
//   exBytes[4] = 1999;
//   short x = exBytes[4]; // return 1999
template<typename T, unsigned char BitsInByte>
class ExtIntArray {
  unsigned char* const bytes;

  class ElementAccessor {
    size_t offset;
    unsigned char* const bytes;
  public:
    ElementAccessor(size_t offset, unsigned char* const bytes) : offset(offset), bytes(bytes) {}

    T operator=(T value)&& {
      size_t realOffset = offset * BitsInByte / CHAR_BIT;
      unsigned char shift = offset * BitsInByte % CHAR_BIT;
      unsigned char byte = bytes[realOffset];
      unsigned char count = BitsInByte;
      while (count--) {
        if (shift == CHAR_BIT) {
          bytes[realOffset] = byte;
          byte = bytes[++realOffset];
          shift = 0;
        }
        byte = (byte & ~(1 << shift)) | ((value & 1) << shift);
        ++shift;
        value >>= 1;
      }
      bytes[realOffset] = byte;
      return value;
    }

    operator T() {
      T result = 0;
      size_t realOffset = offset * BitsInByte / CHAR_BIT;
      const unsigned char shift = offset * BitsInByte % CHAR_BIT;
      unsigned char byte = bytes[realOffset] >> shift;
      unsigned char bitsLeft = CHAR_BIT - shift;
      unsigned char count = 0;
      while (count < BitsInByte) {
        result |= (byte & 1) << count++;
        if (!--bitsLeft) {
          bitsLeft = CHAR_BIT;
          byte = bytes[++realOffset];
        }
        else {
          byte >>= 1;
        }
      }
      return result;
    }
  };

public:
  ExtIntArray(unsigned char* const bytes) : bytes(bytes) {}

  ElementAccessor operator[](size_t offset) const {
    return { offset, bytes };
  }
};
