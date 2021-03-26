#include "utils.h"
#include <string>

void DeleteArray(void *&array);

void AddCopyString(char **&stringList, unsigned count, char *string) {
	char *copyString = 0;//NULL
	CopyString(copyString, string);
	AddString(stringList, count, copyString);
}

void AddString(char **&stringList, unsigned count, char *string) {
	char **newStringList = new char*[count + 1];
	for (unsigned i = 0; i < count; i++)
		newStringList[i] = stringList[i];
	newStringList[count] = string;
	if(count) delete[] stringList;
	stringList = newStringList;
}

char* GetTextFromStrings(char **strings, int count, const char *delim) {
	if (count <= 0) return 0;//NULL
	int length = 0;
	for (int i = 0; i < count; i++)
		length += GetLength(strings[i]);
	if(!length) return 0;//NULL
	length += (count - 1) * GetLength(delim) + 1;
	char *text = new char[length];
	*text = 0;
	for (int i = 0; i < count; i++) {
		if (i && delim) strcat_s(text, length, delim);
		if (strings[i]) strcat_s(text, length, strings[i]);
	}
	return text;
}

char** GetStringsFromText(char *text, const char *delims, int &count) {
	if (!text) return 0;//NULL
	char **stringList = 0;//NULL
	count = 0;
	char *tmp = 0;//NULL
	char *context = NULL;
	CopyString(tmp, text);
	char *string = strtok_s(tmp, delims, &context);
	while (string) {
		AddCopyString(stringList, count++, string);
		string = strtok_s(0, delims, &context);
	}
	delete[] tmp;
	return stringList;
}

void CopyString(char *&dst, char *src) {
	if (dst == src || dst && src && !_stricmp(dst, src))
		return;
	DeleteArray(dst);
	if (src) {
		int length = GetLength(src);
		dst = new char[length + 1];
		strcpy_s(dst, length + 1, src);
	}
}

int GetLength(const char *string) {
	return (string) ? strlen(string) : 0;
}

bool IsEqual(const char *first, const char *second) {
	return first == second || first && second && !strcmp(first, second);
}

void DeleteArray(char **&array, int count) {
	if (count <= 0) return;
	for (int i = 0; i < count; i++)
		DeleteArray(array[i]);
	DeleteArray(array);
}

void DeleteArray(char *&array) {
	DeleteArray((void*&)array);
}

void DeleteArray(char **&array) {
	DeleteArray((void*&)array);
}

void DeleteArray(void *&array) {
	if (array) delete[] array;
	array = 0;//NULL
}

char* CreateCharArray(int size) {
	if (size <= 0) return 0;//NULL
	return new char[size];
}

char** CreateCharArray(int height, int width) {
	if (height <= 0 || width <= 0) return 0;//NULL
	char **array = new char*[height];
	for (int i = 0; i < height; i++)
		array[i] = CreateCharArray(width);
	return array;
}

char* IntToStr(int number) {
	char *string = CreateCharArray(11);
	_itoa_s(number, string, 11, 10);
	return string;
}