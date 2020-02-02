//DrawLoop.h
#pragma once
#include "Utils.h"
#include "ILoop.h"

template<typename T>
class IDrawBufferNative;

template<typename T>
class IDisplay;

template<typename T>
class DrawLoop
  : public ILoop
{
public:
  DrawLoop(IDrawBufferNative<T>*, IDisplay<T>*);
private:
  void loop() override;
private:
  IDrawBufferNative<T>* const m_drawBufferNative = nullptr;
  IDisplay<T>* const m_display = nullptr;
};


template<typename T>
DrawLoop<T>::DrawLoop(IDrawBufferNative<T>* drawBuffer, IDisplay<T>* display)
  : m_drawBufferNative(drawBuffer)
  , m_display(display)
{}

template<typename T>
void DrawLoop<T>::loop()
{
  if (m_drawBufferNative->swap())
  {
    auto buffer = m_drawBufferNative->buffer();
    m_display->show(buffer);
  }
  utils::sleep(1);
}
