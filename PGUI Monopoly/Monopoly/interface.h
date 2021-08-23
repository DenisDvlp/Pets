#pragma once
#include "pseudoGUI.h"
#include "components.h"
#include "dispatcher.h"
#include "gamecore.h"

struct Interface {
	void(*Run)();
};

Interface CreateInterface();
void DestroyInterface();