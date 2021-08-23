#include "coremanager.h"
#include "utils.h"

Core* CreateCore() {
	Core *core = new Core;
	core->leftFiles = CreateFiles();
	core->rightFiles = CreateFiles();
	core->leftPath = F.GetCurrentDir();
	core->rightPath = F.GetCurrentDir();

	BuildFiles(core, CORE_LEFT);
	BuildFiles(core, CORE_RIGHT);

	return core;
}

void DestroyCore(Core *&core) {
	if (!core) return;
	DestroyFiles(core->leftFiles);
	DestroyFiles(core->rightFiles);
	S.Destroy(core->leftPath);
	S.Destroy(core->rightPath);
	delete core;
	core = 0;
}

void BuildFiles(Core *core, CoreSide side) {
	char *dir = 0;
	Files *fls = 0;
	if (side == CORE_LEFT) {
		dir = core->leftPath;
		fls = core->leftFiles;
	}
	else {
		dir = core->rightPath;
		fls = core->rightFiles;
	}
	Strings *dirs = F.DirList(dir, "*");
	Strings *files = F.FileList(dir, "*");
	ClearFiles(fls);
	for (int i = 0; i < dirs->count; i++)
		AddFile(fls, dirs->items[i], true);
	for (int i = 0; i < files->count; i++)
		AddFile(fls, files->items[i], false);
	SS.Destroy(dirs);
	SS.Destroy(files);
}