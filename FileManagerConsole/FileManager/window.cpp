#include "components.h"

Window* CreateWindow() {
	Window *window = new Window;
	window->x = 0;
	window->y = 0;
	window->height = 0;
	window->width = 0;

	window->body = CreateObject();
	window->body->backgroundColor = COLOR_DARKBLUE;

	window->leftPath = CreateObject();
	window->leftPath->contentColor = COLOR_DARKRED;
	window->leftPath->backgroundColor = COLOR_YELLOW;
	SetParent(window->leftPath, window->body);

	window->rightPath = CreateObject();
	window->rightPath->contentColor = COLOR_DARKRED;
	window->rightPath->backgroundColor = COLOR_YELLOW;
	SetParent(window->rightPath, window->body);

	window->leftList = CreateViewList();
	SetParent(window->leftList->body, window->body);

	window->rigthList = CreateViewList();
	SetParent(window->rigthList->body, window->body);

	for (int i = 0; i < 5; i++) {
		window->hints[i] = CreateObject();
		SetSize(window->hints[i], 20, 3);
		window->hints[i]->x = 1 + i * (window->hints[i]->width + 1);
		SetVerticalAlign(window->hints[i], ALIGN_CENTER);
		SetHorizontalAlign(window->hints[i], ALIGN_CENTER);
		window->hints[i]->contentColor = COLOR_CYAN;
		window->hints[i]->backgroundColor = COLOR_DARKBLUE;
		SetStroke(window->hints[i], STROKE_THIN);
		SetParent(window->hints[i], window->body);
	}
	SetContent(window->hints[0], " Del - удалить");
	SetContent(window->hints[1], " F2 - копировать");
	SetContent(window->hints[2], " F3 - переместить");
	SetContent(window->hints[3], " F4 - создать");
	SetContent(window->hints[4], " F5 - обновить");

	return window;
}

void DestroyWindow(Window *&window) {
	if (window) return;
	DestroyViewList(window->leftList);
	DestroyViewList(window->rigthList);
	DestroyObject(window->body);
	delete window;
	window = 0;
}

void SetPosition(Window *window, short x, short y) {
	if (!window) return;
	window->x = x;
	window->y = y;
	window->body->x = x;
	window->body->y = y;
}

void SetSize(Window *window, short width, short height) {
	SetSize(window->body, width, height);
	window->width = window->body->width;
	window->height = window->body->height;
	SetSize(window->leftList, (width - 3) / 2, height - 6);
	SetPosition(window->leftList, 1, 5);
	SetSize(window->rigthList, (width - 3) / 2, height - 6);
	SetPosition(window->rigthList, (width - 3) / 2 + 2, 5);
	window->leftPath->x = window->leftList->x;
	window->leftPath->y = window->leftList->body->y - 1;
	window->rightPath->x = window->rigthList->x;
	window->rightPath->y = window->rigthList->body->y - 1;
	SetSize(window->leftPath, window->leftList->width, 1);
	SetSize(window->rightPath, window->rigthList->width, 1);
}
