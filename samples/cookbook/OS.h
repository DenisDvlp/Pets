#pragma once
#include <windows.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include "Block.h"
#include "Screen.h"

using std::vector;
using std::cout;
using std::endl;

class OS {

	Screen screen;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	vector<Block*> blocks; 
	Drawable *drawable = nullptr;

	POINT GetMousePosition() {
		POINT point = { 0, 0 };
		GetCursorPos(&point);
		ScreenToClient(GetConsoleWindow(), &point);
		return point;
	}

	POINT GetMouseCursorPosition() {
		CONSOLE_FONT_INFO cursor;
		GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), false, &cursor);
		POINT point = GetMousePosition();
		point.x = point.x / cursor.dwFontSize.X - 2;
		point.y = point.y / cursor.dwFontSize.Y - 2;
		return point;
	}

	void MouseMove(POINT position, bool down) {
		if (down) {
			drawable->SetPosition(position);
			screen.Draw();
		}
		//cout << "MouseMove" << endl;
	}
	void MouseDown(POINT position) {
		//cout << "MouseDown(" << position.x << ";" << position.y << ")" << endl;
	}
	void MouseUp(POINT position) {
		//cout << "MouseUp" << endl;
	}

	void CheckMouse() {
		static POINT point = { 0, 0 };
		static bool LKM = false;

		static POINT pointPrev = { 0, 0 };
		static bool LKMPrev = false;


		point = GetMouseCursorPosition();
		LKM = HIWORD(GetKeyState(VK_LBUTTON));
		bool IsOutOfScreen = point.x < 0 || point.y < 0 || point.x > screen.Size().x || point.y > screen.Size().y;

		if (!IsOutOfScreen && LKM && !LKMPrev)
			MouseDown(point);
		if (!IsOutOfScreen && !LKM && LKMPrev)
			MouseUp(point);
		if (!IsOutOfScreen && (point.x != pointPrev.x || point.y != pointPrev.y))
			MouseMove(point, LKM);

		LKMPrev = LKM;
		pointPrev = point;
	}

public:

	OS() {
		screen.SetSize(50, 20);

		drawable = new Drawable();
		drawable->SetContent("ahaha");
		drawable->SetPosition({ 1, 1 });
		drawable->SetBackground(COLOR_BLUE);
		screen.Add(drawable);

		drawable = new Drawable();
		drawable->SetPosition({ 2, 4 });
		drawable->SetContent("Hello\nHow are you?");
		drawable->SetSize({ 10, 5 });
		drawable->SetColor(COLOR_CYAN);
		drawable->SetBackground(COLOR_RED);
		screen.Add(drawable);

		screen.Draw();
	}

	void AddForm(Block *block) {
		blocks.push_back(block);
	}

	void Run() {
		while (1) {
			CheckMouse();
		}
	}
};