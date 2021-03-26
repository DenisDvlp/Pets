#pragma once
#include "pseudoGUI.h"
#include "utils.h"

struct Button;
struct Dialog;
struct Window;

enum ViewListType {
	VIEWLIST_LEFT,
	VIEWLIST_RIGHT
};

//кнопка
struct Button {
	Object *body;
	Object *caption;
	bool focused;
	short x, y;
	short width, height;
};

Button* CreateButton();
void DestroyButton(Button *&button);
void SetPosition(Button *button, short x, short y);
void SetSize(Button *button, short width, short height);
void SetFocus(Button *button, bool focused);

//диалоговое окно с 1,2,3 кнопками
struct Dialog {
	Object *body;
	Object *message;
	Button *button1, *button2, *button3;
	short x, y;
	short width, height;
};

Dialog* CreateDialog();
void DestroyDialog(Dialog *&dialog);
void SetPosition(Dialog *dialog, short x, short y);
void SetSize(Dialog *dialog, short width, short height);
void SetButtons(Dialog *dialog, char *first, char *second = 0, char *third = 0);
void ResetButtonFocus(Dialog *dialog);

//список строк
struct StringList {
	Object *body; // ограничивает отрисовку контента
	Object *content; // контент, представляющий собой список строк
	Object **items;
	short count;
	short selected;
	short x, y;
	short width, height;
	bool focused;
};

StringList* CreateStringList();
void DestroyStringList(StringList *&stringList);
void SetSelected(StringList *stringList, short index);
void AddItem(StringList *stringList, char *string);
void DeleteItem(StringList *stringList, short index);
void InsertItem(StringList *stringList, char *string, short index);
void ClearStringList(StringList *stringList);
void SetPosition(StringList *stringList, short x, short y);
void SetSize(StringList *stringList, short width, short height);
void InitWithStrings(StringList *stringList, Strings *strings);

//список строк
struct ViewList {
	Object *body;
	StringList *stringList;
	short x, y;
	short width, height;
	bool focused;
};

ViewList* CreateViewList();
void DestroyViewList(ViewList *&viewList);
void SetFocused(ViewList *viewList, bool focused);
void SetPosition(ViewList *viewList, short x, short y);
void SetSize(ViewList *viewList, short width, short height);

//главное окно
struct Window {
	Object *body;
	Object *hints[5];
	Object *leftPath, *rightPath;
	ViewList *leftList, *rigthList;
	ViewListType focusedList;
	short selectedLeft, selectedRight;
	short x, y;
	short width, height;
};

Window* CreateWindow();
void DestroyWindow(Window *&window);
void SetPosition(Window *window, short x, short y);
void SetSize(Window *window, short width, short height);