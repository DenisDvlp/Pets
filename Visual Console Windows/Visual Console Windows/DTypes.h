#pragma once
#include<cstdint>
//DTypes.h

//char
using uchar   = unsigned char;
using byte    = std::uint8_t;
using sbyte   = std::int8_t;
using char16  = char16_t;
using char32  = char32_t;
using wchar   = wchar_t;

//int
using ushort = unsigned short;
using uint   = unsigned int;
using ulong  = unsigned long;
//long
using llong  = long long;
using ullong = unsigned long long;

using int8   = std::int8_t;
using uint8  = std::uint8_t;
using int16  = std::int16_t;
using uint16 = std::uint16_t;
using int32  = std::int32_t;
using uint32 = std::uint32_t;
using int64  = std::int64_t;
using uint64 = std::uint64_t;

//float
//double
using ldouble = long double;

//pointer
using ptr = void*;
#ifdef _WIN64
using ptrint  = int64;
using ptruint = uint64;
#else
using ptrint = int32;
using ptruint = uint32;
#endif

//aliases
template<typename Return, typename T, typename... Args>
using ClassMethodT = Return(T::*)(Args...);
template<typename Return, typename... Args>
using FunctionT = Return(*)(Args...);

using dint = int16;