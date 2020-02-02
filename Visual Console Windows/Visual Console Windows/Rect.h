//Rect.h
#pragma once
#include "RectT.h"

using Rect8 = RectT<char>;
using Rect16 = RectT<short>;
using Rect32 = RectT<int>;
using Rect = Rect32;
using RectF = RectT<float>;