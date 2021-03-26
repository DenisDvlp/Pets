#pragma once
#include "pseudoGUI.h"
#include "utils.h"

struct Board;
struct Card;
struct Bone;
struct Button;
struct Chip;
struct Infopanel;
struct Dialog;

enum ChipType;
enum InfopanelType;

enum ChipType {
	CHIP_FIRST,
	CHIP_SECOND
};

enum CardType {
	CARD_INFO,
	CARD_CLASSIC
};

//игровая карточка с недвижимостью и услугами
struct Card {
	Object *body;
	Object *caption;
	Object *details;
	char *name;
	int cost;
	short x, y;
	short width, height;
	CardType viewType;
};

Card* CreateCard();
void DestroyCard(Card *&card);
void SetSize(Card *card, short width, short height);
void SetPosition(Card *card, short x, short y);
void SetCost(Card *card, int cost);
void SetName(Card *card, char *name);
void SetCardViewType(Card *card, CardType viewType);
void InitCard(Card *dst, Card *src);
void InitCard(Card *card, char *name, int cost, CardType viewType, Color captionColor, Color cardColor);

//игровая кость
struct Bone {
	Object *body;
	Object *dots;
	unsigned number;
	short x, y;
};

Bone* CreateBone();
void DestroyBone(Bone *&bone);
void SetNumber(Bone *bone, unsigned number);
void SetPosition(Bone *bone, short x, short y);

//кнопка
struct Button {
	Object *body;
	Object *caption;
	bool focused;
	short x, y;
	short width, height;
};

Button* CreateButton();
void DestroyButton(Button *&button);
void SetPosition(Button *button, short x, short y);
void SetSize(Button *button, short width, short height);
void SetFocus(Button *button, bool focused);

//игровая фишка
struct Chip {
	Object *body;
	ChipType type;
	short x, y;
};

Chip* CreateChip();
void DestroyChip(Chip *&chip);
void SetChipType(Chip *chip, ChipType type);
void SetPosition(Chip *chip, short x, short y);

//панель с информацией о клетке
struct Infopanel {
	Dialog *dialog;
	Object *caption;
	Card *card;
	short x, y;
	short width, height;
};

Infopanel* CreateInfopanel();
void DestroyInfopanel(Infopanel *&infopanel);
void SetPosition(Infopanel *infopanel, short x, short y);
void SetSize(Infopanel *infopanel, short width, short height);
void SetInfopanelInfo(Infopanel *infopanel, char *caption, char *message, char *button1, char *button2);

//диалоговое окно с 1,2,3 кнопками
struct Dialog {
	Object *body;
	Object *message;
	Button *button1, *button2, *button3;
	short x, y;
	short width, height;
};

Dialog* CreateDialog();
void DestroyDialog(Dialog *&dialog);
void SetPosition(Dialog *dialog, short x, short y);
void SetSize(Dialog *dialog, short width, short height);
void SetButtons(Dialog *dialog, char *first, char *second = 0, char *third = 0);
void ResetButtonFocus(Dialog *dialog);

//игровое поле
struct Board {
	Object *body;
	Object *players[2];
	Object *plashka;
	Object *manual;
	Card *cards[24];
	Bone *bones[2];
	Button *button;
	Chip *chip[2];
	short x, y;
	short width, height;
};

Board* CreateBoard();
void DestroyBoard(Board *&board);
void SetPosition(Board *board, short x, short y);
void SetCardSize(Board *board, short width, short height);
void SetPlayerBalance(Board *board, short index, short balance);
void SetActivePlayer(Board *board, short index);