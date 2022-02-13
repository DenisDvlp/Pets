#pragma once

template<typename T, unsigned char BitsInByte>
class ArrayOfExtendedByte {
  char* const bytes;

  class ElementAccessor {
    size_t offset;
    char* const bytes;
  public:
    ElementAccessor(size_t offset, char* const bytes) : offset(offset), bytes(bytes) {}

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
  ArrayOfExtendedByte(char* const bytes) : bytes(bytes) {}

  ElementAccessor operator[](size_t offset) const {
    return { offset, bytes };
  }
};
