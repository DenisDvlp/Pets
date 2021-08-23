#pragma once
#include "CookBook.h"
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

	CookBook *book;
	Item *localRoot;
	Item *root;
	Color actionColor;

public:

	void Init(Color menuColor, Color submenuColor, Color aActionColor) {
		book = new CookBook;
		root = new Item;
		root->Init("", menuColor, ITEM_NONE);
		root->AddSubitem("Show cook book", menuColor, ITEM_SHOW);
		root->AddSubitem("Add recipe", menuColor, ITEM_ADD);
		root->AddSubitem("Remove recipe", menuColor, ITEM_DELETE);
		root->AddSubitem("Save to file", menuColor, ITEM_SAVE);
		root->AddSubitem("Load from file", menuColor, ITEM_LOAD);
		root->AddSubitem("Exit", menuColor, ITEM_EXIT);
		Item *item = root->FindItemById(ITEM_ADD);
		item->AddSubitem("Back", submenuColor, ITEM_BACK);
		item->AddSubitem("Cold dish", submenuColor, ITEM_COLD);
		item->AddSubitem("Warm dish", submenuColor, ITEM_WARM);
		root->SetChoosen(true);
		localRoot = root;
		actionColor = aActionColor;
	}

	void Run() {
		//показ меню
		int id = 0;
		root->Show();
		do {
			id = WaitInputWithDialog();
			//показ меню
			system("cls");
			root->Show();
			//безопастный ввод с клавиатуры
			Execute(id);
		} while (id != ITEM_EXIT);
		//установка цветов консоли по умолчанию
		SetDefaultConsoleColors();
		cout << endl;
		system("pause");
	}

private:

	//ожидание ввода с диалогом
	int WaitInputWithDialog() {
		//показ диалога пользователю о том, что ему делать
		ShowText("\nChoose item:", localRoot->GetSubitem(0)->GetColor(), BLACK);
		//безопастный ввод с клавиатуры
		char input[255];
		cin >> input;
		int itemNumber = atoi(input);
		//определяем ID выбраного пункта
		int id = ITEM_NONE;
		if (itemNumber > 0 && itemNumber <= localRoot->GetItemCount())
			id = localRoot->GetSubitem(itemNumber - 1)->GetId();
		else
			id = localRoot->GetId();
		//снимаем выделения со всех пунктов внутри корневого
		localRoot->SetChoosen(false);
		//выделяем корневой
		localRoot->SetChoosen(true);
		//выделяем выбранный
		localRoot->SetChoosenById(id, true);
		return id;
	}

	//выполнение действий
	void Execute(int id) {
		int index;
		char input[255] = { 0 };
		Recipe *recipe = nullptr;
		FILE *file = nullptr;
		switch (id) {
		case ITEM_NONE:
			break;
		case ITEM_SHOW:
			ShowText("\n", actionColor, BLACK);
			book->Show();
			break;
		case ITEM_ADD:
			localRoot = root->FindItemById(ITEM_ADD);
			break;
		case ITEM_BACK:
			localRoot = root;
			root->SetChoosen(false);
			//выделяем корневой
			root->SetChoosen(true);
			system("cls");
			root->Show();
			break;
		case ITEM_COLD:
		case ITEM_WARM:
			ShowText("\n", actionColor, BLACK);
			recipe = new Recipe;
			cout << "Name:";
			getchar();
			gets_s(input);
			recipe->SetName(input);
			if (id == ITEM_COLD)
				recipe->SetDishType(dtCold);
			else
				recipe->SetDishType(dtWarm);
			cout << "Desription:";
			gets_s(input);
			recipe->SetDesription(input);
			cout << "Number of ingredients:";
			cin >> input;
			index = atoi(input);
			for (int i = 0; i < index; i++) {
				cout << "Ingredient " << i + 1 << ":\nName:";
				char name[256] = { 0 };
				getchar();
				gets_s(name);
				cout << "Weight:";
				cin >> input;
				int weight = atoi(input);
				recipe->AddIngredient(name, weight);
			}
			book->AddRecipe(recipe);
			cout << "\nRecipe added\n";
			break;
		case ITEM_DELETE:
			ShowText("\nDelete recipe by index(1..n):", actionColor, BLACK);
			cin >> input;
			index = atoi(input);
			if(index > 0 && index <= book->GetCount())
				ShowText("\nRecipe successfully deleted!\n", actionColor, BLACK);
			else
				ShowText("\nRecipe not found!\n", actionColor, BLACK);
			book->DeleteRecipe(index - 1);
			break;
		case ITEM_SAVE:
			ShowText("\nEnter name of file:", actionColor, BLACK);
			cin >> input;
			if (!fopen_s(&file, input, "wb")) {
				book->SaveToFile(file);
				fclose(file);
				ShowText("\nCook book loaded!\n", actionColor, BLACK);
			} else
				ShowText("\nCould not save!\n", actionColor, BLACK);
			break;
		case ITEM_LOAD:
			ShowText("\nEnter name of file:", actionColor, BLACK);
			cin >> input;
			if (!fopen_s(&file, input, "rb")) {
				book->LoadFromFile(file);
				fclose(file);
				ShowText("\nCook book loaded!\n", actionColor, BLACK);
			}
			else
				ShowText("\nCould not load!\n", actionColor, BLACK);
			break;
		case ITEM_EXIT:
			break;
		}
	}
};
