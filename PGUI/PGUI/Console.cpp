#include "Console.h"
#include "Utils.h"

Console::Console() :
  Console(80, 40, 12)
{}

Console::Console(CSize size) :
  Console(size.width(), size.height(), 12)
{}

Console::Console(CSize size, int fontSize) :
  Console(size.width(), size.height(), fontSize)
{}

Console::Console(int width, int height) :
  Console(width, height, 12)
{}

Console::Console(int width, int height, int font)
{
  initFontex();
  disableSelection();
  size(width, height);
  fontSize(font);
}

void Console::onResize()
{
  int width  = range(CONSOLE_WIDTH_MIN,  m_size.width(),  CONSOLE_WIDTH_MAX );
  int height = range(CONSOLE_HEIGHT_MIN, m_size.height(), CONSOLE_HEIGHT_MAX);
  m_size.set(width, height);
  COORD      bufferSize = { width, height };
  SMALL_RECT consoleSize = { 0, 0, width - 1, height - 1 };
  SetConsoleWindowInfo(m_hOut, TRUE, &consoleSize); // Window Size 
  SetConsoleScreenBufferSize(m_hOut, bufferSize);   // Buffer Size
  recalcSize();
}

void Console::fontSize(int fontSize)
{
  CONSOLE_FONT_INFOEX fontex = m_fontex;
  fontex.dwFontSize.Y = range(FONT_SIZE_MIN, fontSize, FONT_SIZE_MAX);
  SetCurrentConsoleFontEx(m_hOut, FALSE, &fontex);
  recalcSize();
}

int Console::fontSize()
{
  CONSOLE_FONT_INFO font;
  GetCurrentConsoleFont(m_hOut, FALSE, &font);
  return font.dwFontSize.Y;
}

void Console::disableSelection()
{
  DWORD dwPreviousMode = 0;
  GetConsoleMode(m_hIn, &dwPreviousMode);
  SetConsoleMode(m_hIn, (dwPreviousMode | ENABLE_MOUSE_INPUT) & ~ENABLE_QUICK_EDIT_MODE);
}

void Console::initFontex()
{
  m_fontex.cbSize = sizeof(m_fontex);
  m_fontex.FontWeight = FW_NORMAL;
  TCHAR fontName[] = TEXT("Lucida Console");
  _tcscpy_s(m_fontex.FaceName, lstrlen(fontName) + 1, fontName);
}

void Console::recalcSize()
{
  RECT displayArea;
  RECT clientRect;
  RECT windowRect;
  CONSOLE_FONT_INFO font;

  GetCurrentConsoleFont(m_hOut, FALSE, &font);
  SystemParametersInfo(SPI_GETWORKAREA, 0, &displayArea, 0);
  GetClientRect(m_hwnd, &clientRect);
  GetWindowRect(m_hwnd, &windowRect);

  SetWindowPos(
    m_hwnd, 0,
    windowRect.left, windowRect.top,
    windowRect.right - windowRect.left - clientRect.right + font.dwFontSize.X * m_size.width(),
    windowRect.bottom - windowRect.top - clientRect.bottom + font.dwFontSize.Y * m_size.height(),
    SWP_SHOWWINDOW
  );
}

void Console::draw(const CHAR_INFO* charInfo, int width, int height)
{
  SMALL_RECT drawableRect = { 0, 0, width, height };
  COORD      bufferSize = { width, height };
  WriteConsoleOutputA(m_hOut, charInfo, bufferSize, { 0, 0 }, &drawableRect);
}

CPoint Console::mousePosToCursorPos(CPoint point)
{
  return mousePosToCursorPos(point.x(), point.y());
}

CPoint Console::mousePosToCursorPos(int x, int y)
{
  CONSOLE_FONT_INFO font;
  GetCurrentConsoleFont(m_hOut, FALSE, &font);
  return CPoint(x / font.dwFontSize.X - 2, y / font.dwFontSize.Y - 2);
}
