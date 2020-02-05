//DMessage.h
#pragma once
#include "Key.h"
#include "MessageType.h"
#include "DPoint.h"
#include "DSize.h"
#include "DTypes.h"

class DMessage
{
public:
    MessageType type{};
    byte keyStates = 0;
    union Data
    {
        Data(){};
        byte byte = 0;
        Key key;
        DPoint position;
        DSize size;
    } data;
};

