#include "Ingredient.h"
#include "StringUtils.h"
using std::cout;
using std::endl;

//destructor

Ingredient::~Ingredient() {
	delete[] name;
}

//setters

void Ingredient::SetName(char *value) {
	CopyString(&name, value);
}

void Ingredient::SetWeight(int value) {
	weight = value;
}

//getters

char* Ingredient::GetName() {
	return name;
}

int Ingredient::GetWeight() {
	return weight;
}

//output

void Ingredient::Show() {
	cout << name << " (" << weight << " grams)" << endl;
}

//file

void Ingredient::SaveToFile(FILE *file) {

	//name
	int len = GetLength(name);
	fwrite(&len, 4, 1, file);
	fwrite(name, 1, len, file);

	//weight
	fwrite(&weight, sizeof(weight), 1, file);
}

void Ingredient::LoadFromFile(FILE *file) {

	//name
	int len = 0;
	fread(&len, 4, 1, file);
	delete[] name;
	name = new char[len + 1];
	name[len] = 0;
	fread(name, 1, len, file);

	//weight
	fread(&weight, sizeof(weight), 1, file);
}