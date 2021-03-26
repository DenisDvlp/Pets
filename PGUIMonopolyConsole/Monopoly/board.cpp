#include "components.h"

Board* CreateBoard() {
	Color colorBoard = COLOR_DARKGREEN;

	Board *board = new Board;
	board->x = 0;
	board->y = 0;

	board->body = CreateObject();
	board->body->backgroundColor = colorBoard;

	for (int i = 0; i < 24; i++) {
		board->cards[i] = CreateCard();
		Card *card = board->cards[i];
		card->body->contentColor = colorBoard;
		SetStroke(card->body, STROKE_BOLD);
		card->details->backgroundColor = COLOR_GRAY;
	}
	for (int i = 0; i < 5; i++) {
		SetParent(board->cards[i + 1]->body, board->body);
		SetParent(board->cards[17 - i]->body, board->body);
	}
	for (int i = 0; i < 7; i++) {
		SetParent(board->cards[i + 6]->body, board->body);
		SetParent(board->cards[(i + 18) % 24]->body, board->body);
	}
	for (int i = 0; i < 2; i++) {
		board->bones[i] = CreateBone();
		SetParent(board->bones[i]->body, board->body);
		SetNumber(board->bones[i], rand() % 7);

		board->chip[i] = CreateChip();
		board->chip[i]->body->contentColor = COLOR_PURPLE;
		board->chip[i]->body->backgroundColor = COLOR_DARKPURPLE;
		SetParent(board->chip[i]->body, board->body);
	}
	SetChipType(board->chip[0], CHIP_FIRST);
	SetChipType(board->chip[1], CHIP_SECOND);

	board->button = CreateButton();
	SetSize(board->button, 25, 5);
	SetContent(board->button->caption, "бросить кости");
	SetParent(board->button->body, board->body);

	board->players[0] = CreateObject();
	board->players[0]->transparent = true;
	SetAutosize(board->players[0], true);
	board->players[0]->contentColor = COLOR_YELLOW;
	board->players[0]->backgroundColor = COLOR_DARKYELLOW;
	SetSize(board->players[0], 40, 1); 
	SetPlayerBalance(board, 0, 0);
	SetParent(board->players[0], board->body);

	board->players[1] = CreateObject();
	board->players[1]->transparent = true;
	SetAutosize(board->players[1], true);
	board->players[1]->contentColor = COLOR_YELLOW;
	board->players[1]->backgroundColor = COLOR_DARKYELLOW;
	SetSize(board->players[1], 40, 1);
	SetPlayerBalance(board, 1, 0);
	SetParent(board->players[1], board->body);

	board->plashka = CreateObject();
	board->plashka->contentColor = COLOR_GREEN;
	board->plashka->transparent = true;
	SetContent(board->plashka,
		"разработчик:   петров денис анатольевич\n"
		"преподаватель: самотой дмитрий николаевич\n"
		"группа 28пр11\n"
		"врем€ разработки - 3 недели\n"
		"окт€брь 2016");
	SetHorizontalAlign(board->plashka, ALIGN_RIGHT);
	SetAutosize(board->plashka, true);
	SetParent(board->plashka, board->body);

	board->manual = CreateObject();
	board->manual->contentColor = COLOR_CYAN;
	board->manual->transparent = true;
	SetContent(board->manual,
		"esc - выход/отмена/закрыть окно\n"
		"enter - нажатие на выбранную кнопку\n"
		"стрелки влево/вправо - выбор кнопки\n");
	SetAutosize(board->manual, true);
	SetParent(board->manual, board->body);

	return board;
}

void DestroyBoard(Board *&board) {
	for (int i = 0; i < 24; i++)
		DestroyCard(board->cards[i]);
	for (int i = 0; i < 2; i++) {
		DestroyChip(board->chip[i]);
		DestroyBone(board->bones[i]);
	}
	DestroyButton(board->button);
	DestroyObject(board->body);
	delete board;
	board = 0;
}

void SetPosition(Board *board, short x, short y) {
	board->x = x;
	board->y = y;
	board->body->x = x;
	board->body->y = y;
}

void SetCardSize(Board *board, short width, short height) {
	int bodyWidth = (width - 2) * 7 + 8,
		bodyHeight = (height - 2) * 7 + 8;
	SetSize(board->body, bodyWidth, bodyHeight);
	board->width = board->body->width;
	board->height = board->body->height;
	for (int i = 0; i < 24; i++)
		SetSize(board->cards[i], width, height);
	for (int i = 0; i < 6; i++) {
		SetPosition(board->cards[i], 0, (6 - i) * (height - 1));
		SetPosition(board->cards[i + 6], i * (width - 1), 0);
		SetPosition(board->cards[i + 12], 6 * (width - 1), i * (height - 1));
		SetPosition(board->cards[i + 18], (6 - i) * (width - 1), 6 * (height - 1));
	}
	SetPosition(board->bones[0], width + 2, board->cards[1]->y - 1);
	SetPosition(board->bones[1], width * 2 + 1, board->cards[1]->y - 1);
	SetPosition(board->button, bodyWidth / 2 + (bodyWidth / 2 - board->button->width - width) / 2, board->cards[1]->y);
	SetPosition(board->chip[0], board->cards[0]->x + 2, board->cards[0]->y + 2);
	SetPosition(board->chip[1], board->cards[0]->x + 2, board->cards[0]->y + 2);
	board->players[0]->x = width + 1;
	board->players[0]->y = height + 1;
	board->players[1]->x = width + 1;
	board->players[1]->y = height + 3;
	board->plashka->x = bodyWidth - width - board->plashka->width - 1;
	board->plashka->y = height + 1;
	board->manual->x = width + 1;
	board->manual->y = board->bones[0]->y - board->manual->height - 1;
}

void SetPlayerBalance(Board *board, short index, short balance) {
	char *number = IntToStr(balance);
	char *current = IntToStr(index + 1);
	char *text = ConcatStrings(4, "игрок ", current, ". баланс: ", number);
	SetContent(board->players[index], text);
	DeleteArray(text);
	DeleteArray(number);
	DeleteArray(current);
}

void SetActivePlayer(Board *board, short index) {
	board->players[index]->transparent = false;
	board->players[(index + 1) % 2]->transparent = true;
}