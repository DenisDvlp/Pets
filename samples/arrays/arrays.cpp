/*
1. Создание массива (1, 2, 3 - мерные)
	1.1 целочисленный
	1.2 вещественный
	1.3 символьный
2. Удаление массива (1, 2, 3 - мерные)
	2.1 целочисленный
	2.2 вещественный
	2.3 символьный
3. Вывод массива (1, 2, 3 - мерные)
	3.1 целочисленный
	3.2 вещественный
	3.3 символьный
	3.4 строки
4. Инициализация массива случайными значениями (1, 2, 3 - мерные)
	4.1 в диапазоне
		4.1.1 целочисленный
		4.1.2 вещественный
		4.1.3 символьный
	4.2 из массива
		4.2.1 целочисленный
		4.2.2 вещественный
		4.2.3 символьный
	4.3 подмассив одним значением
		4.3.1 целочисленный
		4.3.2 вещественный
		4.3.3 символьный
	4.4 весь массив одним значением
		4.4.1 целочисленный
		4.4.2 вещественный
		4.4.3 символьный
5. Обмен указателей/переменных значениями
6. Получение случайного значения
7. Копии массивов
	7.1 Создание копии массива
	7.2 Копирование массива
8. Изменение размеров массива
	8.1 Добавление элемента
	8.2 Удаление элемента
	8.3 Конкатенация массивов
	8.4 Обрезка массива
	8.5 Вырезка массива
*/

#include <iostream>
#include <cstring>
#include "arrays.h"

using namespace std;

//СОЗДАНИЕ МАССИВА

//создание целочисленного массива
int* CreateIntArray(int size) {
	if (size <= 0)
		return NULL;
	return new int[size];
}

//создание двухмерного целочисленного массива
int** CreateIntArray(int rows, int cols) {
	if (rows <= 0 || cols <= 0)
		return NULL;
	int **array = new int*[rows];
	for (int i = 0; i < rows; i++)
		array[i] = CreateIntArray(cols);
	return array;
}

//создание трёхмерного целочисленного массива
int*** CreateIntArray(int depth, int rows, int cols) {
	if (depth <= 0 || rows <= 0 || cols <= 0)
		return NULL;
	int ***array = new int**[depth];
	for (int i = 0; i < depth; i++)
		array[i] = CreateIntArray(rows, cols);
	return array;
}

//создание вещественного массива
double* CreateDoubleArray(int size) {
	if (size <= 0)
		return NULL;
	return new double[size];
}

//создание двухмерного вещественного массива
double** CreateDoubleArray(int rows, int cols) {
	if (rows <= 0 || cols <= 0)
		return NULL;
	double **array = new double*[rows];
	for (int i = 0; i < rows; i++)
		array[i] = CreateDoubleArray(cols);
	return array;
}

//создание трёхмерного вещественного массива
double*** CreateDoubleArray(int depth, int rows, int cols) {
	if (depth <= 0 || rows <= 0 || cols <= 0)
		return NULL;
	double ***array = new double**[depth];
	for (int i = 0; i < depth; i++)
		array[i] = CreateDoubleArray(rows, cols);
	return array;
}

//создание символьного массива
char* CreateCharArray(int size) {
	if (size <= 0)
		return NULL;
	return new char[size];
}

//создание двухмерного символьного массива
char** CreateCharArray(int rows, int cols) {
	if (rows <= 0 || cols <= 0)
		return NULL;
	char **array = new char*[rows];
	for (int i = 0; i < rows; i++)
		array[i] = CreateCharArray(cols);
	return array;
}

//создание трёхмерного символьного массива
char*** CreateCharArray(int depth, int rows, int cols) {
	if (depth <= 0 || rows <= 0 || cols <= 0)
		return NULL;
	char ***array = new char**[depth];
	for (int i = 0; i < depth; i++)
		array[i] = CreateCharArray(rows, cols);
	return array;
}

//УДАЛЕНИЕ МАССИВА

//удаление целочисленного массива
void DeleteArray(int *array) {
	delete[] array;
}

//удаление двухмерного целочисленного массива
void DeleteArray(int **array, int rows) {
	for (int i = 0; i < rows; i++)
		DeleteArray(array[i]);
	DeleteArray((int*)array);
}

//удаление трёхмерного целочисленного массива
void DeleteArray(int ***array, int depth, int rows) {
	for (int i = 0; i < depth; i++)
		DeleteArray(array[i], rows);
	DeleteArray((int*)array);
}

//удаление вещественного массива
void DeleteArray(double *array) {
	delete[] array;
}

//удаление двухмерного вещественного массива
void DeleteArray(double **array, int rows) {
	for (int i = 0; i < rows; i++)
		DeleteArray(array[i]);
	DeleteArray((double*)array);
}

//удаление трёхмерного вещественного массива
void DeleteArray(double ***array, int depth, int rows) {
	for (int i = 0; i < depth; i++)
		DeleteArray(array[i], rows);
	DeleteArray((double*)array);
}

//удаление символьного массива
void DeleteArray(char *array) {
	delete[] array;
}

//удаление двухмерного символьного массива
void DeleteArray(char **array, int rows) {
	for (int i = 0; i < rows; i++)
		DeleteArray(array[i]);
	DeleteArray((char*)array);
}

//удаление трёхмерного символьного массива
void DeleteArray(char ***array, int depth, int rows) {
	for (int i = 0; i < depth; i++)
		DeleteArray(array[i], rows);
	DeleteArray((char*)array);
}

//ВЫВОД МАССИВА

//вывод целочисленного массива
void ShowArray(int *array, int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
}

//вывод двухмерного целочисленного массива
void ShowArray(int **array, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		ShowArray(array[i], cols);
		cout << endl;
	}
}

//вывод трёхмерного целочисленного массива
void ShowArray(int ***array, int depth, int rows, int cols) {
	for (int i = 0; i < depth; i++) {
		ShowArray(array[i], rows, cols);
		cout << endl;
	}
}

//вывод вещественного массива
void ShowArray(double *array, int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
}

//вывод двухмерного вещественного массива
void ShowArray(double **array, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		ShowArray(array[i], cols);
		cout << endl;
	}
}

//вывод трёхмерного вещественного массива
void ShowArray(double ***array, int depth, int rows, int cols) {
	for (int i = 0; i < depth; i++) {
		ShowArray(array[i], rows, cols);
		cout << endl;
	}
}

//вывод символьного массива
void ShowArray(char *array, int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
}

//вывод двухмерного символьного массива
void ShowArray(char **array, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		ShowArray(array[i], cols);
		cout << endl;
	}
}

//вывод трёхмерного символьного массива
void ShowArray(char ***array, int depth, int rows, int cols) {
	for (int i = 0; i < depth; i++) {
		ShowArray(array[i], rows, cols);
		cout << endl;
	}
}

//вывод строки
void ShowString(char *array) {
	cout << array;
}

//вывод массива строк
void ShowStrings(char **array, int rows) {
	for (int i = 0; i < rows; i++) {
		ShowString(array[i]);
		cout << endl;
	}
}

//вывод двухмерного массива строк
void ShowStrings(char ***array, int depth, int rows) {
	for (int i = 0; i < depth; i++) {
		ShowStrings(array[i], rows);
		cout << endl;
	}
}

//ИНИЦИАЛИЗАЦИЯ МАССИВА

//инициализация целочисленного массива случайными значениями
void InitRandomArray(int *array, int size, int from, int to) {
	for (int i = 0; i < size; i++)
		array[i] = GetRand(from, to);
}

//инициализация двухмерного целочисленного массива случайными значениями
void InitRandomArray(int **array, int rows, int cols, int from, int to) {
	for (int i = 0; i < rows; i++)
		InitRandomArray(array[i], cols, from, to);
}

//инициализация трёхмерного целочисленного массива случайными значениями
void InitRandomArray(int ***array, int depth, int rows, int cols, int from, int to) {
	for (int i = 0; i < depth; i++)
		InitRandomArray(array[i], rows, cols, from, to);
}

//инициализация вещественного массива случайными значениями
void InitRandomArray(double *array, int size, double from, double to) {
	for (int i = 0; i < size; i++)
		array[i] = GetRand(from, to);
}

//инициализация двухмерного вещественного массива случайными значениями
void InitRandomArray(double **array, int rows, int cols, double from, double to) {
	for (int i = 0; i < rows; i++)
		InitRandomArray(array[i], cols, from, to);
}

//инициализация трёхмерного вещественного массива случайными значениями
void InitRandomArray(double ***array, int depth, int rows, int cols, double from, double to) {
	for (int i = 0; i < depth; i++)
		InitRandomArray(array[i], rows, cols, from, to);
}

//инициализация символьного массива случайными значениями
void InitRandomArray(char *array, int size, char from, char to) {
	for (int i = 0; i < size; i++)
		array[i] = GetRand(from, to);
}

//инициализация двухмерного символьного массива случайными значениями
void InitRandomArray(char **array, int rows, int cols, char from, char to) {
	for (int i = 0; i < rows; i++)
		InitRandomArray(array[i], cols, from, to);
}

//инициализация трёхмерного символьного массива случайными значениями
void InitRandomArray(char ***array, int depth, int rows, int cols, char from, char to) {
	for (int i = 0; i < depth; i++)
		InitRandomArray(array[i], rows, cols, from, to);
}

//инициализация целочисленного массива случайными из строки
void InitRandomArrayFromAlphabet(int *array, int size, int *alphabet, int asize) {
	for (int i = 0; i < size; i++)
		array[i] = GetRandFromArray(alphabet, asize);
}

//инициализация двухмерного целочисленного массива случайными значениями
void InitRandomArrayFromAlphabet(int **array, int rows, int cols, int *alphabet, int asize) {
	for (int i = 0; i < rows; i++)
		InitRandomArrayFromAlphabet(array[i], cols, alphabet, asize);
}

//инициализация трёхмерного целочисленного массива случайными значениями
void InitRandomArrayFromAlphabet(int ***array, int depth, int rows, int cols, int *alphabet, int asize) {
	for (int i = 0; i < depth; i++)
		InitRandomArrayFromAlphabet(array[i], rows, cols, alphabet, asize);
}

//инициализация вещественного массива случайными из строки
void InitRandomArrayFromAlphabet(double *array, int size, double *alphabet, int asize) {
	for (int i = 0; i < size; i++)
		array[i] = GetRandFromArray(alphabet, asize);
}

//инициализация двухмерного вещественного массива случайными значениями
void InitRandomArrayFromAlphabet(double **array, int rows, int cols, double *alphabet, int asize) {
	for (int i = 0; i < rows; i++)
		InitRandomArrayFromAlphabet(array[i], cols, alphabet, asize);
}

//инициализация трёхмерного вещественного массива случайными значениями
void InitRandomArrayFromAlphabet(double ***array, int depth, int rows, int cols, double *alphabet, int asize) {
	for (int i = 0; i < depth; i++)
		InitRandomArrayFromAlphabet(array[i], rows, cols, alphabet, asize);
}

//инициализация символьного массива случайными из строки
void InitRandomArrayFromAlphabet(char *array, int size, char *alphabet, int asize) {
	for (int i = 0; i < size; i++)
		array[i] = GetRandFromArray(alphabet, asize);
}

//инициализация двухмерного символьного массива случайными значениями
void InitRandomArrayFromAlphabet(char **array, int rows, int cols, char *alphabet, int asize) {
	for (int i = 0; i < rows; i++)
		InitRandomArrayFromAlphabet(array[i], cols, alphabet, asize);
}

//инициализация трёхмерного символьного массива случайными значениями
void InitRandomArrayFromAlphabet(char ***array, int depth, int rows, int cols, char *alphabet, int asize) {
	for (int i = 0; i < depth; i++)
		InitRandomArrayFromAlphabet(array[i], rows, cols, alphabet, asize);
}

//заполнение части целочисленного массива значением
void FillSubArray(int *array, int start, int count, int value) {
	int size = start + count;
	for (int i = start; i < size; i++)
		array[i] = value;
}

//заполнение части двухмерного целочисленного массива значением
void FillSubArray(int **array, int startRow, int startCol, int rowCount, int colCount, int value) {
	int size = startRow + rowCount;
	for (int i = startRow; i < size; i++)
		FillSubArray(array[i], startCol, colCount, value);
}

//заполнение части трёхмерного целочисленного массива значением
void FillSubArray(int ***array, int startDepth, int startRow, int startCol, int depthCount, int rowCount, int colCount, int value) {
	int size = startDepth + depthCount;
	for (int i = startRow; i < size; i++)
		FillSubArray(array[i], startRow, startCol, rowCount, colCount, value);
}

//заполнение части вещественного массива значением
void FillSubArray(double *array, int start, int count, double value) {
	int size = start + count;
	for (int i = start; i < size; i++)
		array[i] = value;
}

//заполнение части двухмерного вещественного массива значением
void FillSubArray(double **array, int startRow, int startCol, int rowCount, int colCount, double value) {
	int size = startRow + rowCount;
	for (int i = startRow; i < size; i++)
		FillSubArray(array[i], startCol, colCount, value);
}

//заполнение части трёхмерного вещественного массива значением
void FillSubArray(double ***array, int startDepth, int startRow, int startCol, int depthCount, int rowCount, int colCount, double value) {
	int size = startDepth + depthCount;
	for (int i = startRow; i < size; i++)
		FillSubArray(array[i], startRow, startCol, rowCount, colCount, value);
}

//заполнение части символьного массива значением
void FillSubArray(char *array, int start, int count, char value) {
	int size = start + count;
	for (int i = start; i < size; i++)
		array[i] = value;
}

//заполнение части двухмерного символьного массива значением
void FillSubArray(char **array, int startRow, int startCol, int rowCount, int colCount, char value) {
	int size = startRow + rowCount;
	for (int i = startRow; i < size; i++)
		FillSubArray(array[i], startCol, colCount, value);
}

//заполнение части трёхмерного символьного массива значением
void FillSubArray(char ***array, int startDepth, int startRow, int startCol, int depthCount, int rowCount, int colCount, char value) {
	int size = startDepth + depthCount;
	for (int i = startRow; i < size; i++)
		FillSubArray(array[i], startRow, startCol, rowCount, colCount, value);
}

//заполнение целочисленного массива значением
void FillArray(int *array, int size, int value) {
	FillSubArray(array, 0, size, value);
}

//заполнение двухмерного целочисленного массива значением
void FillArray(int **array, int rows, int cols, int value) {
	FillSubArray(array, 0, 0, rows, cols, value);
}

//заполнение трёхмерного целочисленного массива значением
void FillArray(int ***array, int depth, int rows, int cols, int value) {
	FillSubArray(array, 0, 0, 0, depth, rows, cols, value);
}

//заполнение вещественного массива значением
void FillArray(double *array, int size, double value) {
	FillSubArray(array, 0, size, value);
}

//заполнение двухмерного вещественного массива значением
void FillArray(double **array, int rows, int cols, double value) {
	FillSubArray(array, 0, 0, rows, cols, value);
}

//заполнение трёхмерного вещественного массива значением
void FillArray(double ***array, int depth, int rows, int cols, double value) {
	FillSubArray(array, 0, 0, 0, depth, rows, cols, value);
}

//заполнение символьного массива значением
void FillArray(char *array, int size, char value) {
	FillSubArray(array, 0, size, value);
}

//заполнение двухмерного символьного массива значением
void FillArray(char **array, int rows, int cols, char value) {
	FillSubArray(array, 0, 0, rows, cols, value);
}

//заполнение трёхмерного символьного массива значением
void FillArray(char ***array, int depth, int rows, int cols, char value) {
	FillSubArray(array, 0, 0, 0, depth, rows, cols, value);
}

//ОБМЕН УКАЗАТЕЛЕЙ/ПЕРЕМЕННЫХ ЗНАЧЕНИЯМИ

//обмен значениями переменных
void Exchange(int &first, int &second) {
	int tmp = first;
	first = second;
	second = tmp;
}

//обмен значениями переменных
void Exchange(double &first, double &second) {
	double tmp = first;
	first = second;
	second = tmp;
}

//обмен значениями переменных
void Exchange(char &first, char &second) {
	char tmp = first;
	first = second;
	second = tmp;
}

//обмен значениями указателей
void Exchange(void* &first, void* &second) {
	void *tmp = first;
	first = second;
	second = tmp;
}

//обмен значениями указателей
void Exchange(int* &first, int* &second) {
	Exchange((void*&)first, (void*&)second);
}

//обмен значениями указателей
void Exchange(int** &first, int** &second) {
	Exchange((void*&)first, (void*&)second);
}

//обмен значениями указателей
void Exchange(double* &first, double* &second) {
	Exchange((void*&)first, (void*&)second);
}

//обмен значениями указателей
void Exchange(double** &first, double** &second) {
	Exchange((void*&)first, (void*&)second);
}

//обмен значениями указателей
void Exchange(char* &first, char* &second) {
	Exchange((void*&)first, (void*&)second);
}

//обмен значениями указателей
void Exchange(char** &first, char** &second) {
	Exchange((void*&)first, (void*&)second);
}

//ПОЛУЧЕНИЕ СЛУЧАЙНОГО ЗНАЧЕНИЯ

//случайное целочисленное число в диапазоне
int GetRand(int from, int to) {
	if (to < from)
		Exchange(from, to);
	return rand() % (to - from + 1) + from;
}

//случайное вещественное число в диапазоне
double GetRand(double from, double to) {
	if (to < from)
		Exchange(from, to);
	return rand() % (int)(to - from + 1) + from + rand() % 100 * 0.01;
}

//случайный символ в диапазоне
char GetRand(char from, char to) {
	if (to < from)
		Exchange(from, to);
	return rand() % (to - from + 1) + from;
}

//случайное целое число из массива
int GetRandFromArray(int *array, int size) {
	if (size <= 0)
		return 0;
	return array[rand() % size];
}

//случайное вещественное число из массива
double GetRandFromArray(double *array, int size) {
	if (size <= 0)
		return 0;
	return array[rand() % size];
}

//случайный символ из массива
char GetRandFromArray(char *array, int size) {
	if (size <= 0)
		return 0;
	return array[rand() % size];
}


//КОПИИ МАССИВОВ

//Создание копии массива
//Копирование массива

//ИЗМЕНЕНИЕ РАЗМЕРОВ МАССИВА

//Добавление элемента
//Удаление элемента
//Конкатенация массивов
//Обрезка массива
//Вырезка массива