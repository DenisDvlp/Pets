//Positionable.h
#pragma once
#include "PositionableT.h"

using Positionable8 = PositionableT<char>;
using Positionable16 = PositionableT<short>;
using Positionable32 = PositionableT<int>;
using Positionable = Positionable32;
using PositionableF = PositionableT<float>;