#include "Console.h"

Console::Console(){
	DisableSelection().fontSize(14).size(80, 40);
}
Console::Console(CSize size){
	DisableSelection().fontSize(14).size(size);
}
Console::Console(CSize size, short fontSize) {
	DisableSelection().fontSize(fontSize).size(size);
}
Console::Console(int width, int height){
	DisableSelection().fontSize(14).size(width, height);
}
Console::Console(int width, int height, short fontSize){
	DisableSelection().fontSize(fontSize).size(width, height);
}
Console& Console::DisableSelection() {
	DWORD dwPreviousMode = 0;
	GetConsoleMode(hIn, &dwPreviousMode);
	SetConsoleMode(hIn, (dwPreviousMode | ENABLE_MOUSE_INPUT) & ~ENABLE_QUICK_EDIT_MODE);
	return me;
}
Console& Console::setFontSize(short size) {
	if (size < 5) size = 5;
	if (size > 40) size = 40;
	CONSOLE_FONT_INFOEX font = { 0 };
	font.cbSize = sizeof(font);
	font.dwFontSize.Y = size;
	font.FontWeight = FW_NORMAL;
	_tcscpy_s(font.FaceName, lstrlen(TEXT("Lucida Console")) + 1, TEXT("Lucida Console"));
	SetCurrentConsoleFontEx(hOut, FALSE, &font);
	SetWindowPos(hwnd, 0, 0, 0, 20000, 20000, SWP_SHOWWINDOW | SWP_NOMOVE);
	return me;
}
CSize Console::getFontSize() {
	CONSOLE_FONT_INFO font;
	GetCurrentConsoleFont(hOut, FALSE, &font);
	return CSize(font.dwFontSize.X, font.dwFontSize.Y);
}
Console& Console::size(int width, int height){
	if (width < 14) width = 14;
	if (height < 1) height = 1;
	if (width > 500) width = 500;
	if (height > 200) height = 200;
	me._size.set(width, height);
	COORD bufferSize = { width, height };
	SMALL_RECT consoleSize = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hOut, TRUE, &consoleSize);// Window Size 
	SetConsoleScreenBufferSize(hOut, bufferSize);  // Buffer Size
	SetWindowPos(hwnd, 0, 0, 0, 20000, 20000, SWP_SHOWWINDOW);
	return me;
}
CPoint Console::mousePosToCursorPos(CPoint position){
	CSize font = getFontSize();
	return CPoint(position.x() / font.width() - 2, position.y() / font.height() - 2);
}
Console& Console::draw(Canvas &canvas){
	SMALL_RECT drawableRect = { 0, 0, canvas.width(), canvas.height() };
	COORD bufferSize = { canvas.width(), canvas.height() };
	WriteConsoleOutput(hOut, canvas.canvas, bufferSize, { 0, 0 }, &drawableRect);
	return me;
}
