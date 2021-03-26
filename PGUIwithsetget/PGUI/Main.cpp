#include <iostream>
#include "Console.h"
#include "Collection.h"
using std::cout;
using std::endl;

int main() {
	Console console(80, 40);
	Canvas canvas(console.size());
	CStrings ss("asd\nsdfgghgf\nu");
	canvas.drawText(CRect(4, 2, 10, 50), ss, COLOR_YELLOW, COLOR_TRANSPARENT, 0);
	console.draw(canvas);
	getchar();
	return 0;
}