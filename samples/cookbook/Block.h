#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::string;
using std::find;
using std::for_each;

#define	ALIGN_NONE 0	//00000
#define	ALIGN_LEFT 1	//00001
#define	ALIGN_RIGHT 2	//00010
#define	ALIGN_TOP 4	//00100
#define	ALIGN_BOTTOM 8	//01000
#define	ALIGN_CENTER 16//10000

#define	ALIGN_HORIZONTAL (ALIGN_LEFT | ALIGN_RIGHT)//00011
#define	ALIGN_VERTICAL (ALIGN_TOP | ALIGN_BOTTOM)//01100

#define	ALIGN_TOP_LEFT (ALIGN_LEFT | ALIGN_TOP)//00101
#define	ALIGN_TOP_RIGHT (ALIGN_RIGHT | ALIGN_TOP)//00110
#define	ALIGN_BOTTOM_LEFT (ALIGN_LEFT | ALIGN_BOTTOM)//01001
#define	ALIGN_BOTTOM_RIGHT (ALIGN_RIGHT | ALIGN_BOTTOM)//01010

#define	ALIGN_CONTENT (ALIGN_HORIZONTAL | ALIGN_VERTICAL)//01111

#define	ALIGN_CONTENT_LEFT (ALIGN_LEFT | ALIGN_VERTICAL)//01101
#define	ALIGN_CONTENT_RIGHT (ALIGN_RIGHT | ALIGN_VERTICAL)//01110
#define	ALIGN_CONTENT_TOP (ALIGN_TOP | ALIGN_HORIZONTAL)//00111
#define	ALIGN_CONTENT_BOTTOM (ALIGN_BOTTOM | ALIGN_HORIZONTAL)//01011

#define HASFLAG(flags, flag) (flags & flag == flag)

#define COLOR_TRANSPARENT = -1
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
typedef int ALIGN;

class Block {

	POINT position = { 0 };
	POINT size = { 0 };
	RECT margin = { 0 };
	RECT padding = { 0 };
	ALIGN align = ALIGN_NONE;
	COLOR color = COLOR_BLACK;
	COLOR background = COLOR_BLACK;
	bool visible = true;
	bool clip = false;
	bool autosize = true;
	string content;
	Block *parent = nullptr;
	vector<Block*> children;

	//SET

	void SetParent(Block *parent);

	void SetPosition(POINT position);
	void SetX(int x);
	void SetY(int y);

	void SetSize(POINT size);
	void SetWidth(int width);
	void SetHeight(int height);

	void SetMargin(RECT margin);
	void SetMargin(int margin);
	void SetMarginLeft(int left);
	void SetMarginTop(int top);
	void SetMarginRight(int right);
	void SetMarginBottom(int bottom);

	void SetPadding(RECT padding);
	void SetPadding(int padding);
	void SetPaddingLeft(int left);
	void SetPaddingTop(int top);
	void SetPaddingRight(int right);
	void SetPaddingBottom(int bottom);

	void SetAlign(ALIGN value);
	void SetContent(string content);
	void SetColor(COLOR color);
	void SetBackground(COLOR background);
	void SetVisible(bool value);
	void SetClip(bool value);
	void SetAutosize(bool value);

	//GET

	Block* Parent();
	vector<Block*> Children();
	int ChildrenCount();
	Block* Child(int index);
	Block* operator[](int index);
	POINT Position();
	POINT PositionAbsolute();
	POINT Size();
	RECT Margin();
	RECT Padding();
	ALIGN Align();
	string Content();
	COLOR Color();
	COLOR Background();
	bool Visible();
	bool Clip();
	bool Autosize();

	//FUNC

	void BringToFront();
	void SendToBack();
	void Realign();
	void Draw();
};
