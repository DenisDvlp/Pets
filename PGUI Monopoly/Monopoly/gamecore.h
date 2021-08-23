#pragma once
#include "utils.h"
#include "pseudoGUI.h"
#include "components.h"

struct Core;
struct Player;
struct Gamecard;

enum GamecardType;

enum GamecardType {
	GAMECARD_START,
	GAMECARD_REST,
	GAMECARD_JAIL,
	GAMECARD_BONUS,
	GAMECARD_INFO,
	GAMECARD_COMMON,
	GAMECARD_PLUS10,
	GAMECARD_MINUS10,
	GAMECARD_PRIVATE
};

struct Core {
	char *bonus[5];
	char *info[5];
	char *plusminus[2];
	Player *players[2];
	Gamecard *gamecards[24];
	const unsigned short playerCount = 2;
	const unsigned short gamecardCount = 24;
	unsigned short currentPlayerIndex;
	int startMoney;// деньги на старте
	int lapMoney; // деньги зя старт
};

Core* CreateCore();
void DestroyCore(Core *&core);

struct Player {
	Gamecard **gamecards;
	unsigned short gamecardCount;
	short currentCard;
	int balance;
	int jailCount = 0;
};

Player* CreatePlayer();
void DestroyPlayer(Player *&player);
void AddCard(Player *player, Gamecard *card);
void DeleteCard(Player *player, Gamecard *card);
void InitPlayer(Player *player, short currentCard, int balance);

struct Gamecard {
	char *name;
	int cost;
	GamecardType type;
	CardType cardType;
	Color colorCard;
	Color colorCaption;
	Player *owner;
};

Gamecard* CreateGamecard();
void DestroyGamecard(Gamecard *&gamecard);
void InitGamecard(Gamecard *gamecard, char *name, int cost, Color colorCaption, Color colorCard, GamecardType type, CardType cardType);