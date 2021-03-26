#include "components.h"

StringList* CreateStringList() {
	StringList *view = new StringList;
	view->x = 0;
	view->y = 0;
	view->height = 0;
	view->width = 0;
	view->items = 0;
	view->count = 0;
	view->selected = 0;
	view->focused = false;

	view->body = CreateObject();
	view->body->clip = true;
	view->body->backgroundColor = COLOR_DARKCYAN;

	view->content = CreateObject();
	view->content->transparent = true;
	SetParent(view->content, view->body);

	return view;
}

void DestroyStringList(StringList *&stringList) {
	if (stringList) return;
	ClearStringList(stringList);
	DestroyObject(stringList->body);
	delete stringList;
	stringList = 0;
}

void SetSelected(StringList *stringList, short index) {
	if (!stringList || index < 0 || index >= stringList->count) return;
	stringList->items[stringList->selected]->transparent = true;
	stringList->items[index]->transparent = false;
	stringList->selected = index;
	if (stringList->content->y + index >= stringList->body->height)
		stringList->content->y = stringList->body->height - index - 1;
	else
		if (index < -stringList->content->y)
			stringList->content->y = -index;
}

void AddItem(StringList *stringList, char *string) {
	if (!stringList) return;
	InsertItem(stringList, string, stringList->count);
}

void DeleteItem(StringList *stringList, short index) {
	if (!stringList) return;
	int count = stringList->count;
	if (index < 0 || index >= count) return;
	Object **list = 0;
	if (count - 1) list = new Object*[count - 1];
	for (int i = 0, j = 0; i < count; i++)
		if (index != i)
			list[j++] = stringList->items[i];
		else
			DestroyObject(stringList->items[i]);
	if (stringList->items)
		delete[] stringList->items;
	stringList->items = list;
	stringList->count = count - 1;
	if (stringList->selected >= stringList->count)
		stringList->selected = stringList->count - 1;
	if (stringList->selected < 0)
		stringList->selected = 0;
	SetSize(stringList->content, stringList->body->width, stringList->count);
}

void InsertItem(StringList *stringList, char *string, short index) {
	if (!stringList) return;
	int count = stringList->count + 1;
	if (!string || index < 0 || index >= count) return;
	Object **list = new Object*[count];
	for (int i = 0, j = 0; i < count; i++) {
		if (index == i) {
			list[i] = CreateObject();
			SetSize(list[i], stringList->content->width, 1);
			SetContent(list[i], string);
			list[i]->contentColor = COLOR_YELLOW;
			list[i]->backgroundColor = COLOR_DARKRED;
			list[i]->transparent = true;
			SetParent(list[i], stringList->content);
		}
		else
			list[i] = stringList->items[j++];
		list[i]->y = i;
	}
	if (stringList->items)
		delete[] stringList->items;
	stringList->items = list;
	stringList->count = count;
	SetSize(stringList->content, stringList->body->width, stringList->count);
}

void ClearStringList(StringList *stringList) {
	if (!stringList || !stringList->count) return;
	for (int i = 0; i < stringList->count; i++)
		DestroyObject(stringList->items[i]);
	if (stringList->items)
		delete[] stringList->items;
	stringList->items = 0;
	stringList->count = 0;
	stringList->selected = 0;
}

void SetPosition(StringList *stringList, short x, short y) {
	if (!stringList) return;
	stringList->x = x;
	stringList->y = y;
	stringList->body->x = x;
	stringList->body->y = y;
}

void SetSize(StringList *stringList, short width, short height) {
	if (!stringList) return;
	SetSize(stringList->body, width, height);
	stringList->width = stringList->body->width;
	stringList->height = stringList->body->height;
	SetSize(stringList->content, width, stringList->count);
	for (int i = 0; i < stringList->count; i++)
		SetSize(stringList->items[i], width, 1);
}

void InitWithStrings(StringList *stringList, Strings *strings) {
	if (!stringList) return;
	ClearStringList(stringList);
	for (int i = 0; i < SS.Count(strings); i++)
		AddItem(stringList, strings->items[i]);
}