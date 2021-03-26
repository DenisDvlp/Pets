#include "objects.h"
#include <cstring>
#include <conio.h>

struct Dialog {
	Block 
		body, yesButton,
		noButton, dialogText, 
		yesText, noText;
};

char Cirillic(unsigned char character);
void GetTextDrawSize(char *text, unsigned short &width, unsigned short &height);

/*Block*/
void SetStroke(Block &block, StrokeType strokeType, char filling = ' ');
void SetFilling(Block &block, char filling);
void SetContent(Block &block, char *content);

/*Text*/
Text* CreateText(unsigned short width, unsigned short height,
	unsigned char contentColor, unsigned char backgroundColor) {
	Text *text = new Text;
	text->body = CreateBlock(width, height, contentColor, backgroundColor);
	text->content = 0;
	text->autosize = false;
	return text;
}

void DestroyText(Text* &text) {
	DestroyBlock(text->body);
	delete[] text;
}

void SetContent(Text *text, char *content) {
	int length = strlen(content);
	char *tmp = new char[length + 1];
	strcpy_s(tmp, length + 1, content);
	if (text->content)
		delete[] text->content;
	text->content = tmp;
	SetFilling(text->body, ' ');
	SetContent(text->body, content);
}

//функция подгоняет размеры объекта под текст
void SetAutosize(Text *text, bool autosize) {
	//если авторазмер включён и функция запрашивает его включить снова - выход
	if (text->autosize && autosize) return;
	text->autosize = autosize;
	//если авторазмер выключен, то дальнейшие расчёты не нужны - выход
	if(!autosize) return;
	//определяем высоту и ширину текста,
	//выражающуюся в количестве строк и максимальной длине символов в строке
	unsigned short width = 0, height = 0;
	GetTextDrawSize(text->content, width, height);
	Resize(text->body, width, height);
	SetContent(text->body, text->content);
}

void Resize(Text *text, unsigned short width, unsigned short height) {
	if (text->autosize ||
		text->body.width == width &&
		text->body.height == height) return;
	Resize(text->body, width, height);
	SetFilling(text->body, ' ');
	SetContent(text->body, text->content);
}

/*Rectangle*/

Rectangle* CreateRectangle(unsigned short width, unsigned short height,
	unsigned char contentColor, unsigned char backgroundColor) {
	Rectangle *rectangle = new Rectangle;
	rectangle->body = CreateBlock(width, height, contentColor, backgroundColor);
	rectangle->strokeType = STROKE_NONE;
	rectangle->filling = ' ';
	return rectangle;

}
void DestroyRectangle(Rectangle* &rectangle) {
	DestroyBlock(rectangle->body);
	delete[] rectangle;
}

void SetStroke(Rectangle *rectangle, StrokeType strokeType) {
	rectangle->strokeType = strokeType;
	SetStroke(rectangle->body, strokeType, rectangle->filling);
}

void SetFilling(Rectangle *rectangle, char filling) {
	rectangle->filling = filling;
	SetFilling(rectangle->body, filling);
}

void Resize(Rectangle *rectangle, unsigned short width, unsigned short height) {
	Resize(rectangle->body, width, height);
	SetFilling(rectangle->body, rectangle->filling);
	SetStroke(rectangle->body, rectangle->strokeType, rectangle->filling);
}

/*Button*/

Button* CreateButton(unsigned short width, unsigned short height,
	unsigned char contentColor, unsigned char backgroundColor) {
	Button *button = new Button;
	return button;
}
void SetActivated(Button *button, bool activated) {

}

void Resize(Button *button, unsigned short width, unsigned short height) {

}

/*Block*/

void SetStroke(Block &block, StrokeType strokeType, char filling) {
	char vert = filling;
	char top = filling;
	char bottom = filling;
	char leftTopConer = filling;
	char rightTopConer = filling;
	char leftBottomConer = filling;
	char rightBottomConer = filling;
	switch (strokeType) {
	case STROKE_THIN:
		vert = char(179);
		top = char(196);
		bottom = char(196);
		leftTopConer = char(218);
		rightTopConer = char(191);
		leftBottomConer = char(192);
		rightBottomConer = char(217);
		break;
	case STROKE_SEMIBOLD:
		vert = char(186);
		top = char(205);
		bottom = char(205);
		leftTopConer = char(201);
		rightTopConer = char(187);
		leftBottomConer = char(200);
		rightBottomConer = char(188);
		break;
	case STROKE_BOLD:
		vert = char(219);
		top = char(223);
		bottom = char(220);
		leftTopConer = char(219);
		rightTopConer = char(219);
		leftBottomConer = char(219);
		rightBottomConer = char(219);
		break;
	}
	block.content[0][0] = leftTopConer;
	block.content[0][block.width - 1] = rightTopConer;
	block.content[block.height - 1][0] = leftBottomConer;
	block.content[block.height - 1][block.width - 1] = rightBottomConer;
	for (int i = 1; i < block.width - 1; i++) {
		block.content[0][i] = top;
		block.content[block.height - 1][i] = bottom;
	}
	for (int i = 1; i < block.height - 1; i++) {
		block.content[i][0] = vert;
		block.content[i][block.width - 1] = vert;
	}

}
void SetFilling(Block &block, char filling) {
	for (int i = 1; i < block.height; i++)
		for (int j = 1; j < block.width; j++)
			block.content[i][j] = Cirillic(filling);
}
void SetContent(Block &block, char *content) {
	if (!content) return;
	int i = 0, j = 0, k = 0;
	while (i < block.height) {
		if (content[k] == 0)
			break;
		if (content[k] == '\n' || j >= block.width) {
			i++;
			j = 0;
			k++;
			continue;
		}
		block.content[i][j++] = Cirillic(content[k++]);
	}
}

char Cirillic(unsigned char character) {
	if (character > 223 && character < 240)
		return character - 64;
	if (character > 239 && character < 256)
		return character - 16;
	if (character > 191 && character < 224)
		return character - 64;
	return character;
}

void GetTextDrawSize(char *text, unsigned short &width, unsigned short &height) {
	//определяем высоту и ширину
	height = 0; //количество строк в тексте, будущая высота
	width = 0;  //максимальное количество букв в строке, будущая ширина
	if (!text) return;
	int length = strlen(text);
	char *tmp = new char[length + 1];
	strcpy_s(tmp, length + 1, text);
	char delims[] = "\n";
	char *context = NULL;
	char *string = strtok_s(tmp, delims, &context);
	while (string) {
		height++;
		string = strtok_s(0, delims, &context);
		if (string) {
			length = strlen(string);
			if (length > width) width = length;
		}
	}
	delete[] tmp;
}