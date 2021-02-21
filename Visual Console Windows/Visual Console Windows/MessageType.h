//MessageType.h
#pragma once
#include "DTypes.h"
#include <xstring>

enum class MessageType : byte
{
    NONE = 0,

    KEY_UP,
    KEY_DOWN,
    MOUSE_BUTTONS,
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_MOVE,
    MOUSE_DOUBLE_CLICK,
    MOUSE_WHEEL,
    DISPLAY_RESIZE,
    APP_FOCUS,

    SIZE
};

std::string toString(MessageType key);