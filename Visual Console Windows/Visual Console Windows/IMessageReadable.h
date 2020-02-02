//IMessageReadable.h
#pragma once
#include "DVector.h"
#include "Message.h"

class IMessageReadable
{
public:
  virtual ~IMessageReadable() = default;
  virtual DVector<Message> readMessages() = 0;
};