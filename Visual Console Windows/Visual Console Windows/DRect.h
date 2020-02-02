//DRect.h
#pragma once
#include "DRectT.h"
#include "DTypes.h"

using DRect8 = DRectT<int8>;
using DRect16 = DRectT<int16>;
using DRect32 = DRectT<int32>;
using DRect64 = DRectT<int64>;
using DRectF = DRectT<float>;

using DRect = DRectT<dint>;