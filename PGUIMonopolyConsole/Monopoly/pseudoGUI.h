#pragma once

enum GraphicChar {
	CHAR_FULL = -37,
	CHAR_FULL_TOP = -33,
	CHAR_FULL_BOT = -36,

	CHAR_STICK_VERT = -77,
	CHAR_STICK_HOR = -60,
	CHAR_STICK_TOP_LEFT = -38,
	CHAR_STICK_TOP_RIGHT = -65,
	CHAR_STICK_BOT_LEFT = -64,
	CHAR_STICK_BOT_RIGHT = -39,

	CHAR_DSTICK_VERT = -70,
	CHAR_DSTICK_HOR = -51,
	CHAR_DSTICK_TOP_LEFT = -55,
	CHAR_DSTICK_TOP_RIGHT = -69,
	CHAR_DSTICK_BOT_LEFT = -56,
	CHAR_DSTICK_BOT_RIGHT = -68,

	CHAR_FILL_LIGHT = -80,
	CHAR_FILL_MEDIUM = -79,
	CHAR_FILL_DARK = -78
};

enum Color {
	COLOR_BLACK,
	COLOR_DARKBLUE,
	COLOR_DARKGREEN,
	COLOR_DARKCYAN,
	COLOR_DARKRED,
	COLOR_DARKPURPLE,
	COLOR_DARKYELLOW,
	COLOR_GRAY,
	COLOR_DARKGRAY,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_PURPLE,
	COLOR_YELLOW,
	COLOR_WHITE
};

enum StrokeType {
	STROKE_NONE,
	STROKE_BOLD,
	STROKE_SEMIBOLD,
	STROKE_THIN,
};

enum Align {
	ALIGN_TOP = 0,
	ALIGN_LEFT = 0,
	ALIGN_CENTER = 1,
	ALIGN_BOTTOM = 2,
	ALIGN_RIGHT = 2
};

//объект, который отрисовывается на экране
struct Object {
	short x, y; //изменяется напрямую
	short width, height; //изменяется через функцию SetSize
	Color contentColor, backgroundColor; //изменяется напрямую
	char *content; //изменяется через функцию SetContent
	char fill; //изменяется через функцию SetFilling
	StrokeType stroke; //изменяется через функцию SetStroke
	Align contentHorizAlign, contentVertAlign;
	bool autosize; //изменяется через функцию SetAutisize
	bool visible; //изменяется напрямую
	bool transparent; //изменяется напрямую
	bool clip; //изменяется напрямую
	char **body; //не изменяется
	unsigned short childrenCount; //не изменяется
	Object **children; //не изменяется
	Object *parent; //изменяется через функцию SetParent
};

//функционал объекта
Object* CreateObject();
void DestroyObject(Object *object);
void SetParent(Object *object, Object *parent);
void SetSize(Object *object, short width, short height);
void SetStroke(Object *object, StrokeType strokeType);
void SetHorizontalAlign(Object *object, Align align);
void SetVerticalAlign(Object *object, Align align);
void SetFilling(Object *object, char filling);
void SetContent(Object *object, char *content);
void SetAutosize(Object *object, bool autosize);
int GetAbsoluteX(Object *object);
int GetAbsoluteY(Object *object);

//отвечает за работу экрана
struct Display {
	Object *mainParent; //главный объект, который является родительским для всех
	short width, height;
	void (*Refresh)();
	void (*Clear)();
};

Display CreateDisplay(short  width, short  height, unsigned char pixelSize, Color color);
void DestroyDisplay();