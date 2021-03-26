#include "gamecore.h"

Gamecard* CreateGamecard() {
	Gamecard *gamecard = new Gamecard;
	gamecard->owner = 0;
	gamecard->name = 0;
	gamecard->cost = 0;
	gamecard->type = GAMECARD_START;
	gamecard->cardType = CARD_INFO;
	gamecard->colorCard = COLOR_BLACK;
	gamecard->colorCaption = COLOR_BLACK;
	return gamecard;
}

void DestroyGamecard(Gamecard *&gamecard) {
	DeleteArray(gamecard->name);
	delete[] gamecard;
	gamecard = 0;
}

void InitGamecard(Gamecard *gamecard, char *name, int cost, Color colorCaption, Color colorCard, GamecardType type, CardType cardType) {
	CopyString(gamecard->name, name);
	gamecard->cost = cost;
	gamecard->colorCaption = colorCaption;
	gamecard->colorCard = colorCard;
	gamecard->type = type;
	gamecard->cardType = cardType;
}