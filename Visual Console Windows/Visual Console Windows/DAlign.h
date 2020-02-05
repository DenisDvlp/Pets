//DAlign.h
#pragma once
#include "DTypes.h"

enum class DAlign : uint8
{
    LEFT      = 0b0000,
    RIGHT     = 0b0001,
    TOP       = 0b0000,
    BOTTOM    = 0b0010,
    CENTER_H  = 0b0100,
    CENTER_V  = 0b1000,

    DEFAULT = LEFT | TOP,
    CENTER = CENTER_V | CENTER_H,
};