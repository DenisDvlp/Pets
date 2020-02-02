//Message.h
#pragma once
#include "Key.h"
#include "MessageType.h"
#include "Point.h"
#include "Size.h"
#include <xstring>

class Message
{
  using byte = unsigned char;
public:
  MessageType type{};
  byte keyStates = 0;
  union Data
  {
    Data() {};
    byte byte = 0;
    Key key;
    Point16 position;
    Size16 size;
  } data;

  std::string toString();
};

