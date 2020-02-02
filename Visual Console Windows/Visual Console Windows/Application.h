//Application.h
#pragma once
#include "Console.h"
#include "MessageBuffer.h"
#include "Root.h"
#include "DrawBuffer.h"
#include "ConsoleLoop.h"
#include "SystemLoop.h"
#include "DrawLoop.h"
#include "Signal.h"
#include "SystemEvents.h"

struct _CHAR_INFO;

class Application
{
public:
  Application();
  void run();
  void exit();
  static SystemEvents events;
private:
  Console m_console;
  MessageBuffer m_messageBuffer;
  DrawBuffer<_CHAR_INFO> m_drawBuffer;
  Root m_root;
  ConsoleLoop m_consoleLoop;
  SystemLoop m_systemLoop;
  DrawLoop<_CHAR_INFO> m_drawLoop;
};