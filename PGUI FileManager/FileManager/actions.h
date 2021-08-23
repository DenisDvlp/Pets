#pragma once
#include "components.h"

enum Key {
	KEY_ESC = 27,
	KEY_ENTER = 13,
	KEY_TAB = 9,
	KEY_SPACE = 32,
	KEY_BACK = 8,
	KEY_PRE_KEY = 224,
	KEY_PRE_KEY2 = 0,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_HOME = 71,
	KEY_END = 79,
	KEY_PGUP = 73,
	KEY_PGDOWN = 81,
	KEY_DEL = 83,
	KEY_F2 = 60,
	KEY_F3 = 61,
	KEY_F4 = 62,
	KEY_F5 = 63
};

enum Answer {
	ANSWER_NONE,
	ANSWER_VIEWLIST_EXIT,
	ANSWER_VIEWLIST_CHANGE,
	ANSWER_VIEWLIST_SELECT,
	ANSWER_VIEWLIST_DELETE,
	ANSWER_VIEWLIST_COPY,
	ANSWER_VIEWLIST_MOVE,
	ANSWER_VIEWLIST_CREATE,
	ANSWER_VIEWLIST_TOPARENT,
	ANSWER_VIEWLIST_REFRESH,
	ANSWER_DIALOG_EXIT,
	ANSWER_DIALOG_FIRST,
	ANSWER_DIALOG_SECOND,
	ANSWER_DIALOG_THIRD
};

//ожидает ввода с клавиатуры
int KeyHandler(void(*Refresh)(), void *component, int(*dispatcher)(void(*)(), void*, Key));
//диспатчер возвращает false когда он прекращает обработку
int DispatcheDialog(void(*Refresh)(), void *dialog, Key key);
int DispatcheViewList(void(*Refresh)(), void *viewlist, Key key);

void Click(void(*Refresh)(), Button *button);
int ShowDialog(void(*Refresh)(), Dialog *dialog);