//SystemLoop.h
#pragma once
#include "IMessageLoop.h"
#include "Drawable.h"

class IView;
class IDrawBuffer;
class Message;
class SystemEvents;

class SystemLoop
  : public IMessageLoop
{
  using byte = unsigned char;
public:
  SystemLoop(IMessageReadable*, SystemEvents*, IDrawBuffer*, Drawable*);
private:
  void loop(Message) override;
private:
  SystemEvents* const m_systemEvents = nullptr;
  IDrawBuffer* const m_drawBuffer = nullptr;
  Drawable* const m_rootDrawable = nullptr;
};

