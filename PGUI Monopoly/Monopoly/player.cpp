#include "gamecore.h"

void DeleteGamecardList(Player *player) {
	if (player->gamecards)
		delete[] player->gamecards;
}

Player* CreatePlayer() {
	Player *player = new Player;
	player->balance = 0;
	player->currentCard = 0;
	player->gamecards = 0;
	player->gamecardCount = 0;
	player->jailCount = 0;
	return player;
}

void DestroyPlayer(Player *&player) {
	DeleteGamecardList(player);
	delete[] player;
	player = 0;
}

void AddCard(Player *player, Gamecard *card) {
	if (!card) return;
	Gamecard **list = new Gamecard*[player->gamecardCount + 1];
	for(int i = 0; i < player->gamecardCount; i++)
		list[i] = player->gamecards[i];
	list[player->gamecardCount++] = card;
	DeleteGamecardList(player);
	player->gamecards = list;
	card->owner = player;
}

void DeleteCard(Player *player, Gamecard *card) {
	if (!card || !player->gamecardCount) return;
	int index = -1;
	for (int i = 0; i < player->gamecardCount; i++)
		if (card == player->gamecards[i]) {
			index = i;
			break;
		}
	if (index < 0) return;
	Gamecard **list = 0;
	if(player->gamecardCount - 1 > 0)
		list = new Gamecard*[player->gamecardCount - 1];
	for (int i = 0, j = 0; i < player->gamecardCount; i++)
		if(i != index)
			list[j++] = player->gamecards[i];
	player->gamecardCount--;
	DeleteGamecardList(player);
	player->gamecards = list;
	card->owner = 0;
}

void InitPlayer(Player *player, short currentCard, int balance) {
	player->currentCard = currentCard;
	player->balance = balance;
}