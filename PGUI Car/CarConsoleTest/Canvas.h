#ifndef CANVAS_H
#define CANVAS_H

#include <windows.h>
#include <string>
#include "Macros.h"
#include "Utils.h"
#include "Console.h"

class Canvas
{
  struct Cell
  {
    CHAR_INFO *info_ = nullptr;
    void set(char character, COLOR color, COLOR background);
  };

  CHAR_INFO* charInfo_ = nullptr;
  Cell **cells_ = nullptr;
  int width_ = 0;
  int height_ = 0;

  void cell(int x, int y, char character, COLOR color, COLOR background, Rect clipRect);
  void resizeCharInfo(int width, int height);
  void resizeCells(int width, int height);

public:
  Canvas();
  Canvas(int width, int height);
  ~Canvas();

  int getWidth();
  int getHeight();
  void resize(int width, int height);
  void clear(COLOR color);
  void clear(COLOR color, Rect rect);
  void drawRect(Rect rect, char character, COLOR color, COLOR background);
  void drawText(int x, int y, std::string str, COLOR color, COLOR background);
  void drawCell(int x, int y, char character, COLOR color, COLOR background);
  void display(Console &console);
};

#endif // CANVAS_H