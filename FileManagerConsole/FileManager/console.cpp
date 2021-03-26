#include "console.h"
#include <windows.h>
#include <VersionHelpers.h>

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND hwnd = GetConsoleWindow();

wchar_t* CharToWideChar(char* text);
void Fullscreen();
void SetFont(char* text, unsigned char fontSize);
void SetTitle(char* text);
void SetColor(unsigned char font, unsigned char background);
void SetCursorPosition(unsigned short x, unsigned short y);
void SetSize(unsigned short width, unsigned short height);

Console CreateConsole() {
	Console console;
	console.Fullscreen = Fullscreen;
	console.SetTitle = SetTitle;
	console.SetFont = SetFont;
	console.SetColor = SetColor;
	console.SetCursorPosition = SetCursorPosition;
	console.SetSize = SetSize;
	return console;
}

void SetSize(unsigned short width, unsigned short height) {
	COORD size;
	size.X = width;
	size.Y = height;
  SetConsoleScreenBufferSize(handle, size);
  SMALL_RECT consoleSize = { 0, 0, width - 1, height - 1 };
  SetConsoleWindowInfo(handle, TRUE, &consoleSize);// Window Size 

  RECT displayArea;
  RECT clientRect;
  RECT windowRect;
  CONSOLE_FONT_INFO font;

  GetCurrentConsoleFont(handle, FALSE, &font);
  SystemParametersInfo(SPI_GETWORKAREA, 0, &displayArea, 0);
  GetClientRect(hwnd, &clientRect);
  GetWindowRect(hwnd, &windowRect);

  SetWindowPos(
    hwnd, 0,
    150,
    150,
    windowRect.right - windowRect.left - clientRect.right + font.dwFontSize.X * width,
    windowRect.bottom - windowRect.top - clientRect.bottom + font.dwFontSize.Y * height,
    SWP_SHOWWINDOW
  );
}

void Fullscreen() {
	Sleep(400);
	/*if (IsWindows8OrGreater())
		SendMessage(hwnd, WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	else*/
		//ShowWindow(hwnd, SW_MAXIMIZE);
}

void SetTitle(char* text) {
	wchar_t *wideText = CharToWideChar(text);
	SetConsoleTitle(wideText);
	delete[] wideText;
}

void SetColor(unsigned char font, unsigned char background) {
	SetConsoleTextAttribute(handle, (background << 4) + font);
}

void SetFont(char* text, unsigned char fontSize) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wchar_t *wideText = CharToWideChar(text);
	wcscpy_s(cfi.FaceName, 32, wideText);
	SetCurrentConsoleFontEx(handle, FALSE, &cfi);
	delete[] wideText;
}

void SetCursorPosition(unsigned short x, unsigned short y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

wchar_t* CharToWideChar(char* text) {
	size_t length = strlen(text) + 1;
	wchar_t* wideText = new wchar_t[length];
	size_t outSize;
	mbstowcs_s(&outSize, wideText, length, text, length - 1);
	return wideText;
}