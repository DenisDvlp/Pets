#pragma once
//dpg_types.h

//char
using uchar = unsigned char;
using byte = unsigned char;
using sbyte = char;
using uchar8 = unsigned char;
using uchar16 = char16_t;
using uchar32 = char32_t;
using wchar = wchar_t;

//int
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
//long
using llong = long long;
using ullong = unsigned long long;
#if _MSC_VER
using int8 = __int8;
using uint8 = unsigned __int8;
using int16 = __int16;
using uint16 = unsigned __int16;
using int32 = __int32;
using uint32 = unsigned __int32;
using int64 = __int64;
using uint64 = unsigned __int64;
#else
using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using int32 = int;
using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;
#endif

//float
//double
using ldouble = long double;

//pointer
using ptr = void*;
#ifdef _WIN64
using ptrint = int64;
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