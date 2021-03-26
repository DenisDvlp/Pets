#pragma once
#include <windows.h>
#include <tchar.h>
#include "Collection.h"
#include "Canvas.h"
#include "Macros.h"

#define classname Console
class Console
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();

	property(CSize, size, size(value.width(), value.height()).size(), value);
	setget(short, fontSize, setFontSize(value), getFontSize().height());

	Console& DisableSelection();
	CSize getFontSize();
	Console& setFontSize(short value);
public:
	Console();
	Console(CSize size);
	Console(CSize size, short fontSize);
	Console(int width, int height);
	Console(int width, int height, short fontSize);
	Console& size(int width, int height);
	CPoint mousePosToCursorPos(CPoint position);
	Console& draw(Canvas &canvas);
};

