#include "utils.h"
#include <cstdio>
#include <iostream>
#include <direct.h>
#include <io.h>

FileFunctions F = {
	DirList,
	FileList,
	DirSize,
	FileSize,
	FileExists,
	DeleteDir,
	DeleteFile,
	CopyDir,
	CopyFile,
	MoveDir,
	MoveFile,
	GetCurrentDir,
	SetCurrentDir,
	SetParentDir,
	SetRootDir,
	GetFileNameFromPath,
	GetDirFromPath,
	MakeDir,
	MakeFile
};

Strings* DirList(char *dirpath, char *filter) {
	Strings *dirs = CreateStrings();
	//добавление "/" в путь
	char *path = ConcatStrings(3, dirpath, "/", filter);
	//поиск
	_finddata_t  data;
	intptr_t h;
	h = _findfirst(path, &data);
	if (h != -1) {
		do
			if (_A_SUBDIR == (data.attrib & _A_SUBDIR) &&
				_A_HIDDEN != (data.attrib & _A_HIDDEN) &&
				CompareStrings(data.name, ".", true) &&
				CompareStrings(data.name, "..", true))
				AddString(dirs, data.name);
		while (!_findnext(h, &data));
		_findclose(h);
	}
	DestroyString(path);
	return dirs;
}

Strings* FileList(char *dirpath, char *filter) {
	Strings *files = CreateStrings();
	//добавление "/" в путь
	char *path = ConcatStrings(3, dirpath, "/", filter);
	//поиск
	_finddata_t  data;
	intptr_t h;
	h = _findfirst(path, &data);
	if (h != -1) {
		do
			if (_A_SUBDIR != (data.attrib & _A_SUBDIR) &&
				_A_HIDDEN != (data.attrib & _A_HIDDEN))
				AddString(files, data.name);
		while (!_findnext(h, &data));
		_findclose(h);
	}
	DestroyString(path);
	return files;
}

void MakeDir(char *dirpath) {
	char *current = GetCurrentDir();
	Strings *dirs = StringsFromString(dirpath, "/\\");
	for (int i = 0; i < dirs->count; i++) {
		_mkdir(dirs->items[i]);
		SetCurrentDir(dirs->items[i]);
	}
	SetCurrentDir(current);
}

long long DirSize(char *dirpath, bool recursive) {
	if (!dirpath) return 0;
	//добавление "/" в путь
	char *correctpath = ConcatTwoStrings(dirpath, "/");
	char *path = ConcatTwoStrings(correctpath, "*");
	//поиск
	_finddata_t  data;
	intptr_t h;
	h = _findfirst(path, &data);
	long long size = 0;
	if (h != -1) {
		do
		{
			if (recursive &&
				_A_SUBDIR == (data.attrib & _A_SUBDIR) &&
				_A_ARCH != (data.attrib & _A_ARCH) &&
				_A_SYSTEM != (data.attrib & _A_SYSTEM) &&
				_A_HIDDEN != (data.attrib & _A_HIDDEN) &&
				CompareStrings(data.name, ".", true) && CompareStrings(data.name, "..", true)) {
				//если папка
				char *dir = ConcatStrings(2, correctpath, data.name);
				size += DirSize(dir, recursive);
				DestroyString(dir);
			}
			else
				//если не папка
				size += data.size;
		} while (!_findnext(h, &data));
		_findclose(h);
	}
	DestroyString(correctpath);
	DestroyString(path);
	return size;
}

long long FileSize(char *filepath) {
	if (!FileExists(filepath)) return 0;
	intptr_t h;
	_finddata_t  data;
	h = _findfirst(filepath, &data);
	_findclose(h);
	return data.size;
}

bool FileExists(char *filepath) {
	if (!filepath) return false;
	FILE *file = 0;
	int code = fopen_s(&file, filepath, "r");
	if (code == ENOENT) return false;
	if (!code) fclose(file);
	return true;
}

void DeleteDir(char *dirpath, bool recursive) {
	Strings *files = FileList(dirpath, "*");
	for (int i = 0; i < files->count; i++) {
		char *nextfile = ConcatStrings(3, dirpath, "/", files->items[i]);
		DeleteFile(nextfile);
		DestroyString(nextfile);
	}
	if (recursive) {
		Strings *dirs = DirList(dirpath, "*");
		for (int i = 0; i < dirs->count; i++) {
			char *nextdir = ConcatStrings(3, dirpath, "/", dirs->items[i]);
			DeleteDir(nextdir, true);
			DestroyString(nextdir);
		}
	}
	_rmdir(dirpath);
}

void DeleteFile(char *filepath) {
	if (filepath) remove(filepath);
}

void CopyDir(char *dirsrc, char *dirdst) {
	Strings *dirs = DirList(dirsrc, "*");
	for (int i = 0; i < dirs->count; i++) {
		char *nextdirsrc = ConcatStrings(3, dirsrc, "/", dirs->items[i]);
		char *nextdirdst = ConcatStrings(3, dirdst, "/", dirs->items[i]);
		CopyDir(nextdirsrc, nextdirdst);
		DestroyString(nextdirsrc);
		DestroyString(nextdirdst);
	}
	MakeDir(dirdst);
	Strings *files = FileList(dirsrc, "*");
	for (int i = 0; i < files->count; i++) {
		char *filesrc = ConcatStrings(3, dirsrc, "/", files->items[i]);
		char *filedst = ConcatStrings(3, dirdst, "/", files->items[i]);
		CopyFile(filesrc, filedst);
		DestroyString(filesrc);
		DestroyString(filedst);
	}
	DestroyStrings(files);
	DestroyStrings(dirs);
}

void CopyFile(char *filesrc, char *filedst) {
	FILE *src = 0;
	FILE *dst = 0;
	if (fopen_s(&src, filesrc, "rb")) return;
	if (fopen_s(&dst, filedst, "wb")) {
		fclose(src);
		return;
	}
	int size = 65536;
	char *bytes = CreateString(size);
	while (!feof(src)) {
		int readCount = fread(bytes, 1, size, src);
		fwrite(bytes, 1, readCount, dst);
	}
	DestroyString(bytes);
	fclose(src);
	fclose(dst);
}

void MakeFile(char *filepath) {
	FILE *file = 0;
	if (fopen_s(&file, filepath, "wb")) return;
	fclose(file);
}

void MoveDir(char *dirsrc, char *dirdst) {
	CopyDir(dirsrc, dirdst);
	DeleteDir(dirsrc, true);
}

void MoveFile(char *filesrc, char *filedst) {
	CopyFile(filesrc, filedst);
	DeleteFile(filesrc);
}

char* GetCurrentDir() {
	char* dir = CreateString(261);
	_getcwd(dir, 261);
	char *str = Replace(dir, "\\", "/", 0);
	DestroyString(dir);
	return str;
}

char* SetCurrentDir(char *dirpath) {
	if (dirpath) _chdir(dirpath);
	char *dir = GetCurrentDir();
	return dir;
}

char* SetParentDir() {
	char *current = GetCurrentDir();
	char *dir = ConcatTwoStrings(current, "/..");
	char *parent = SetCurrentDir(dir);
	DestroyString(current);
	DestroyString(dir);
	return parent;
}

char* SetRootDir() {
	char *prev = 0;
	char *root = GetCurrentDir();
	do {
		prev = CopyString(root);
		DestroyString(root);
		root = SetParentDir();
	} while (CompareStrings(root, prev, false));
	DestroyString(prev);
	return root;
}

char* GetFileNameFromPath(char *path) {
	char *str = Replace(path, "\\", "/", 0);
	int index = LastIndexOfString(str, "/");
	int length = LengthString(str);
	char *filename = Substring(str, index + 1, length);
	DestroyString(str);
	return filename;
}

char* GetDirFromPath(char *path) {
	char *str = Replace(path, "\\", "/", 0);
	int index = LastIndexOfString(str, "/");
	char *dir = Substring(str, 0, index);
	DestroyString(str);
	return dir;
}