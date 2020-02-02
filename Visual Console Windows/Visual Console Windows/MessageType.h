//MessageType.h
#pragma once
#include <xstring>

enum class MessageType : unsigned char
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

    SIZE
};

std::string toString(MessageType key);