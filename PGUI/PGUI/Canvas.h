#pragma once
#include <windows.h>    // CHAR_INFO
#include "Macros.h"     // ALIGN,COLOR
#include "Sizable.h"
#include "Collection.h" // CRect,CStrings,CPoint
#include "Console.h"

class Canvas : public Sizable
{
  struct Cell
  {
    CHAR_INFO *m_info = nullptr;
    void set(char character, COLOR color, COLOR background);
  };

  CHAR_INFO* m_info = nullptr;
  Cell **m_cells = nullptr;

  void resizeCharInfo(int width, int height);
  void resizeCells(int width, int height);

  void cell(int x, int y, char character, COLOR color, COLOR background, CRect cropRect);
  void drawRectHelper(CRect rect, char character, COLOR color, COLOR background);
  void drawBorderHelper(CRect rect, COLOR color, COLOR background, char borders[8], int thickness, CRect cropRect);
  void drawTextHelperCalc(int &i, int &di, int &size, int srcStart, int srcSize, int destSize, ALIGN align, ALIGN centerAlign, ALIGN bottomRightAlign, bool crop);
  void drawTextHelper(int x, int y, int width, CString str, COLOR color, COLOR background, ALIGN align, bool crop, CRect cropRect);
  void drawTextHelper(CRect rect, CStrings strings, COLOR color, COLOR background, ALIGN align, bool crop, CRect cropRect);

  virtual void onResize();

public:

  Canvas();
  Canvas(CSize size);
  Canvas(int width, int height);
  virtual ~Canvas();

  void clear(COLOR color);
  void clear(COLOR color, CRect cropRect);
  void drawRect(CRect rect, COLOR background, COLOR color, char character);
  void drawRect(CRect rect, COLOR background, COLOR color, char character, CRect cropRect);
  void drawBorder(CRect rect, COLOR background, COLOR color, char borders[8], int thickness);
  void drawBorder(CRect rect, COLOR background, COLOR color, char borders[8], int thickness, CRect cropRect);
  void drawText(CRect rect, CString str, COLOR color, COLOR background, ALIGN align, bool crop);
  void drawText(CRect rect, CString str, COLOR color, COLOR background, ALIGN align, bool crop, CRect cropRect);
  void drawText(CRect rect, CStrings strings, COLOR color, COLOR background, ALIGN align, bool crop);
  void drawText(CRect rect, CStrings strings, COLOR color, COLOR background, ALIGN align, bool crop, CRect cropRect);

  void display(Console &console);
};
