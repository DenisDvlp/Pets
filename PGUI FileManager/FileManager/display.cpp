#include "pseudoGUI.h"
#include "console.h"
#include <iostream>

struct Pixel {
	char content;
	unsigned char contentColor;
	unsigned char backgroundColor;
};

struct GlobalDisplay {
	Object *mainObject;
	Pixel **pixels;
	Pixel **prevpixels;
	short width, height;
} globalDisplay;

Console console = CreateConsole();

void ShowDisplayInConsole();
void ShowDisplayInConsole(short left, short top, short right, short bottom);
void DrawObjectOnDisplay(Object *object, short x, short y, short width, short height);
void ClearDisplay();
void CopyToPrev();
void RefreshDisplay();
char Cirillic(char character);

Display CreateDisplay(short  width, short  height, unsigned char pixelSize, Color color) {
	if (width < 0) width = 0;
	if (height < 0) height = 0;
	system("color 70");
	//инициализация консоли
	console.SetSize(width + 1, height);
	console.SetTitle("Monopoly");
	console.SetFont("Lucida Console", pixelSize);
	console.Fullscreen();
	//инициализация матрицы псевдодисплея
	globalDisplay.mainObject = CreateObject();
	SetSize(globalDisplay.mainObject, width, height);
	globalDisplay.mainObject->contentColor = color;
	globalDisplay.mainObject->backgroundColor = color;
	globalDisplay.width = width;
	globalDisplay.height = height;
	globalDisplay.pixels = new Pixel*[height];
	for (int i = 0; i < height; i++)
		globalDisplay.pixels[i] = new Pixel[width];
	ClearDisplay();
	globalDisplay.prevpixels = new Pixel*[height];
	for (int i = 0; i < height; i++)
		globalDisplay.prevpixels[i] = new Pixel[width];
	CopyToPrev();
	//инициализация объекта управления псевдодисплеем
	Display display;
	display.mainParent = globalDisplay.mainObject;
	display.width = width;
	display.height = height;
	display.Refresh = RefreshDisplay;
	display.Clear = ClearDisplay;
	//возврат объекта управления псевдодисплеем
	return display;
}

void DestroyDisplay() {
	DestroyObject(globalDisplay.mainObject);
	for (int i = 0; i < globalDisplay.height; i++) {
		delete[] globalDisplay.pixels[i];
		delete[] globalDisplay.prevpixels[i];
	}
	delete[] globalDisplay.pixels;
	delete[] globalDisplay.prevpixels;
	console.SetColor(COLOR_GRAY, COLOR_GRAY);
}

void ClearDisplay() {
	char color = (globalDisplay.mainObject->transparent) ? COLOR_GRAY : globalDisplay.mainObject->backgroundColor;
	Pixel *pixel = 0;
	for (int i = 0; i < globalDisplay.height; i++)
		for (int j = 0; j < globalDisplay.width; j++) {
			pixel = globalDisplay.pixels[i] + j;
			pixel->content = ' ';
			pixel->contentColor = color;
			pixel->backgroundColor = color;
		}
}

void CopyToPrev() {
	for (int i = 0; i < globalDisplay.height; i++)
		for (int j = 0; j < globalDisplay.width; j++)
			globalDisplay.prevpixels[i][j] = globalDisplay.pixels[i][j];
}

void RefreshDisplay() {
	DrawObjectOnDisplay(globalDisplay.mainObject, 0, 0, globalDisplay.width, globalDisplay.height);
	ShowDisplayInConsole();
	CopyToPrev();
}

void ShowDisplayInConsole() {
	short left = globalDisplay.width, top = globalDisplay.height, right = 0, bottom = 0;
	for (int i = 0; i < globalDisplay.height; i++)
		for (int j = 0; j < globalDisplay.width; j++) {
			if (globalDisplay.prevpixels[i][j].content != globalDisplay.pixels[i][j].content ||
				globalDisplay.prevpixels[i][j].contentColor != globalDisplay.pixels[i][j].contentColor ||
				globalDisplay.prevpixels[i][j].backgroundColor != globalDisplay.pixels[i][j].backgroundColor) {
				if (left > j) left = j;
				if (top > i) top = i;
				if (right < j) right = j;
				if (bottom < i) bottom = i;
			}
		}
	ShowDisplayInConsole(left, top, right, bottom);
}

void ShowDisplayInConsole(short left, short top, short right, short bottom) {
	int contentColor = -1;
	int backgroundColor = -1;
	Pixel *pixel = 0;
	for (int i = top; i <= bottom; i++) {
		console.SetCursorPosition(left, i);
		for (int j = left; j <= right; j++) {
			pixel = globalDisplay.pixels[i] + j;
			if (backgroundColor != pixel->backgroundColor ||
				contentColor != pixel->contentColor) {
				contentColor = pixel->contentColor;
				backgroundColor = pixel->backgroundColor;
				console.SetColor(contentColor, backgroundColor);
			}
			std::cout << pixel->content;
		}
	}
	console.SetCursorPosition(globalDisplay.width, globalDisplay.height - 1);
}

void DrawObjectOnDisplay(Object *object, short x, short y, short width, short height) {
	if (width < 0) width = 0;
	if (height < 0) height = 0;
	short objX = GetAbsoluteX(object);
	short objY = GetAbsoluteY(object);
	short left = (objX < x) ? x : objX;
	short top = (objY < y) ? y : objY;
	short right = (objX + object->width > x + width) ? x + width - 1 : objX + object->width - 1;
	short bottom = (objY + object->height > y + height) ? y + height - 1 : objY + object->height - 1;
	for (short i = top, m = top - objY; i <= bottom; i++, m++)
		for (short j = left, n = left - objX; j <= right; j++, n++) {
			if (object->transparent && object->body[m][n] == ' ')
				continue;
			globalDisplay.pixels[i][j].content = Cirillic(object->body[m][n]);
			globalDisplay.pixels[i][j].contentColor = object->contentColor;
			if (!object->transparent)
				globalDisplay.pixels[i][j].backgroundColor = object->backgroundColor;
		}
	for (int i = 0; i < object->childrenCount; i++) {
		if (!object->children[i]->visible) continue;
		if (object->clip)
			DrawObjectOnDisplay(object->children[i], objX, objY, object->width, object->height);
		else
			DrawObjectOnDisplay(object->children[i], x, y, width, height);
	}
}

char Cirillic(char character) {
	//буква а - п
	if (character > -33 && character < -16)
		return character - 64;
	//буква р - я
	if (character > -17 && character < 0)
		return character - 16;
	//буква ё
	if (-72 == character)
		return character + 57;
	return character;
}