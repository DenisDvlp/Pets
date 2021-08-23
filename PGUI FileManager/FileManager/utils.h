#pragma once

struct Strings;
struct StringFunctions;
struct StringsFunctions;
struct FileFunctions;

extern StringFunctions S;
extern StringsFunctions SS;
extern FileFunctions F;

// !!!ни одна функция не возвращает нулевого указателя!!!

///строка

char* CreateString(int length);
void DestroyString(char *&string);
int LengthString(char *string);
bool IsEmptyString(char *string);
char* CopyString(char *string);
char* ConcatStrings(int count, char *string1, ...);
char* ConcatTwoStrings(char *string1, char *string2);
char* StringFromStrings(Strings *strings, char *delim);
int CompareStrings(char *first, char *second, bool caseSensitive);
int IndexOfChar(char *string, char character, int start);
int IndexOfString(char *string, char *substring, int start);
int LastIndexOfChar(char *string, char character);
int LastIndexOfString(char *string, char *substring);
bool ContainsChar(char *string, char character, int start);
bool ContainsString(char *string, char *substring, int start);
char* Substring(char *string, int start, int end);
char* Replace(char *string, char *target, char *replacement, int start);
char* ToUpper(char *string);
char* ToLower(char *string);
char* CharToString(char character);
char* IntToString(int number);
char* DoubleToString(double number);

struct StringFunctions {
	//создаёт строку, если длина строки меньше 1, то создаёт пустую строку
	char*(*Create)(int length);
	//создаёт копию строки
	char*(*Copy)(char *string);
	//создаёт строку, соединяя список строк разделённых строкой delim
	char*(*CreateFrom)(Strings *strings, char *delim);
	//очистить память (уничтожить строку)
	void(*Destroy)(char *&string);
	//получает длину строки
	int(*Length)(char *string);
	//пуста ли строка
	bool(*IsEmpty)(char *string);
	//создаёт подстроку из строки диапазоном от start до end включительно
	char*(*Substring)(char *string, int start, int end);
	//создаёт строку, соедининяя строки
	char*(*ConcatStrings)(int count, char *string1, ...);
	//создаёт строку, соедининяя две строки
	char*(*ConcatTwoStrings)(char *string1, char *string2);
	//сравнивает две строки, строки равны - 0, первая > второй - >0, первая < второй - <0
	//caseSensitive включает/отключает зависимость регистра
	int(*Compare)(char *first, char *second, bool caseSensitive);
	//возвращает индекс первого вхождения строки, если символа нет -1
	int(*IndexOf)(char *string, char *substring, int start);
	//возвращает индекс первого вхождения символа, если символа нет -1
	int(*IndexOfChar)(char *string, char character, int start);
	//возвращает индекс последнего вхождения строки, если символа нет -1
	int(*LastIndexOf)(char *string, char *substring);
	//возвращает индекс последнего вхождения символа, если символа нет -1
	int(*LastIndexOfChar)(char *string, char character);
	//содержит ли строка подстроку
	bool(*Contains)(char *string, char *substring, int start);
	//содержит ли строка символ
	bool(*ContainsChar)(char *string, char character, int start);
	//создаёт строку, заменяя подстроку другой подстрокой
	char*(*Replace)(char *string, char *target, char *replacement, int start);
	//создаёт строку, приводя её к верхнему регистру
	char*(*ToUpper)(char *string);
	//создаёт строку, приводя её к нижнему регистру
	char*(*ToLower)(char *string);
	//создаёт строку, преобразуя вещественное в строку
	char*(*DoubleToString)(double number);
	//создаёт строку, преобразуя целое в строку
	char*(*IntToString)(int number);
	//создаёт строку, преобразуя символ в строку
	char*(*CharToString)(char character);
};

///строки

struct Strings {
	char **items;
	int count;
};

Strings* CreateStrings();
Strings* Substrings(Strings *strings, int start, int end);
Strings* StringsFromString(char *string, char *delims);
Strings* LoadFromFile(char *filepath);
void SaveToFile(Strings *strings, char *filepath);
void DestroyStrings(Strings *&strings);
int LengthOfAllStrings(Strings *strings);
int CountStrings(Strings *strings);
void AddString(Strings *strings, char *string);
void AddStrings(Strings *strings, Strings *strs);
void DeleteString(Strings *strings, int index);
void DeleteStrings(Strings *strings, int start, int count);
void InsertString(Strings *strings, char *string, int index);
void InsertStrings(Strings *strings, Strings *strs, int start);
int IndexOf(Strings *strings, char *string, int start, bool caseSensitive);
void SortStrings(Strings *strings, bool reverse);
void ClearStrings(Strings *strings);
void ExchangeStrings(Strings *strings, int firstIndex, int secondIndex);

struct StringsFunctions {
	//создаёт пусток список
	Strings*(*Create)();
	//создаёт список из строки, разбивая её разделителями (разделители исключаются)
	Strings*(*SplitString)(char *string, char *delims);
	//создаёт подсписок из списка строк диапазоном от start до end включительно
	Strings*(*Substrings)(Strings *strings, int start, int end);
	//загрузка строк из файла
	Strings*(*LoadFromFile)(char *filepath);
	//сохранение в файл
	void(*SaveToFile)(Strings *strings, char *filepath);
	//очистить память (уничтожить список)
	void(*Destroy)(Strings *&strings);
	//общая длина строк
	int(*LengthOfAll)(Strings *strings);
	//количество строк
	int(*Count)(Strings *strings);
	//добавить строку в список
	void(*Add)(Strings *strings, char *str);
	//добавить строки в список
	void(*AddStrings)(Strings *strings, Strings *strs);
	//вставить строку в список
	void(*Insert)(Strings *strings, char *string, int index);
	//вставить строки в список
	void(*InsertStrings)(Strings *strings, Strings *strs, int start);
	//удалить строку из списка
	void(*Delete)(Strings *strings, int index);
	//удалить строки из списка
	void(*DeleteStrings)(Strings *strings, int start, int end);
	//найти первое вхождение строки в списке, возвращает -1 если строка не найдена
	int(*IndexOf)(Strings *strings, char *string, int start, bool caseSensitive);
	//отсортировать строки, reverse - сортирует по убыванию/возрастанию
	void(*Sort)(Strings *strings, bool reverse);
	//очистка списка (удалить все строки в списке)
	void(*Clear)(Strings *strings);
	//поменять местами две строки в списке
	void(*Exchange)(Strings *strings, int firstIndex, int secondIndex);
};

//файл

Strings* DirList(char *dirpath, char *filter);
Strings* FileList(char *dirpath, char *filter);
long long DirSize(char *dirpath, bool recursive);
long long FileSize(char *filepath);
bool FileExists(char *filepath);
void DeleteDir(char *dirpath, bool recursive);
void DeleteFile(char *filepath);
void CopyDir(char *dirsrc, char *dirdst);
void CopyFile(char *filesrc, char *filedst);
void MoveDir(char *dirsrc, char *dirdst);
void MoveFile(char *filesrc, char *filedst);
char* GetCurrentDir();
char* SetCurrentDir(char *dirpath);
char* SetParentDir();
char* SetRootDir();
char* GetFileNameFromPath(char *path);
char* GetDirFromPath(char *path);
void MakeDir(char *dirpath);
void MakeFile(char *filepath);

struct FileFunctions {
	//список папок из текущей папки
	Strings*(*DirList)(char *dirpath, char *filter);
	//список файлов из текущей папки
	Strings*(*FileList)(char *dirpath, char *filter);
	//размер папки
	long long(*DirSize)(char *dirpath, bool recursive);
	//размер файла
	long long(*FileSize)(char *filepath);
	//существует ли файл
	bool(*FileExists)(char *filepath);
	//удалить папку
	void(*DeleteDir)(char *dirpath, bool recursive);
	//удалить файл
	void(*DeleteFile)(char *filepath);
	//копировать папку
	void(*CopyDir)(char *dirsrc, char *dirdst);
	//копировать файл
	void(*CopyFile)(char *filesrc, char *filedst);
	//переместить папку
	void(*MoveDir)(char *dirsrc, char *dirdst);
	//переместить файл
	void(*MoveFile)(char *filesrc, char *filedst);
	//текущая папка
	char*(*GetCurrentDir)();
	//переместиться в папку
	char*(*SetCurrentDir)(char *dirpath);
	//переместиться в родительскую папку
	char*(*SetParentDir)();
	//переместиться в корневую папку
	char*(*SetRootDir)();
	//извлечь имя файла из пути
	char*(*GetFileNameFromPath)(char *path);
	//извлечь папки из пути
	char*(*GetDirFromPath)(char *path);
	//создать папку
	void(*MakeDir)(char *dirpath);
	//создать файл
	void(*MakeFile)(char *filepath);
};

bool IsEqual(const char *first, const char *second);
int GetLength(const char *string);
void CopyString(char *&dst, char *src);
void AddString(char **&stringList, unsigned count, char *string);
void AddCopyString(char **&stringList, unsigned count, char *string);
char** GetStringsFromText(char *text, const char *delims, int &count);
char* GetTextFromStrings(char **strings, int count, const char *delim = 0);
char* CreateCharArray(int size);
char** CreateCharArray(int height, int width);
char* IntToStr(int number);
void DeleteArray(char *&array);
void DeleteArray(char **&array);
void DeleteArray(char *&array);
void DeleteArray(char **&array, int count);