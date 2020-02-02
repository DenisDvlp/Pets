//Console.h
#pragma once
#include "BasicTypes.h"
#include "IMessageReadable.h"
#include "IDisplay.h"
#include <Windows.h>

class Console
  : public IMessageReadable
  , public IDisplay<CHAR_INFO>
{
public:
  Console();
  void setTitle(const std::string&);
  std::string getTitle();
  void setFontSize(short);
  short getFontSize();
  void setFontName(const std::string&);
  std::string getFontName();
  void setSize(Size16);
  void setSize(short, short);
  Size16 getSize();
  void show(const CHAR_INFO*) override;
  DVector<Message> readMessages() override;

private:
  void init();
  void initFont(short size, const std::string&);
  void setFontSize(CONSOLE_FONT_INFOEX&, short);
  void setFontName(CONSOLE_FONT_INFOEX&, const std::string&);
  void setFont(CONSOLE_FONT_INFOEX&);
  CONSOLE_FONT_INFOEX getFont();

private:
  HANDLE m_handleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE m_handleIN = GetStdHandle(STD_INPUT_HANDLE);
  HWND m_handleWindow = GetConsoleWindow();
  Size16 m_size;
  Size16 m_maxSize;
  std::string m_title;
};