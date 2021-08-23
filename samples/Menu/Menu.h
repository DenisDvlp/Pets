#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

enum Color { COLOR_NONE = 0, BLACK = 8, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW, WHITE };

class Item {

	//fields

	int id = 0;
	char text[256] = { 0 };
	Color color = COLOR_NONE;
	bool choosen = false;
	Item **subitems = nullptr;
	int count = 0;
	HANDLE console = nullptr;

public:

	//destructor
	~Item();
	//getters
	int GetId();
	Color GetColor();
	int GetItemCount();
	Item* GetSubitem(int index);
	//methods
	void Init(char *aText, Color aColor, int aId);
	void Show(int index = 0, int offset = 0);
	void AddSubitem(char *text, Color color, int id);
	void SetChoosen(bool aChoosen);
	void SetChoosenById(int id, bool choosen);
	Item* FindItemById(int aId);
};

//установка цветов консоли по умолчанию
void SetDefaultConsoleColors();
//вывод текста определённого цвета с задним фоном определённого цвета
void ShowText(char *text, Color font, Color background);