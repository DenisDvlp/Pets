#include "Canvas.h"

//Cell

inline void Canvas::Cell::set(char character, COLOR color, COLOR background)
{
  m_info->Char.AsciiChar = character;
  m_info->Attributes =
    (background == COLOR_TRANSPARENT ? m_info->Attributes & 0xF0 : background << 4) |
    (color == COLOR_TRANSPARENT ? m_info->Attributes & 0x0F : color);
}

//Canvas

Canvas::Canvas() {}

Canvas::Canvas(CSize size) :
  Canvas(size.width(), size.height())
{}

Canvas::Canvas(int width, int height)
{
  size(width, height);
}

Canvas::~Canvas()
{
  size(0, 0);
}

void Canvas::resizeCharInfo(int width, int height)
{
  int newSize = width * height;
  delete[] m_info;
  m_info = newSize > 0 ? new CHAR_INFO[newSize] : nullptr;
}

void Canvas::resizeCells(int width, int height)
{
  for (int i = 0; i < m_size.width(); i++)
  {
    delete[] m_cells[i];
  }
  delete[] m_cells;
  m_cells = nullptr;

  if (width * height > 0)
  {
    m_cells = new Cell*[width];
    for (int i = 0; i < width; i++)
    {
      m_cells[i] = new Cell[height];
      for (int j = 0; j < height; j++)
      {
        m_cells[i][j].m_info = &m_info[i + j * width];
      }
    }
  }
}

void Canvas::onResize()
{
  resizeCharInfo(m_size.width(), m_size.height());
  resizeCells(m_size.width(), m_size.height());
  clear(COLOR_BLACK);
}

inline void Canvas::cell(int x, int y, char character, COLOR color, COLOR background, CRect cropRect)
{
  if (cropRect.hasPoint(x, y))
  {
    m_cells[x][y].set(character, color, background);
  }
}

void Canvas::drawRectHelper(CRect rect, char character, COLOR color, COLOR background)
{
  int right = rect.right();
  int bottom = rect.bottom();
  for (int i = rect.left(); i < right; i++)
  {
    for (int j = rect.top(); j < bottom; j++)
    {
      m_cells[i][j].set(character, color, background);
    }
  }
}

void Canvas::drawBorderHelper(CRect rect, COLOR color, COLOR background, char borders[8], int thickness, CRect cropRect)
{
  CRect rect = rect.intersectRect(cropRect);

  int x = 0;
  int y = 0;
  int right = 0;
  int bottom = 0;
  int width = 0;
  int height = 0;

  for(int i = 0; i < thickness && !rect.isEmpty(); i++)
  {
    x = rect.x();
    y = rect.y();
    right = rect.right() - 1;
    bottom = rect.bottom() - 1;
    width = rect.width() - 2;
    height = rect.height() - 2;

    cell(x, y, borders[0], color, background, rect);
    cell(right, y, borders[2], color, background, rect);
    cell(x, bottom, borders[5], color, background, rect);
    cell(right, bottom, borders[7], color, background, rect);

    drawRectHelper(CRect(x + 1, y, width, 1).intersectRect(rect), borders[1], color, background);
    drawRectHelper(CRect(x, y + 1, 1, height).intersectRect(rect), borders[3], color, background);
    drawRectHelper(CRect(right, y + 1, 1, height).intersectRect(rect), borders[4], color, background);
    drawRectHelper(CRect(x + 1, bottom, width, 1).intersectRect(rect), borders[6], color, background);

    rect.expand(-1, -1, -1, -1);
  }
}

void Canvas::drawTextHelperCalc(int &i, int &di, int &newSrcSize, int srcStart, int srcSize, int destSize, ALIGN align, ALIGN centerAlign, ALIGN bottomRightAlign, bool crop)
{
  i = 0;
  di = srcStart;
  newSrcSize = srcSize;

  if (HASFLAG(align, centerAlign))
  {
    di += (destSize - srcSize) / 2;
  }
  else if (HASFLAG(align, bottomRightAlign))
  {
    di += destSize - srcSize;
  }

  if (crop && destSize < srcSize)
  {
    i = srcStart - di;
    di += i;
    newSrcSize = i + destSize;
  }
}

void Canvas::drawTextHelper(int x, int y, int width, string str, COLOR color, COLOR background, ALIGN align, bool crop, CRect clipRect)
{
  int i = 0;
  int dx = 0;
  int length = 0;

  drawTextHelperCalc(i, dx, length, x, str.size(), width, align, ALIGN_TEXT_HCENTER, ALIGN_TEXT_RIGHT, crop);

  while (i < length) {
    cell(dx, y, str[i], color, background, clipRect);
    i++;
    dx++;
  }
}

void Canvas::drawTextHelper(CRect rect, CStrings strings, COLOR color, COLOR background, ALIGN align, bool crop, CRect clipRect)
{
  int i = 0;
  int dy = 0;
  int count = 0;

  drawTextHelperCalc(i, dy, count, rect.y(), strings.count(), rect.height(), align, ALIGN_TEXT_VCENTER, ALIGN_TEXT_BOTTOM, crop);

  int x = rect.x();
  int width = rect.width();
  while (i < count)
  {
    drawTextHelper(x, dy, width, strings[i], color, background, align, crop, clipRect);
    i++;
    dy++;
  }
}

void Canvas::clear(COLOR color)
{
  CHAR_INFO info;
  info.Char.AsciiChar = ' ';
  info.Attributes = color << 4;
  int size = m_size.square();
  for (int i = 0; i < size; i++)
  {
    m_info[i] = info;
  }
}

void Canvas::clear(COLOR color, CRect cropRect)
{
  CHAR_INFO info;
  info.Char.AsciiChar = ' ';
  info.Attributes = color << 4;
  cropRect = cropRect.intersectRect(CRect(0, 0, m_size.width(), m_size.height()));
  int right = cropRect.right();
  int bottom = cropRect.bottom();
  for (int i = cropRect.x(); i < right; i++)
  {
    for (int j = cropRect.y(); j < bottom; j++)
    {
      *m_cells[i][j].m_info = info;
    }
  }
}

inline void Canvas::drawRect(CRect rect, COLOR background, COLOR color, char character)
{
  drawRectHelper(rect.intersectRect(m_size.rect()), character, color, background);
}

inline void Canvas::drawRect(CRect rect, COLOR background, COLOR color, char character, CRect cropRect)
{
  drawRectHelper(cropRect.intersectRect(rect).intersectRect(m_size.rect()), character, color, background);
}

inline void Canvas::drawBorder(CRect rect, COLOR background, COLOR color, char borders[8], int thickness)
{
  drawBorderHelper(rect, color, background, borders, thickness, m_size.rect());
}

inline void Canvas::drawBorder(CRect rect, COLOR background, COLOR color, char borders[8], int thickness, CRect cropRect)
{
  drawBorderHelper(rect, color, background, borders, thickness, cropRect.intersectRect(m_size.rect()));
}

inline void Canvas::drawText(CRect rect, string str, COLOR color, COLOR background, ALIGN align, bool crop)
{
  drawText(rect, CStrings(str), color, background, align, crop);
}

inline void Canvas::drawText(CRect rect, string str, COLOR color, COLOR background, ALIGN align, bool crop, CRect cropRect)
{
  drawText(rect, CStrings(str), color, background, align, crop, cropRect);
}

inline void Canvas::drawText(CRect rect, CStrings strings, COLOR color, COLOR background, ALIGN align, bool crop)
{
  drawTextHelper(rect, strings, color, background, align, crop, crop ? rect.intersectRect(m_size.rect()) : m_size.rect());
}

inline void Canvas::drawText(CRect rect, CStrings strings, COLOR color, COLOR background, ALIGN align, bool crop, CRect cropRect)
{
  drawTextHelper(rect, strings, color, background, align, crop, cropRect.intersectRect(rect).intersectRect(m_size.rect()));
}

inline void Canvas::display(Console &console)
{
  console.draw(m_info, m_size.width(), m_size.height());
}