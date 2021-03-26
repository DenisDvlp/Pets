#pragma once

struct Console {
	void (*Fullscreen)();
	void (*SetTitle)(char* title);
	void (*SetFont)(char* font, unsigned char fontSize);
	void (*SetColor)(unsigned char font, unsigned char background);
	void (*SetCursorPosition)(unsigned short x, unsigned short y);
	void (*SetSize)(unsigned short width, unsigned short height);
};

Console CreateConsole();