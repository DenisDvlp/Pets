#pragma once
#include "pseudoGUI.h"
#include "utils.h"

struct Card {
	Object *body;
	Object *caption;
	Object *details;
	char *name;
	int cost;
	short x, y;
	unsigned short width, height;
};

Card* CreateCard();
void DestroyCard(Card *&card);
void SetSize(Card *card, unsigned short width, unsigned short height);
void SetPosition(Card *card, short x, short y);
void SetCost(Card *card, int cost);
void SetName(Card *card, char *name);

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