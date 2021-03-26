#include "coremanager.h"
#include "utils.h"

File* CreateFile() {
	File *core = new File;
	core->name = 0;
	core->isDir = false;

	return core;
}

void DestroyFile(File *&file) {
	if (!file) return;
	S.Destroy(file->name);
	delete file;
	file = 0;
}