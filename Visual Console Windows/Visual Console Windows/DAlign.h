//DAlign.h
#pragma once
#include "DTypes.h"

enum class DAlign : uint8
{
    LEFT = 0b0010,
    CENTER_H = 0b0000,
    RIGHT = 0b0001,
    JUSTIFY_H = LEFT | RIGHT,

    TOP = 0b1000,
    CENTER_V = CENTER_H,
    BOTTOM = 0b0100,
    JUSTIFY_V = TOP | BOTTOM,

    DEFAULT = LEFT | TOP,
    CENTER = CENTER_V | CENTER_H,
};