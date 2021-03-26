#include "utils.h"
#include <string.h>
#include <cstdio>

//функции работы со строкой
StringFunctions S = {
	CreateString,
	CopyString,
	StringFromStrings,
	DestroyString,
	LengthString,
	IsEmptyString,
	Substring,
	ConcatStrings,
	ConcatTwoStrings,
	CompareStrings,
	IndexOfString,
	IndexOfChar,
	LastIndexOfString,
	LastIndexOfChar,
	ContainsString,
	ContainsChar,
	Replace,
	ToUpper,
	ToLower,
	DoubleToString,
	IntToString,
	CharToString
};

char* CreateString(int length) {
	if (length < 1) length = 1;
	char *string = new char[length];
	*string = 0;
	return string;
}

void DestroyString(char *&string) {
	if (!string) return;
	delete[] string;
	string = 0;
}

int LengthString(char *string) {
	if (!string) return 0;
	return strlen(string);
}

bool IsEmptyString(char *string) {
	return !LengthString(string);
}

char* CopyString(char *string) {
	int length = LengthString(string) + 1;
	char *str = CreateString(length);
	if (string) strcpy_s(str, length, string);
	return str;
}

char* ConcatStrings(int count, char *string1, ...) {
	char **strings = &string1;
	int length = 1;
	for (int i = 0; i < count; i++)
		length += LengthString(strings[i]);
	char *str = CreateString(length);
	for (int i = 0; i < count; i++)
		if(strings[i])
			strcat_s(str, length, strings[i]);
	return str;
}

char* ConcatTwoStrings(char *string1, char *string2) {
	return ConcatStrings(2, string1, string2);
}

char* StringFromStrings(Strings *strings, char *delim) {
	int length = LengthOfAllStrings(strings) + 1;
	char *string = CreateString(length);
	int count = CountStrings(strings);
	for (int i = 0; i < CountStrings(strings); i++)
		if (strings->items[i]) {
			strcat_s(string, length, strings->items[i]);
			if(delim && i < count - 1)
				strcat_s(string, length, delim);
		}
	return string;
}

int CompareStrings(char *first, char *second, bool caseSensitive) {
	if (!first || !second) return false;
	int result = 0;
	if(caseSensitive)
		result = strcmp(first, second);
	else
		result = _stricmp(first, second);
	return result;
}

int IndexOfChar(char *string, char character, int start) {
	char *str = CharToString(character);
	int index = IndexOfString(string, str, start);
	DestroyString(str);
	return index;
}

int IndexOfString(char *string, char *substring, int start) {
	int length = LengthString(string);
	if (start < 0) start = 0;
	if (!length || start >= length || !LengthString(substring)) return -1;
	char *str = strstr(string + start, substring);
	int index = -1;
	if (str) index = str - string;
	return index;
}

int LastIndexOfChar(char *string, char character) {
	char *str = CharToString(character);
	int index = LastIndexOfString(string, str);
	DestroyString(str);
	return index;
}

int LastIndexOfString(char *string, char *substring) {
	int length = LengthString(string);
	int lengthSub = LengthString(substring);
	int index = -1;
	if (length && lengthSub)
		for (int i = length - lengthSub - 1; i >= 0; i--) {
			index = IndexOfString(string, substring, i);
			if (index >= 0) break;
		}
	return index;
}

bool ContainsChar(char *string, char character, int start) {
	return IndexOfChar(string, character, start) < 0;
}

bool ContainsString(char *string, char *substring, int start) {
	return IndexOfString(string, substring, start) < 0;
}

char* Substring(char *string, int start, int end) {
	int length = LengthString(string);
	if (start < 0) start = 0;
	if (end >= length) end = length - 1;
	int count = end - start + 1;
	if (count < 0) count = 0;
	char *str = CreateString(count + 1);
	if (string)
		strncat_s(str, count + 1, string + start, count);
	return str;
}

char* Replace(char *string, char *target, char *replacement, int start) {
	char *str = CopyString(string);
	int index = start;
	while(true) {
		index = IndexOfString(str, target, index);
		if (index < 0) return str;
		int length = LengthString(str);
		int end = index + LengthString(target) - 1;
		char *first = Substring(str, 0, index - 1);
		char *last = Substring(str, end + 1, length);
		char *concat = ConcatStrings(3, first, replacement, last);
		DestroyString(first);
		DestroyString(last);
		DestroyString(str);
		str = concat;
		index = end + 1;
	}
}

char* ToUpper(char *string) {
	char *str = CopyString(string);
	_strupr_s(str, LengthString(str) + 1);
	return str;
}

char* ToLower(char *string) {
	char *str = CopyString(string);
	_strlwr_s(str, LengthString(str) + 1);
	return str;
}

char* CharToString(char character) {
	char *string = CreateString(2);
	string[0] = character;
	string[1] = 0;
	return string;
}

char* IntToString(int number) {
	char *string = CreateString(20);
	sprintf_s(string, 20, "%i", number);
	return string;
}

char* DoubleToString(double number) {
	char *string = CreateString(30);
	sprintf_s(string, 30, "%f", number);
	return string;
}
