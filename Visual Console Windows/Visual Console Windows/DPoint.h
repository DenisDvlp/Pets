//DPoint.h
#pragma once
#include "DPointT.h"
#include "DTypes.h"

using DPoint8 = DPointT<int8>;
using DPoint16 = DPointT<int16>;
using DPoint32 = DPointT<int32>;
using DPoint64 = DPointT<int64>;
using DPointF = DPointT<float>;

using DPoint = DPointT<dint>;