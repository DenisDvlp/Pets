//DMessages.h
#pragma once
#include "Key.h"
#include "MessageType.h"
#include "DPoint.h"
#include "DSize.h"
#include "DTypes.h"

struct DMessage
{
    MessageType type{};
    byte keyStates = 0;
    union Data
    {
        Data(){}
        struct
        {
            byte byte;
            DPoint position;
        };
        Key key{};
        DSize size;
    } data;
};


struct DMouseMessage
{
  Key key{};
  DPoint position;
};