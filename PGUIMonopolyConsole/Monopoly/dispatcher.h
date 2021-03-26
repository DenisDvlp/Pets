#pragma once
#include "components.h"
#include "animations.h"
#include <conio.h>

enum Key {
	KEY_ESC = 27,
	KEY_ENTER = 13,
	KEY_SPACE = 32,
	KEY_PRE_ARROW = 224,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_UP = 72,
	KEY_DOWN = 80
};

enum Answer {
	ANSWER_NONE,
	ANSWER_BOARD_EXIT,
	ANSWER_BOARD_THROW,
	ANSWER_INFOPANEL_EXIT,
	ANSWER_INFOPANEL_ACCEPT,
	ANSWER_INFOPANEL_DENY,
	ANSWER_DIALOG_EXIT,
	ANSWER_DIALOG_FIRST,
	ANSWER_DIALOG_SECOND,
	ANSWER_DIALOG_THIRD
};

//ожидает ввода с клавиатуры
int KeyHandler(void(*Refresh)(), void *component, int(*dispatcher)(void(*)(), void*, Key));
//диспатчер возвращает false когда он прекращает обработку
int DispatcherBoard(void(*Refresh)(), void *board, Key key);
int DispatcheDialog(void(*Refresh)(), void *dialog, Key key);