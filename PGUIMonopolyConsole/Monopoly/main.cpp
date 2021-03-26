#include "interface.h"
#include <iostream>
using namespace std;

void main() {
	Interface interface = CreateInterface();
	interface.Run();
	DestroyInterface();
}