#include "CookBook.h"
using std::cout;
using std::endl;

//destructor

CookBook::~CookBook() {
	for (int i = 0; i < count; i++)
		delete recipes[i];
	delete[] recipes;
}

//getters

int CookBook::GetCount() {
	return count;
}

//list

void CookBook::AddRecipe(Recipe *item) {
	if (!item) return;
	Recipe **list = new Recipe*[count + 1];
	for (int i = 0; i < count; i++)
		list[i] = recipes[i];
	list[count] = item;
	delete[] recipes;
	recipes = list;
	count++;
}

void CookBook::DeleteRecipe(int index) {
	if (index < 0 || index >= count)
		return;
	Recipe **list = nullptr;
	if (count)
		list = new Recipe*[count - 1];
	for (int i = 0, j = 0; i < count; i++)
		if (i == index)
			list[j++] = recipes[i];
		else
			delete recipes[i];
	delete[] recipes;
	recipes = list;
	count--;
}

//output

void CookBook::Show() {
	if (!count)
		cout << "No recipes." << endl;
	for (int i = 0; i < count; i++) {
		cout << "Recipe " << i + 1 << endl;
		recipes[i]->Show();
		cout << endl;
	}
}

//file

void CookBook::SaveToFile(FILE *file) {
	//recipes
	fwrite(&count, sizeof(count), 1, file);
	for (int i = 0; i < count; i++)
		recipes[i]->SaveToFile(file);
}

void CookBook::LoadFromFile(FILE *file) {
	//recipes
	fread(&count, sizeof(count), 1, file);
	if (!count) return;
	recipes = new Recipe*[count];
	for (int i = 0; i < count; i++) {
		recipes[i] = new Recipe;
		recipes[i]->LoadFromFile(file);
	}
}