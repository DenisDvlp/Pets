#include "actions.h"
#include <windows.h>

void Click(void(*Refresh)(), Button *button) {
	Color tmp = button->body->backgroundColor;
	button->body->backgroundColor = button->body->contentColor;
	Refresh();
	button->body->backgroundColor = tmp;
	Sleep(50);
	Refresh();
}

int ShowDialog(void(*Refresh)(), Dialog *dialog) {
	ResetButtonFocus(dialog);
	if (!dialog->body->parent) return ANSWER_NONE;
	short x = (dialog->body->parent->width - dialog->width) / 2;
	short y = (dialog->body->parent->height - dialog->height) / 2;
	SetPosition(dialog, x, y);
	dialog->body->visible = true;
	int answer = KeyHandler(Refresh, dialog, DispatcheDialog);
	dialog->body->visible = false;
	return answer;
}