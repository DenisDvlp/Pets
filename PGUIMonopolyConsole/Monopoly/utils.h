#pragma once
#include <iostream>

bool IsEqual(const char *first, const char *second);
int GetLength(const char *string);
void CopyString(char *&dst, char *src);
char* ConcatStrings(int count, char *string1, ...);
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