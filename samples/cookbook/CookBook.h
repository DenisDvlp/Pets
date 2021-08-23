#pragma once
#include "Recipe.h"
#include <iostream>

class CookBook {

	Recipe **recipes = nullptr;
	int count = 0;

public:

	//getters
	int GetCount();
	//list
	void AddRecipe(Recipe *item);
	void DeleteRecipe(int index);
	//output
	void Show();
	//file
	void SaveToFile(FILE *file);
	void LoadFromFile(FILE *file);

	//destructor
	~CookBook();
};
