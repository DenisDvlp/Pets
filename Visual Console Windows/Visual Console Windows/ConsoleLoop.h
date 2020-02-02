//ConsoleLoop.h
#pragma once
#include "IMessageLoop.h"
#include "BasicTypes.h"

class MessageBuffer;

class ConsoleLoop
  : public IMessageLoop
{
public:
  ConsoleLoop(IMessageReadable*, MessageBuffer*);
private:
  void loop(Message) override;
private:
  MessageBuffer* const m_messageBuffer = nullptr;
  byte m_keyStates = 0;
  byte m_mouseButtons = 0;
  Size16 m_size;
  Point16 m_position;
};