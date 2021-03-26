#pragma once

enum CoreSide {
	CORE_LEFT,
	CORE_RIGHT
};

struct File {
	bool isDir;
	char *name;
};

File* CreateFile();
void DestroyFile(File *&file);

struct Files {
	File **list;
	short count;
};
Files* CreateFiles();
void DestroyFiles(Files *&files);
void AddFile(Files *files, char *string, bool isDir);
void ClearFiles(Files *files);

struct Core {
	char *leftPath, *rightPath;
	Files *leftFiles, *rightFiles;
};
Core* CreateCore();
void BuildFiles(Core *core, CoreSide side);
void DestroyCore(Core *&core);