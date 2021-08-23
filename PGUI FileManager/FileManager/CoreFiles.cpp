#include "coremanager.h"
#include "utils.h"

Files* CreateFiles() {
	Files *files = new Files;
	files->count = 0;
	files->list = 0;
	return files;
}

void DestroyFiles(Files *&files) {
	if (!files) return;
	ClearFiles(files);
	delete files;
	files = 0;
}

void AddFile(Files *files, char *string, bool isDir) {
	if (!files) return;
	File **list = new File*[files->count + 1];
	for (int i = 0; i < files->count; i++) {
		list[i] = CreateFile();
		list[i]->name = S.Copy(files->list[i]->name);
		list[i]->isDir = files->list[i]->isDir;
	}
	list[files->count] = CreateFile();
	list[files->count]->name = S.Copy(string);
	list[files->count]->isDir = isDir;
	if (files->list) delete[] files->list;
	files->list = list;
	files->count++;
}

void ClearFiles(Files *files) {
	if (!files) return;
	for (int i = 0; i < files->count; i++)
		DestroyFile(files->list[i]);
	if (files->list) delete[] files->list;
	files->list = 0;
	files->count = 0;
}
