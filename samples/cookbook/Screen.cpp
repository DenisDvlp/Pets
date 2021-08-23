#include "Screen.h"

Screen::~Screen() {
	for (auto rect : drawables)
		delete rect;
}

void Screen::Add(Drawable* singleRect) {
	drawables.push_back(singleRect);
}

void Screen::Draw() {
	canvas.Clear(COLOR_BLACK);
	for (auto drawable : drawables) {
		if (!drawable->Visible()) continue;
		canvas.Draw(drawable);
	}
	SMALL_RECT drawableRect = {
		0, 0,
		canvas.Size().x,
		canvas.Size().y
	};
	COORD bufferSize = {
		canvas.Size().x,
		canvas.Size().y
	};
	WriteConsoleOutput(handle, canvas, bufferSize, { 0, 0 }, &drawableRect);
}

void Screen::SetSize(int width, int height) {
	width = width < 0 ? 0 : width;
	height = height < 0 ? 0 : height;
	size.x = width;
	size.y = height;
	canvas.SetSize({ width , height });
	SMALL_RECT windowSize = { 0, 0, width - (!width ? 0 : 1), height - (!height ? 0 : 1) };
	COORD bufferSize = { width, height };
	SetConsoleWindowInfo(handle, TRUE, &windowSize);
	SetConsoleScreenBufferSize(handle, bufferSize);
}

POINT Screen::Size()
{
	return size;
}

vector<string> Canvas::Split(string str, const char * delim)
{
	vector<string> strings;
	int pos = str.find_first_of('\n');
	while (pos >= 0) {
		strings.push_back(str.substr(0, pos));
		str = str.substr(pos + 1);
		pos = str.find_first_of('\n');
	}
	strings.push_back(str);
	return strings;
}

void Canvas::Clear(COLOR color)
{
	for (int i = 0; i < size.x * size.y; i++) {
		canvas[i].Char.UnicodeChar = ' ';
		canvas[i].Attributes = color;
	}
}

void Canvas::SetSize(POINT size)
{
	if (size.x < 0) size.x = 0;
	if (size.y < 0) size.y = 0;
	int newSize = size.x * size.y;
	if (!newSize || newSize != this->size.x * this->size.y) {
		delete[] canvas;
		canvas = nullptr;
	}
	if (!newSize || newSize == this->size.x * this->size.y) return;
	canvas = new CHAR_INFO[newSize];
	this->size.x = size.x;
	this->size.y = size.y;
	Clear(COLOR_BLACK);
}

void Canvas::Draw(Drawable *drawable)
{
	vector<string> strings = Split(drawable->Content(), "\n");
	int count = strings.size();
	bool isNoColor = drawable->Color() == COLOR_TRANSPARENT;
	bool isNoBackground = drawable->Background() == COLOR_TRANSPARENT;
	if (isNoBackground && isNoColor) return;
	int index = 0;
	int length = size.x * size.y;
	int x = drawable->Position().x;
	int y = drawable->Position().y;
	for (int i = 0; i < drawable->Size().y; i++)
	for (int j = 0; j < drawable->Size().x; j++) {
		index = (y + i) * size.x + x + j;
		if (index >= length) return;
		if (index < 0 || index / size.x > y + i) break;
		if (index / size.x < y + i) continue;
		if (i >= count || j >= strings[i].size())
			canvas[index].Char.UnicodeChar = ' ';
		else {
			if(!isNoBackground)
				canvas[index].Char.UnicodeChar = isNoColor ? ' ' : strings[i][j];
			if (!isNoColor)
				canvas[index].Attributes = canvas[index].Attributes & 240 | drawable->Color();
		}
		if (!isNoBackground)
			canvas[index].Attributes = canvas[index].Attributes & 15 | drawable->Background() << 4;
	}
}

Canvas::~Canvas()
{
	SetSize({ 0, 0 });
}

Canvas::operator const CHAR_INFO*()
{
	return canvas;
}

POINT Canvas::Size()
{
	return size;
}
