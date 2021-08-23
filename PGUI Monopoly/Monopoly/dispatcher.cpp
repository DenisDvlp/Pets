#include "dispatcher.h"

//ожидает ввода с клавиатуры
int KeyHandler(void(*Refresh)(), void *component, int(*dispatcher)(void(*)(), void*, Key)) {
	int i = 0;
	int answer = ANSWER_NONE;
	do {
		Refresh();
		i = _getch();
		if(i == KEY_PRE_ARROW)
			i = _getch();
		answer = dispatcher(Refresh, component, Key(i));
	} while (answer == ANSWER_NONE);
	Refresh();
	return answer;
}

//диспатчер возвращает false когда он прекращает обработку
int DispatcherBoard(void(*Refresh)(), void *component, Key key) {
	Board *board = (Board*)component;
	switch (key) {
	case KEY_ESC:
		return ANSWER_BOARD_EXIT;
		break;
	case KEY_ENTER:
		Click(Refresh, board->button);
		int first = rand() % 6 + 1;
		int second = rand() % 6 + 1;
		SpinBones(Refresh, board, first, second);
		return ANSWER_BOARD_THROW;
		break;
	}
	return ANSWER_NONE;
}

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