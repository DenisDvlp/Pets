#pragma once

//СОЗДАНИЕ МАССИВА

//создание целочисленного массива
int* CreateIntArray(int size);
int** CreateIntArray(int rows, int cols);
int*** CreateIntArray(int depth, int rows, int cols);
//создание вещественного массива
double* CreateDoubleArray(int size);
double** CreateDoubleArray(int rows, int cols);
double*** CreateDoubleArray(int depth, int rows, int cols);
//создание массива символов
char* CreateCharArray(int size);
char** CreateCharArray(int rows, int cols);
char*** CreateCharArray(int depth, int rows, int cols);

//УДАЛЕНИЕ МАССИВА

//удаление целочисленного массива
void DeleteArray(int *array);
void DeleteArray(int **array, int rows);
void DeleteArray(int ***array, int depth, int rows);
//удаление вещественного массива
void DeleteArray(double *array);
void DeleteArray(double **array, int rows);
void DeleteArray(double ***array, int depth, int rows);
//удаление символьного массива
void DeleteArray(char *array);
void DeleteArray(char **array, int rows);
void DeleteArray(char ***array, int depth, int rows);

//ВЫВОД МАССИВА

//вывод целочисленного массива
void ShowArray(int *array, int size);
void ShowArray(int **array, int rows, int cols);
void ShowArray(int ***array, int depth, int rows, int cols);
//вывод вещественного массива
void ShowArray(double *array, int size);
void ShowArray(double **array, int rows, int cols);
void ShowArray(double ***array, int depth, int rows, int cols);
//вывод символьного массива
void ShowArray(char *array, int size);
void ShowArray(char **array, int rows, int cols);
void ShowArray(char ***array, int depth, int rows, int cols);
//вывод строк
void ShowString(char *array);
void ShowStrings(char **array, int rows);
void ShowStrings(char ***array, int depth, int rows);

//ИНИЦИАЛИЗАЦИЯ МАССИВА

//инициализация массива случайными значениями из диапазона
//целочисленного
void InitRandomArray(int *array, int size, int from, int to);
void InitRandomArray(int **array, int rows, int cols, int from, int to);
void InitRandomArray(int ***array, int depth, int rows, int cols, int from, int to);
//вещественного
void InitRandomArray(double *array, int size, double from, double to);
void InitRandomArray(double **array, int rows, int cols, double from, double to);
void InitRandomArray(double ***array, int depth, int rows, int cols, double from, double to);
//символьного
void InitRandomArray(char *array, int size, char from, char to);
void InitRandomArray(char **array, int rows, int cols, char from, char to);
void InitRandomArray(char ***array, int depth, int rows, int cols, char from, char to);
//инициализация массива случайными значениями из массива
//целочисленного
void InitRandomArrayFromAlphabet(int *array, int size, int *alphabet, int asize);
void InitRandomArrayFromAlphabet(int **array, int rows, int cols, int *alphabet, int asize);
void InitRandomArrayFromAlphabet(int ***array, int depth, int rows, int cols, int *alphabet, int asize);
//вещественного
void InitRandomArrayFromAlphabet(double *array, int size, double *alphabet, int asize);
void InitRandomArrayFromAlphabet(double **array, int rows, int cols, double *alphabet, int asize);
void InitRandomArrayFromAlphabet(double ***array, int depth, int rows, int cols, double *alphabet, int asize);
//символьного
void InitRandomArrayFromAlphabet(char *array, int size, char *alphabet, int asize);
void InitRandomArrayFromAlphabet(char **array, int rows, int cols, char *alphabet, int asize);
void InitRandomArrayFromAlphabet(char ***array, int depth, int rows, int cols, char *alphabet, int asize);
//заполнение части массива значением
//целочисленного
void FillSubArray(int *array, int start, int count, int value);
void FillSubArray(int **array, int startRow, int startCol, int rowCount, int colCount, int value);
void FillSubArray(int ***array, int startDepth, int startRow, int startCol, int depthCount, int rowCount, int colCount, int value);
//вещественного
void FillSubArray(double *array, int start, int count, double value);
void FillSubArray(double **array, int startRow, int startCol, int rowCount, int colCount, double value);
void FillSubArray(double ***array, int startDepth, int startRow, int startCol, int depthCount, int rowCount, int colCount, double value);
//символьного
void FillSubArray(char *array, int start, int count, char value);
void FillSubArray(char **array, int startRow, int startCol, int rowCount, int colCount, char value);
void FillSubArray(char ***array, int startDepth, int startRow, int startCol, int depthCount, int rowCount, int colCount, char value);
//заполнение массива значением
//целочисленного
void FillArray(int *array, int size, int value);
void FillArray(int **array, int rows, int cols, int value);
void FillArray(int ***array, int depth, int rows, int cols, int value);
//вещественного
void FillArray(double *array, int size, double value);
void FillArray(double **array, int rows, int cols, double value);
void FillArray(double ***array, int depth, int rows, int cols, double value);
//символьного
void FillArray(char *array, int size, char value);
void FillArray(char **array, int rows, int cols, char value);
void FillArray(char ***array, int depth, int rows, int cols, char value);

//ОБМЕН УКАЗАТЕЛЕЙ/ПЕРЕМЕННЫХ ЗНАЧЕНИЯМИ

void Exchange(int &first, int &second);
void Exchange(double &first, double &second);
void Exchange(char &first, char &second);
void Exchange(void* &first, void* &second);
void Exchange(int* &first, int* &second);
void Exchange(int** &first, int** &second);
void Exchange(double* &first, double* &second);
void Exchange(double** &first, double** &second);
void Exchange(char* &first, char* &second);
void Exchange(char** &first, char** &second);

//ПОЛУЧЕНИЕ СЛУЧАЙНОГО ЗНАЧЕНИЯ

//случайное значение в диапазоне
int GetRand(int from, int to);
double GetRand(double from, double to);
char GetRand(char from, char to);
//случайное значение из массива
int GetRandFromArray(int *array, int size);
double GetRandFromArray(double *array, int size);
char GetRandFromArray(char *array, int size);
