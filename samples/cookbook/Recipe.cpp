#include "Recipe.h"
#include "StringUtils.h"
using std::cout;
using std::endl;

//destructor
Recipe::~Recipe() {
	delete[] name;
	delete[] description;
	for (int i = 0; i < ingredientsCount; i++)
		delete ingredients[i];
	delete[] ingredients;
}

//setters

void Recipe::SetName(char *value) {
	CopyString(&name, value);
}

void Recipe::SetDesription(char *value) {
	CopyString(&description, value);
}

void Recipe::SetDishType(DishType value) {
	dishType = value;
}

//getters

char* Recipe::GetName() {
	return name;
}

char* Recipe::GetDesription() {
	return description;
}

DishType Recipe::GetDishType() {
	return dishType;
}

//list

void Recipe::AddIngredient(char *name, int weight) {
	Ingredient *item = new Ingredient;
	item->SetName(name);
	item->SetWeight(weight);
	AddIngredient(item);
}

void Recipe::AddIngredient(Ingredient *item) {
	if (!item) return;
	Ingredient **list = new Ingredient*[ingredientsCount + 1];
	for (int i = 0; i < ingredientsCount; i++)
		list[i] = ingredients[i];
	list[ingredientsCount] = item;
	delete[] ingredients;
	ingredients = list;
	ingredientsCount++;
}

void Recipe::DeleteIngredient(int index) {
	if (index < 0 || index >= ingredientsCount)
		return;
	Ingredient **list = nullptr;
	if (ingredientsCount)
		list = new Ingredient*[ingredientsCount - 1];
	for (int i = 0, j = 0; i < ingredientsCount; i++)
		if (i == index)
			list[j++] = ingredients[i];
		else
			delete ingredients[i];
	delete[] ingredients;
	ingredients = list;
	ingredientsCount--;
}

//output

void Recipe::Show() {
	if (name) cout << name << endl;
	switch (dishType) {
	case dtCold:
		cout << "Cold dish" << endl;
		break;
	case dtWarm:
		cout << "Warm dish" << endl;
		break;
	}
	if (description) cout << description << endl;
	if (!ingredientsCount)
		cout << "No ingredients." << endl;
	else
		cout << "Ingredients:" << endl;
	for (int i = 0; i < ingredientsCount; i++) {
		cout << i + 1 << ") ";
		ingredients[i]->Show();
	}
}

//file

void Recipe::SaveToFile(FILE *file) {

	//name
	int len = GetLength(name);
	fwrite(&len, 4, 1, file);
	fwrite(name, 1, len, file);

	//description
	len = GetLength(description);
	fwrite(&len, 4, 1, file);
	fwrite(description, 1, len, file);

	//dishType
	fwrite(&dishType, sizeof(dishType), 1, file);

	//ingredients
	fwrite(&ingredientsCount, sizeof(ingredientsCount), 1, file);
	for (int i = 0; i < ingredientsCount; i++)
		ingredients[i]->SaveToFile(file);
}

void Recipe::LoadFromFile(FILE *file) {

	//name
	int len = 0;
	fread(&len, 4, 1, file);
	delete[] name;
	name = new char[len + 1];
	name[len] = 0;
	fread(name, 1, len, file);

	//description
	len = 0;
	fread(&len, 4, 1, file);
	delete[] description;
	description = new char[len + 1];
	description[len] = 0;
	fread(description, 1, len, file);

	//dishType
	fread(&dishType, sizeof(dishType), 1, file);

	//ingredients
	fread(&ingredientsCount, sizeof(ingredientsCount), 1, file);
	if (!ingredientsCount) return;
	ingredients = new Ingredient*[ingredientsCount];
	for (int i = 0; i < ingredientsCount; i++) {
		ingredients[i] = new Ingredient;
		ingredients[i]->LoadFromFile(file);
	}
}