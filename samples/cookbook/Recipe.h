#pragma once
#include "Ingredient.h"
#include <iostream>

enum DishType { dtCold, dtWarm };

class Recipe {

	DishType dishType = dtCold;
	char *name = nullptr;
	char *description = nullptr;
	Ingredient **ingredients = nullptr;
	int ingredientsCount = 0;

public:

	//setters
	void SetName(char *value);
	void SetDesription(char *value);
	void SetDishType(DishType value);
	//getters
	char* GetName();
	char* GetDesription();
	DishType GetDishType();
	//list
	void AddIngredient(char *name, int weight);
	void AddIngredient(Ingredient *item);
	void DeleteIngredient(int index);
	//output
	void Show();
	//file
	void SaveToFile(FILE *file);
	void LoadFromFile(FILE *file);

	//destructor
	~Recipe();
};