#include "utils.h"
#include <string.h>
#include <cstdio>

//функции работы со списком строк
StringsFunctions SS = {
	CreateStrings,
	StringsFromString,
	Substrings,
	LoadFromFile,
	SaveToFile,
	DestroyStrings,
	LengthOfAllStrings,
	CountStrings,
	AddString,
	AddStrings,
	InsertString,
	InsertStrings,
	DeleteString,
	DeleteStrings,
	IndexOf,
	SortStrings,
	ClearStrings,
	ExchangeStrings
};

void DestroyItems(Strings *string);

Strings* CreateStrings() {
	Strings *strings = new Strings;
	strings->items = 0;
	strings->count = 0;
	return strings;
}

Strings* LoadFromFile(char *filepath) {
	Strings *strings = CreateStrings();
	FILE *file = 0;
	if (!filepath || fopen_s(&file, filepath, "r"))
		return strings;
	int size = 1024;
	char *buffer = CreateString(size);
	char *string = 0;
	while (!feof(file)) {
		*buffer = 0;
		fgets(buffer, size, file);
		string = ConcatTwoStrings(string, buffer);
		if (feof(file) || buffer[LengthString(buffer) - 1] == '\n') {
			AddString(strings, string);
			DestroyString(string);
		}
	}
	fclose(file);
	return strings;
}

Strings* StringsFromString(char *string, char *delims) {
	Strings *strings = CreateStrings();
	if (!string) return strings;
	char *copy = CopyString(string);
	char *delimiters = CopyString(delims);
	char *context = 0;
	char *str = strtok_s(copy, delimiters, &context);
	while (str) {
		AddString(strings, str);
		str = strtok_s(0, delimiters, &context);
	}
	DestroyString(copy);
	DestroyString(delimiters);
	return strings;
}

Strings* Substrings(Strings *strings, int start, int end) {
	Strings *list = CreateStrings();
	if (start < 0) start = 0;
	int count = CountStrings(strings);
	if (end >= count) end = count - 1;
	for (int i = start; i <= end; i++)
		AddString(list, strings->items[i]);
	return list;
}

void SaveToFile(Strings *strings, char *filepath) {
	FILE *file = 0;
	if (!filepath || fopen_s(&file, filepath, "w")) return;
	for(int i = 0; i < CountStrings(strings); i++)
		fputs(strings->items[i], file);
	fclose(file);
}

void DestroyStrings(Strings *&strings) {
	ClearStrings(strings);
	if (strings) delete strings;
	strings = 0;
}

int LengthOfAllStrings(Strings *strings) {
	int length = 0;
	for (int i = 0; i < CountStrings(strings); i++)
		length += LengthString(strings->items[i]);
	return length;
}

int CountStrings(Strings *strings) {
	if (!strings) return 0;
	return strings->count;
}

void AddString(Strings *strings, char *string) {
	InsertString(strings, string, CountStrings(strings));
}

void AddStrings(Strings *strings, Strings *strs) {
	InsertStrings(strings, strs, CountStrings(strings));
}

void DeleteString(Strings *strings, int index) {
	DeleteStrings(strings, index, index);
}

void DeleteStrings(Strings *strings, int start, int end) {
	int count = CountStrings(strings);
	if (start < 0) start = 0;
	if (end >= count) end = count - 1;
	if (end - start < 0) return;
	int newCount = count - end + start - 1;
	char **list = new char*[newCount];
	for (int i = 0, j = 0; i < count; i++)
		if (i < start || i > end)
			list[j++] = strings->items[i];
		else
			delete[] strings->items[i];
	DestroyItems(strings);
	strings->items = list;
	strings->count = newCount;
}

void InsertString(Strings *strings, char *string, int index) {
	int count = CountStrings(strings) + 1;
	if (!strings || !string || index < 0 || index >= count) return;
	char **list = new char*[count];
	for (int i = 0, j = 0; i < count; i++)
		if(index == i)
			list[i] = CopyString(string);
		else
			list[i] = strings->items[j++];
	DestroyItems(strings);
	strings->items = list;
	strings->count = count;
}

void InsertStrings(Strings *strings, Strings *strs, int start) {
	int countDst = CountStrings(strings);
	if (!strings || !strs || start < 0 || start > countDst) return;
	int countSrc = CountStrings(strs);
	int count = countSrc + countDst;
	char **list = new char*[count];
	for (int i = 0, j = 0, k = 0; i < count; i++)
		if (i >= start && i < countSrc + start)
			list[i] = CopyString(strs->items[j++]);
		else
			list[i] = strings->items[k++];
	DestroyItems(strings);
	strings->items = list;
	strings->count = count;
}

int IndexOf(Strings *strings, char *string, int start, bool caseSensitive) {
	for (int i = start; i < CountStrings(strings); i++)
		if(!CompareStrings(strings->items[i], string, caseSensitive))
			return i;
	return -1;
}

void SortStrings(Strings *strings, bool reverse) {
	int count = CountStrings(strings);
	for (int i = 0, j = count; i < count - 1; i++, j--)
		for (int k = 0; k < j - 1; k++)
			if (reverse && CompareStrings(strings->items[k], strings->items[k + 1], true) < 0 ||
				!reverse && CompareStrings(strings->items[k], strings->items[k + 1], true) > 0)
				ExchangeStrings(strings, k, k + 1);
}

void ClearStrings(Strings *strings) {
	if (!strings) return;
	for (int i = 0; i < strings->count; i++)
		DestroyString(strings->items[i]);
	DestroyItems(strings);
	strings->count = 0;
}

void ExchangeStrings(Strings *strings, int firstIndex, int secondIndex) {
	int count = CountStrings(strings);
	if (firstIndex < 0 || firstIndex >= count ||
		secondIndex < 0 || secondIndex >= count) return;
	char *tmp = strings->items[firstIndex];
	strings->items[firstIndex] = strings->items[secondIndex];
	strings->items[secondIndex] = tmp;
}

void DestroyItems(Strings *strings) {
	if (!strings) return;
	if (strings->items)
		delete[] strings->items;
	strings->items = 0;
}