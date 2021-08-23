#include "Screen.h"
#include "OS.h"

int main() {
	OS os;
	os.Run();

	/*Screen screen;
	screen.SetSize(50, 20);

	Drawable *drawable = new Drawable();
	drawable->SetPosition({ 2, 4 });
	drawable->SetContent("Hello\nHow are you?");
	drawable->SetSize({ 10, 5 });
	drawable->SetColor(COLOR_CYAN);
	drawable->SetBackground(COLOR_RED);
	screen.Add(drawable);

	drawable = new Drawable();
	drawable->SetContent("ahaha");
	drawable->SetPosition({ 1, 1 });
	drawable->SetBackground(COLOR_BLUE);
	screen.Add(drawable);

	screen.Draw();

	drawable->SetPosition({ 3, 8 });

	screen.Draw();*/

	return 0;
}