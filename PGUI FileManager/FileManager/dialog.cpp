#include "components.h"

Dialog* CreateDialog() {
	Dialog *dialog = new Dialog;
	dialog->x = 0;
	dialog->y = 0;
	dialog->width = 0;
	dialog->height = 0;

	dialog->body = CreateObject();
	dialog->body->backgroundColor = COLOR_DARKCYAN;
	dialog->body->contentColor = COLOR_CYAN;
	SetStroke(dialog->body, STROKE_BOLD);

	dialog->message = CreateObject();
	dialog->message->x = 1;
	dialog->message->y = 1;
	dialog->message->transparent = true;
	dialog->message->contentColor = COLOR_WHITE;
	SetVerticalAlign(dialog->message, ALIGN_CENTER);
	SetHorizontalAlign(dialog->message, ALIGN_CENTER);
	SetParent(dialog->message, dialog->body);

	dialog->button1 = CreateButton();
	SetFocus(dialog->button1, false);
	SetParent(dialog->button1->body, dialog->body);

	dialog->button2 = CreateButton();
	SetFocus(dialog->button2, false);
	SetParent(dialog->button2->body, dialog->body);

	dialog->button3 = CreateButton();
	SetFocus(dialog->button3, false);
	SetParent(dialog->button3->body, dialog->body);

	return dialog;
}

void DestroyDialog(Dialog *&dialog) {
	DestroyButton(dialog->button1);
	DestroyButton(dialog->button2);
	DestroyButton(dialog->button3);
	DestroyObject(dialog->body);
	delete dialog;
	dialog = 0;
}

void SetSize(Dialog *dialog, short width, short height) {
	SetSize(dialog->body, width, height);
	dialog->width = dialog->body->width;
	dialog->height = dialog->body->height;
	SetSize(dialog->message, width - 2, height - 6);
	SetSize(dialog->button1, (width - 8) / 3, 3);
	SetSize(dialog->button2, (width - 8) / 3, 3);
	SetSize(dialog->button3, (width - 8) / 3, 3);
	SetButtons(dialog, dialog->button1->caption->content, dialog->button2->caption->content, dialog->button3->caption->content);
}

void SetPosition(Dialog *dialog, short x, short y) {
	dialog->x = x;
	dialog->y = y;
	dialog->body->x = x;
	dialog->body->y = y;
}

void SetButtons(Dialog *dialog, char *first, char *second, char *third) {
	int buttonCount = 1;
	if (second) buttonCount++;
	if (third) buttonCount++;
	short height = dialog->height - dialog->button1->height - 1;
	short width = dialog->button1->width;
	short offset = (dialog->width - width * buttonCount) / (buttonCount + 1);
	dialog->button2->body->visible = false;
	dialog->button3->body->visible = false;
	SetContent(dialog->button1->caption, first);
	SetContent(dialog->button2->caption, second);
	SetContent(dialog->button3->caption, third);
	SetPosition(dialog->button1, offset, height);
	if (second) {
		dialog->button2->body->visible = true;
		SetPosition(dialog->button2, offset * 2 + width, height);
	}
	if (third) {
		dialog->button3->body->visible = true;
		SetPosition(dialog->button3, offset * 3 + width * 2, height);
	}
}

void ResetButtonFocus(Dialog *dialog) {
	bool f1 = false, f2 = false, f3 = false;
	f3 = dialog->button3->body->visible;
	f2 = dialog->button2->body->visible && !f3;
	f1 = !f2 && !f3;
	SetFocus(dialog->button1, f1);
	SetFocus(dialog->button2, f2);
	SetFocus(dialog->button3, f3);
}