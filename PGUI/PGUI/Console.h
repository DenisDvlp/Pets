#pragma once
#include <windows.h>
#include <tchar.h>
#include "Collection.h"
#include "Sizable.h"

class Console : public Sizable
{
  HANDLE  m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE  m_hIn = GetStdHandle(STD_INPUT_HANDLE);
  HWND    m_hwnd = GetConsoleWindow();
  CONSOLE_FONT_INFOEX m_fontex = { 0 };

  void disableSelection();
  void initFontex();
  void recalcSize();

  virtual void onResize();

public:

  Console();
  Console(CSize size);
  Console(CSize size, int fontSize);
  Console(int width, int height);
  Console(int width, int height, int fontSize);

  void fontSize(int fontSize);
  int fontSize();

  //func
  void draw(const CHAR_INFO* charInfo, int width, int height);
  CPoint mousePosToCursorPos(CPoint point);
  CPoint mousePosToCursorPos(int x, int y);
};

