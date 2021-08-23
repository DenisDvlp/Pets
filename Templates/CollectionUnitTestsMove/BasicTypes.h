//BasicTypes.h
#pragma once
#include "PointBase.h"
#include "SizeBase.h"
#include "RectBase.h"
#include "Container.h"

using Point  = PointBase<int>;
using PointF = PointBase<float>;

using Size  = SizeBase<int>;
using SizeF = SizeBase<float>;

using Rect  = RectBase<int>;
using RectF = RectBase<float>;

template <typename T>
using Vector = Container<std::vector<T>>;
template <typename T>
using List = Container<std::list<T>>;
template <typename T>
using Deque = Container<std::deque<T>>;