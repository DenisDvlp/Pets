#include "components.h"

Button* CreateButton() {
	Button *button = new Button;
	button->x = 0;
	button->y = 0;
	button->width = 0;
	button->height = 0;
	button->body = CreateObject();
	button->body->backgroundColor = COLOR_DARKRED;
	button->body->contentColor = COLOR_RED;
	button->caption = CreateObject();
	button->caption->contentColor = COLOR_CYAN;
	button->caption->transparent = true;
	SetHorizontalAlign(button->caption, ALIGN_CENTER);
	SetVerticalAlign(button->caption, ALIGN_CENTER);
	SetParent(button->caption, button->body);
	SetContent(button->caption, "кнопка");
	SetFocus(button, true);
	return button;
}

void DestroyButton(Button *&button) {
	DestroyObject(button->body);
	delete button;
	button = 0;
}

void SetPosition(Button *button, short x, short y) {
	button->x = x;
	button->y = y;
	button->body->x = x;
	button->body->y = y;
}

void SetSize(Button *button, short width, short height) {
	SetSize(button->body, width, height);
	button->width = button->body->width;
	button->height = button->body->height;
	SetSize(button->caption, width, height);
}

void SetFocus(Button *button, bool focused) {
	button->focused = focused;
	if (focused)
		SetStroke(button->body, STROKE_SEMIBOLD);
	else
		SetStroke(button->body, STROKE_NONE);
}
