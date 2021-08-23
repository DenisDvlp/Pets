#include "animations.h"
#include <windows.h>

void SpinBones(void(*Refresh)(), Board *board, unsigned first, unsigned second) {
	for (int i = 0; i < 17; i++) {
		SetNumber(board->bones[0], rand() % 6 + 1);
		SetNumber(board->bones[1], rand() % 6 + 1);
		Refresh();
		Sleep(7 * i * i / 10);
	}
	SetNumber(board->bones[0], first);
	SetNumber(board->bones[1], second);
	Refresh();
}

void Click(void(*Refresh)(), Button *button) {
	Color tmp = button->body->backgroundColor;
	button->body->backgroundColor = button->body->contentColor;
	Refresh();
	button->body->backgroundColor = tmp;
	Sleep(50);
	Refresh();
}

void ChipMovement(void(*Refresh)(), Board *board, Chip *chip, int start, int count) {
	int finish = start + count;
	for (int i = start; i <= finish; i++) {
		int current = i % 24;
		SetPosition(chip, board->cards[current]->x + 2, board->cards[current]->y + 2);
		Sleep(100);
		Refresh();
	}
}

int ShowInfopanel(void(*Refresh)(), Infopanel *infopanel) {
	int answer = ShowDialog(Refresh, infopanel->dialog);
	switch (answer) {
	case ANSWER_DIALOG_EXIT:
		answer = ANSWER_INFOPANEL_EXIT;
		break;
	case ANSWER_DIALOG_FIRST:
		answer = ANSWER_INFOPANEL_ACCEPT;
		break;
	case ANSWER_DIALOG_SECOND:
		answer = ANSWER_INFOPANEL_DENY;
		break;
	}
	return answer;
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

void ChangeBalance(void(*Refresh)(), Board *board, short index, int from, int to) {
	int delta = (from < to) ? 10 : -10;
	for (int i = from; (from < to) ? i <= to : i >= to; i += delta) {
		SetPlayerBalance(board, index, i);
		Refresh();
	}
	SetPlayerBalance(board, index, to);
	Refresh();
}