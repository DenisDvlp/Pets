#include "StringUtils.h"

int GetLength(char *string) {
	if (!string)
		return 0;
	return strlen(string);
}

char* CreateCopyString(char *string) {
	int length = GetLength(string) + 1;
	char *result = new char[length];
	if (string)
		strcpy_s(result, length, string);
	return result;
}

void CopyString(char **dst, char *src) {
	if (*dst)
		delete[] * dst;
	*dst = CreateCopyString(src);
}