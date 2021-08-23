#pragma once
#include "Menu.h"

enum MenuItem {
	ITEM_NONE,
	ITEM_SHOW,
	ITEM_ADD,
	ITEM_BACK,
	ITEM_COLD,
	ITEM_WARM,
	ITEM_DELETE,
	ITEM_SAVE,
	ITEM_LOAD,
	ITEM_EXIT
};

class Interface {

	Item *localRoot;
	Item *root;
	char dialogText[256];
	Color dialogColor;
	Color actionColor;

private:
	int WaitInputWithDialog();
	void Execute(int id);
public:
	void Init(Color menuColor, Color submenuColor, Color aActionColor);
	void Run();
};
