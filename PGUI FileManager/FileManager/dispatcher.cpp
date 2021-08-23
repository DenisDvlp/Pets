#include "actions.h"
#include <conio.h>

//ожидает ввода с клавиатуры
int KeyHandler(void(*Refresh)(), void *component, int(*dispatcher)(void(*)(), void*, Key)) {
	int i = 0;
	int answer = ANSWER_NONE;
	do {
		Refresh();
		i = _getch();
		if(i == KEY_PRE_KEY || i == KEY_PRE_KEY2)
			i = _getch();
		answer = dispatcher(Refresh, component, Key(i));
	} while (answer == ANSWER_NONE);
	Refresh();
	return answer;
}

//диспатчер возвращает false когда он прекращает обработку

int DispatcheDialog(void(*Refresh)(), void *component, Key key) {
	Dialog *dialog = (Dialog*)component;
	int answer = ANSWER_NONE;
	bool f1 = false, f2 = false, f3 = false;
	switch (key) {
	case KEY_ESC:
		return ANSWER_DIALOG_EXIT;
	case KEY_ENTER:
		if (dialog->button1->focused) {
			Click(Refresh, dialog->button1);
			answer = ANSWER_DIALOG_FIRST;
		} else
		if (dialog->button2->focused) {
			Click(Refresh, dialog->button2);
			answer = ANSWER_DIALOG_SECOND;
		} else
		if (dialog->button3->focused) {
			Click(Refresh, dialog->button3);
			answer = ANSWER_DIALOG_THIRD;
		}
		return answer;
	case KEY_LEFT:
		f1 = dialog->button1->focused || dialog->button2->focused;
		f2 = dialog->button3->focused;
		break;
	case KEY_RIGHT:
		f2 = dialog->button2->body->visible && dialog->button1->focused || !dialog->button3->body->visible;
		f3 = dialog->button3->body->visible && (dialog->button2->focused || dialog->button3->focused);
		break;
	}
	if (key == KEY_LEFT || key == KEY_RIGHT) {
		SetFocus(dialog->button1, f1);
		SetFocus(dialog->button2, f2);
		SetFocus(dialog->button3, f3);
	}
	return ANSWER_NONE;
}

int DispatcheViewList(void(*Refresh)(), void *component, Key key) {
	ViewList *viewlist = (ViewList*)component;
	int index = 0;
	switch (key) {
	case KEY_UP:
		SetSelected(viewlist->stringList, viewlist->stringList->selected - 1);
		break;
	case KEY_DOWN:
		SetSelected(viewlist->stringList, viewlist->stringList->selected + 1);
		break;
	case KEY_HOME:
		SetSelected(viewlist->stringList, 0);
		break;
	case KEY_END:
		SetSelected(viewlist->stringList, viewlist->stringList->count - 1);
		break;
	case KEY_PGUP:
		index = viewlist->stringList->selected - viewlist->stringList->height;
		if (index < 0) index = 0;
		SetSelected(viewlist->stringList, index);
		break;
	case KEY_PGDOWN:
		index = viewlist->stringList->selected + viewlist->stringList->height;
		if (index >= viewlist->stringList->count) index = viewlist->stringList->count - 1;
		SetSelected(viewlist->stringList, index);
		break;
	case KEY_BACK:
		return ANSWER_VIEWLIST_TOPARENT;
	case KEY_ENTER:
		return ANSWER_VIEWLIST_SELECT;
	case KEY_TAB:
		return ANSWER_VIEWLIST_CHANGE;
	case KEY_ESC:
		return ANSWER_VIEWLIST_EXIT;
	case KEY_DEL:
		return ANSWER_VIEWLIST_DELETE;
	case KEY_F2:
		return ANSWER_VIEWLIST_COPY;
	case KEY_F3:
		return ANSWER_VIEWLIST_MOVE;
	case KEY_F4:
		return ANSWER_VIEWLIST_CREATE;
	case KEY_F5:
		return ANSWER_VIEWLIST_REFRESH;
	}
	return ANSWER_NONE;
}