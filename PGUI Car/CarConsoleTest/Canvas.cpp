#include "Canvas.h"

//Cell

void Canvas::Cell::set(char character, COLOR color, COLOR background)
{
  info_->Char.AsciiChar = character;
  info_->Attributes =
    (background == COLOR_TRANSPARENT ? info_->Attributes & 0xF0 : background << 4) |
    (color      == COLOR_TRANSPARENT ? info_->Attributes & 0x0F : color);
}

//Canvas

int Canvas::getWidth()
{
  return width_;
}

int Canvas::getHeight()
{
  return height_;
}

Canvas::Canvas() 
{}

Canvas::Canvas(int width, int height)
{
  resize(width, height);
}

Canvas::~Canvas()
{
  resize(0, 0);
}

void Canvas::cell(int x, int y, char character, COLOR color, COLOR background, Rect cropRect)
{
  if (cropRect.hasPoint(x, y))
    cells_[x][y].set(character, color, background);
}

void Canvas::resizeCharInfo(int width, int height)
{
  int newSize = width * height;
  delete[] charInfo_;
  charInfo_ = newSize > 0 ? new CHAR_INFO[newSize] : nullptr;
}

void Canvas::resizeCells(int width, int height)
{
  for (int i = 0; i < width_; i++)
  {
    delete[] cells_[i];
  }
  delete[] cells_;
  cells_ = nullptr;

  if (width * height > 0)
  {
    cells_ = new Cell*[width];
    for (int i = 0; i < width; i++)
    {
      cells_[i] = new Cell[height];
      for (int j = 0; j < height; j++)
      {
        cells_[i][j].info_ = &charInfo_[i + j * width];
      }
    }
  }
}

void Canvas::resize(int width, int height)
{
  width  = max(0, width);
  height = max(0, height);
  resizeCharInfo(width, height);
  resizeCells(width, height);
  width_  = width;
  height_ = height;
  clear(COLOR_BLACK);
}

void Canvas::drawRect(Rect rect, char character, COLOR color, COLOR background)
{
  rect = rect.intersectRect(Rect(0, 0, width_, height_));
  int right  = rect.getRight();
  int bottom = rect.getBottom();
  for (int i = rect.x; i < right; i++)
  {
    for (int j = rect.y; j < bottom; j++)
    {
      cells_[i][j].set(character, color, background);
    }
  }
}
void Canvas::drawText(int x, int y, std::string str, COLOR color, COLOR background)
{
  int i = 0;
  int length = str.size();
  Rect rect = Rect(0, 0, width_, height_);
  while (i < length)
  {
    cell(x++, y, str[i++], color, background, rect);
  }
}

void Canvas::drawCell(int x, int y, char character, COLOR color, COLOR background)
{
  cell(x, y, character, color, background, Rect(0, 0, width_, height_));
}

void Canvas::clear(COLOR color)
{
  CHAR_INFO info;
  info.Char.AsciiChar = ' ';
  info.Attributes = color << 4;
  int size = width_ * height_;
  for (int i = 0; i < size; i++)
  {
    charInfo_[i] = info;
  }
}

void Canvas::clear(COLOR color, Rect rect)
{
  CHAR_INFO info;
  info.Char.AsciiChar = ' ';
  info.Attributes = color << 4;
  rect = rect.intersectRect(Rect(0, 0, width_, height_));
  int right  = rect.getRight();
  int bottom = rect.getBottom();
  for (int i = rect.x; i < right; i++)
  {
    for (int j = rect.y; j < bottom; j++)
    {
      *cells_[i][j].info_ = info;
    }
  }
}

void Canvas::display(Console &console)
{
  console.draw(charInfo_, width_, height_);
}