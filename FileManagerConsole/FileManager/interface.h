#pragma once
#include "pseudoGUI.h"
#include "components.h"
#include "actions.h"

struct Interface {
	void(*Run)();
};

Interface CreateInterface();
void DestroyInterface();