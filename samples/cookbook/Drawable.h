#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
using std::vector;
using std::string;

#define COLOR_TRANSPARENT -1
#define COLOR_BLACK 0
#define COLOR_DARKBLUE 1
#define COLOR_DARKGREEN 2
#define COLOR_DARKCYAN 3
#define COLOR_DARKRED 4
#define COLOR_DARKPURPLE 5
#define COLOR_DARKYELLOW 6
#define COLOR_GRAY 7
#define COLOR_DARKGRAY 8
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_CYAN 11
#define COLOR_RED 12
#define COLOR_PURPLE 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

typedef int COLOR;

class Drawable {

	POINT position = { 0 };
	POINT size = { 0 };
	COLOR color = COLOR_WHITE;
	COLOR background = COLOR_BLACK;
	bool visible = true;
	bool autosize = true;
	string content;

	POINT TextDrawSize(string text);

public:

	//SET

	void SetPosition(POINT position);
	void SetX(int x);
	void SetY(int y);

	void SetSize(POINT size);
	void SetWidth(int width);
	void SetHeight(int height);

	void SetContent(string content);
	void SetColor(COLOR color);
	void SetBackground(COLOR background);
	void SetVisible(bool value);
	void SetAutosize(bool value);

	//GET

	POINT Position();
	POINT Size();
	string Content();
	COLOR Color();
	COLOR Background();
	bool Visible();
	bool Autosize();
};
