#pragma once
#include <Windows.h>
#include "Collection.h"
#include "Macros.h"

#define classname Canvas
class Canvas
{
	friend class Console;

	CHAR_INFO* canvas = nullptr;
	property(CSize, size, size(value.width(), value.height()).size(), value);

	void info(CPoint &position, char character, COLOR color, COLOR background);
	void info(int x, int y, char character, COLOR color, COLOR background);

	setget(int, width, _size.width(value), _size.width());
	setget(int, height, _size.height(value), _size.height());

public:

	Canvas();
	Canvas(CSize size);
	Canvas(int width, int height);
	~Canvas();
	Canvas& size(int width, int height);
	Canvas& clear(COLOR color);
	Canvas& drawBorder(CRect &rect, char borders[8], COLOR color, COLOR background);
	Canvas& drawText(CRect &rect, CStrings &strings, COLOR color, COLOR background, ALIGN align);

	Canvas& drawRect(CRect &rect, char character, COLOR color, COLOR background);
	Canvas& drawHorizLine(CPoint &position, int length, char character, COLOR color, COLOR background);
	Canvas& drawVertLine(CPoint &position, int length, char character, COLOR color, COLOR background);
};