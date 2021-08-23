#include "Menu.h"
//destructor

Item::~Item() {
	for (int i = 0; i < count; i++)
		delete subitems[i];
	delete[] subitems;
}

//getters

int Item::GetId() {
	return id;
}

Color Item::GetColor() {
	return color;
}

int Item::GetItemCount() {
	return count;
}

Item* Item::GetSubitem(int index) {
	if (index < 0 || index >= count)
		return nullptr;
	return subitems[index];
}

//methods

void Item::Init(char *aText, Color aColor, int aId) {
	id = aId;
	strcpy_s(text, aText);
	color = aColor;
	choosen = false;
	subitems = NULL;
	count = 0;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Item::Show(int index, int offset) {
	if (strlen(text)) {
		SetConsoleTextAttribute(console, ((choosen ? color : BLACK) - 8) * 16 + color);
		for (int i = 0; i < offset; i++)
			cout << " ";
		cout << index << ". " << text << "\n";
	}
	else
		offset -= 3;
	if (choosen)
		for (int i = 0; i < count; i++)
			subitems[i]->Show(i + 1, offset + 3);
}

void Item::AddSubitem(char *text, Color color, int id) {
	Item **list = new Item*[count + 1];
	for (int i = 0; i < count; i++)
		list[i] = subitems[i];
	Item *item = new Item;
	item->Init(text, color, id);
	list[count++] = item;
	delete[] subitems;
	subitems = list;
}

void Item::SetChoosen(bool aChoosen) {
	choosen = aChoosen;
	if (!choosen)
		for (int i = 0; i < count; i++)
			subitems[i]->SetChoosen(false);
}

void Item::SetChoosenById(int id, bool choosen) {
	Item *item = FindItemById(id);
	if (item) item->SetChoosen(choosen);
}

Item* Item::FindItemById(int aId) {
	if (id == aId)
		return this;
	for (int i = 0; i < count; i++) {
		Item *item = subitems[i]->FindItemById(aId);
		if (item) return item;
	}
	return nullptr;
}

//установка цветов консоли по умолчанию
void SetDefaultConsoleColors() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, WHITE);
}

//вывод текста определённого цвета с задним фоном определённого цвета
void ShowText(char *text, Color font, Color background) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (background - 8) * 16 + font);
	cout << text;
}