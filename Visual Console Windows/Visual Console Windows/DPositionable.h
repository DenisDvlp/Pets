//DPositionable.h
#pragma once
#include "DPositionableT.h"
#include "DTypes.h"

using DPositionable8 = DPositionableT<int8>;
using DPositionable16 = DPositionableT<int16>;
using DPositionable32 = DPositionableT<int32>;
using DPositionable64 = DPositionableT<int64>;
using DPositionableF = DPositionableT<float>;

using DPositionable = DPositionableT<dint>;