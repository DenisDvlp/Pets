#pragma once
#include "Drawable.h"

class Canvas {
	CHAR_INFO* canvas = nullptr;
	POINT size = { 0 };
	vector<string> Split(string str, const char* delim);

public:

	void Clear(COLOR color);
	void SetSize(POINT size);
	void Draw(Drawable *drawable);
	~Canvas();
	operator const CHAR_INFO*();
	POINT Size();
};

class Screen {

	Canvas canvas;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<Drawable*> drawables;
	POINT size = { 0 };

public:

	~Screen();
	void Add(Drawable* singleRect);
	void Draw();
	void SetSize(int width, int height);
	POINT Size();
};