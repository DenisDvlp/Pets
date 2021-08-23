#pragma once
#include <iostream>

class Ingredient {

	char *name = nullptr;
	int weight = 0; //grams

public:

	//setters
	void SetName(char *value);
	void SetWeight(int value);
	//getters
	char* GetName();
	int GetWeight();
	//output
	void Show();
	//file
	void SaveToFile(FILE *file);
	void LoadFromFile(FILE *file);

	//destructor
	~Ingredient();
};