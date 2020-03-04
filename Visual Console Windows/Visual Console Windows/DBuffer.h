//DBuffer.h
#pragma once
#include "DMultiBufferT.h"

template<typename T>
using DBuffer = DMultiBufferT<T, 1>;

template<typename T>
using DDoubleBuffer = DMultiBufferT<T, 2>;

template<typename T>
using DTripleBuffer = DMultiBufferT<T, 3>;