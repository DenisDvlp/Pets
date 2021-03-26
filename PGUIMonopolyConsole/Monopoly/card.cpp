#include "components.h"

void SetCaption(Card *card);

Card* CreateCard() {
	Card *card = new Card;
	card->x = 0;
	card->y = 0;
	card->width = 0;
	card->height = 0;
	card->cost = 0;
	card->name = 0;
	card->viewType = CARD_INFO;
	card->body = CreateObject();
	card->caption = CreateObject();
	card->caption->x = 1;
	card->caption->y = 1;
	card->caption->transparent = true;
	SetParent(card->caption, card->body);
	card->details = CreateObject();
	card->details->x = 2;
	card->details->y = 4;
	SetHorizontalAlign(card->caption, ALIGN_CENTER);
	SetFilling(card->details, CHAR_FILL_LIGHT);
	SetParent(card->details, card->body);
	return card;
}

void DestroyCard(Card *&card) {
	DeleteArray(card->name);
	DestroyObject(card->body);
	delete card;
	card = 0;
}

void SetSize(Card *card, short width, short height) {
	SetSize(card->body, width, height);
	card->width = card->body->width;
	card->height = card->body->height;
	SetSize(card->caption, width - 2, height - 2);
	SetSize(card->details, width - 4, height - 5);
}

void SetPosition(Card *card, short x, short y) {
	card->x = x;
	card->y = y;
	card->body->x = x;
	card->body->y = y;
}

void SetCost(Card *card, int cost) {
	card->cost = cost;
	SetCaption(card);
}

void SetName(Card *card, char *name) {
	CopyString(card->name, name);
	SetCaption(card);
}

void SetCaption(Card *card) {
	char *text = 0;
	char *number = 0;
	if (card->cost) {
		number = IntToStr(card->cost);
		text = ConcatStrings(3, card->name, "\n", number);
	} else
		CopyString(text, card->name);
	SetContent(card->caption, text);
	DeleteArray(number);
	DeleteArray(text);
}

void SetCardViewType(Card *card, CardType viewType) {
	card->viewType = viewType;
	if (card->viewType == CARD_INFO) {
		card->details->visible = false;
		SetVerticalAlign(card->caption, ALIGN_CENTER);
	}
	if (card->viewType == CARD_CLASSIC) {
		card->details->visible = true;
		SetVerticalAlign(card->caption, ALIGN_TOP);
	}
}

void InitCard(Card *dst, Card *src) {
	InitCard(dst, src->name, src->cost, src->viewType, src->caption->contentColor, src->body->backgroundColor);
}

void InitCard(Card *card, char *name, int cost, CardType viewType, Color captionColor, Color cardColor) {
	SetName(card, name);
	SetCost(card, cost);
	SetCardViewType(card, viewType);
	card->body->backgroundColor = cardColor;
	card->details->contentColor = cardColor;
	card->caption->contentColor = captionColor;
}