#include "components.h"

ViewList* CreateViewList() {
	ViewList *view = new ViewList;
	view->x = 0;
	view->y = 0;
	view->height = 0;
	view->width = 0;
	view->focused = false;

	view->body = CreateObject();
	view->body->backgroundColor = COLOR_DARKCYAN;
	view->body->contentColor = COLOR_CYAN;

	view->stringList = CreateStringList();
	view->stringList->body->transparent = true;
	SetPosition(view->stringList, 1, 1);
	SetParent(view->stringList->body, view->body);

	SetFocused(view, false);
	return view;
}

void DestroyViewList(ViewList *&viewList) {
	if (viewList) return;
	DestroyStringList(viewList->stringList);
	DestroyObject(viewList->body);
	delete viewList;
	viewList = 0;
}

void SetPosition(ViewList *viewList, short x, short y) {
	if (!viewList) return;
	viewList->x = x;
	viewList->y = y;
	viewList->body->x = x;
	viewList->body->y = y;
}

void SetSize(ViewList *viewList, short width, short height) {
	SetSize(viewList->body, width, height);
	viewList->width = viewList->body->width;
	viewList->height = viewList->body->height;
	SetSize(viewList->stringList, width - 2, height - 2);
}

void SetFocused(ViewList *viewList, bool focused) {
	if (!viewList) return;
	viewList->focused = focused;
	if (focused)
		SetStroke(viewList->body, STROKE_BOLD);
	else
		SetStroke(viewList->body, STROKE_SEMIBOLD);
}