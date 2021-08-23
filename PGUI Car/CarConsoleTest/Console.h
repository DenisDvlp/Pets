#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

class Console
{
  HANDLE hOut_ = GetStdHandle(STD_OUTPUT_HANDLE);
  HWND hwnd_ = GetConsoleWindow();
  int width_ = 0;
  int height_ = 0;

  void recalcSize(bool noMove);
public:

  Console();
  Console(int width, int height);
  Console(int width, int height, short fontSize);
  int getWidth();
  int getHeight();
  void setFontSize(short fontSize);
  short getFontSize();
  void resize(int width, int height);
  void draw(const CHAR_INFO* charInfo, int width, int height);
};

#endif // CONSOLE_H