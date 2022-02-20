#pragma once

// ArrayOfExtendedByte allows to read a plain bytes
// as if there was an arbitrary number of bits in each value.
// This allows to reduce occupied place. If you know the values wouldn't be larger
// then, say, 2000, which exactly fit in 11 bits, then you haven't to use regular 16 bits of `short`,
// you can represent the bytes as 11-bit-numbers instead.
//E.g.:
//   ArrayOfExtendedByte<short, 11> exBytes(bytes);
//                        // ^ get and set the values as `short`
//   // 4th element starts from the 2nd bit of 5th byte (offset is 3 * 11 = 33 bits).
//   exBytes[4] = 1999;
//   short x = exBytes[4]; // return 1999
template<typename T>
class ArrayOfExtendedByte {
  static constexpr byte BITS_IN_BYTE;
  const uint8_t* const bytes;
  const byte bitsInByte;

public:
  ArrayOfExtendedByte(const uint8_t* const bytes, byte bitsInByte) :
    bytes(bytes), bitsInByte(bitsInByte) {}

  T operator[](size_t offset) const {
    T result = 0;
    size_t realOffset = offset * bitsInByte / BITS_IN_BYTE;
    const unsigned char shift = offset * bitsInByte % BITS_IN_BYTE;
    unsigned char byte = pgm_read_byte(bytes + realOffset) >> shift;
    unsigned char bitsLeft = BITS_IN_BYTE - shift;
    unsigned char count = 0;
    while (count < bitsInByte) {
      result |= (byte & 1) << count++;
      if (!--bitsLeft) {
        bitsLeft = BITS_IN_BYTE;
        byte = pgm_read_byte(bytes + ++realOffset);
      }
      else {
        byte >>= 1;
      }
    }
    return result;
  }
};
