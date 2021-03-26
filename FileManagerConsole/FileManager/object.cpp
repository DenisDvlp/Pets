
#include "utils.h"
#include "pseudoGUI.h"

void BuildBody(Object *object);
void ClearBody(Object *object);
void DrawContent(Object *object);
void DrawFilling(Object *object);
void DrawStroke(Object *object);
void AddChild(Object *object, Object *child);
void DeleteChild(Object *object, Object *child);
void CalculateSizeOfContent(char *content, short &width, short &height);
void CheckAutosize(Object *object);

Object* CreateObject() {
	Object *object = new Object;
	object->body = 0;//NULL
	object->x = 0;
	object->y = 0;
	object->width = 0;
	object->height = 0;
	object->contentColor = COLOR_BLACK;
	object->backgroundColor = COLOR_BLACK;
	object->stroke = STROKE_NONE;
	object->contentHorizAlign = ALIGN_LEFT;
	object->contentVertAlign = ALIGN_TOP;
	object->fill = ' ';
	object->content = 0;//NULL
	object->autosize = false;
	object->visible = true;
	object->transparent = false;
	object->clip = false;
	object->parent = 0;//NULL
	object->children = 0;
	object->childrenCount = 0;//NULL
	return object;
}

void DestroyObject(Object *object) {
	if (!object) return;
	SetParent(object, 0);
	while (object->childrenCount)
		DestroyObject(object->children[0]);
	SetSize(object, 0, 0);
	delete object;
}

int GetAbsoluteX(Object *object) {
	if (!object) return 0;
	int x = object->x;
	if (object->parent)
		x += GetAbsoluteX(object->parent);
	return x;
}

int GetAbsoluteY(Object *object) {
	if (!object) return 0;
	int y = object->y;
	if (object->parent)
		y += GetAbsoluteY(object->parent);
	return y;
}

void SetSize(Object *object, short width, short height) {
	if (!object || object->height == height && object->width == width) return;
	if (width < 0) width = 0;
	if (height < 0) height = 0;
	DeleteArray(object->body, object->height);
	object->width = width;
	object->height = height;
	object->body = CreateCharArray(height, width);
	BuildBody(object);
}

void SetParent(Object *object, Object *parent) {
	if (!object) return;
	if (parent)
		AddChild(parent, object);
	else
		if (object->parent)
			DeleteChild(object->parent, object);
	object->parent = parent;
}

void AddChild(Object *object, Object *child) {
	if (!object || !child) return;
	Object **newChildren = new Object*[object->childrenCount + 1];
	for (int i = 0; i < object->childrenCount; i++)
		newChildren[i] = object->children[i];
	newChildren[object->childrenCount++] = child;
	if (object->childrenCount)
		delete[] object->children;
	object->children = newChildren;
}

void DeleteChild(Object *object, Object *child) {
	if (!object || !child || !object->childrenCount) return;
	for (int i = 0, j = 0; i < object->childrenCount; i++)
		if (object->children[i] != child)
			object->children[j++] = object->children[i];
	object->childrenCount--;
	if (!object->childrenCount) {
		delete[] object->children;
		object->children = 0;
	}
}

void SetStroke(Object *object, StrokeType strokeType) {
	if (!object) return;
	object->stroke = strokeType;
	BuildBody(object);
}

void SetHorizontalAlign(Object *object, Align align) {
	if (!object) return;
	object->contentHorizAlign = align;
	BuildBody(object);
}

void SetVerticalAlign(Object *object, Align align) {
	if (!object) return;
	object->contentVertAlign = align;
	BuildBody(object);
}

void SetFilling(Object *object, char fill) {
	if (!object) return;
	object->fill = fill;
	BuildBody(object);
}

void SetContent(Object *object, char *content) {
	if (!object || IsEqual(object->content, content)) return;
	CopyString(object->content, content);
	CheckAutosize(object);
	BuildBody(object);
}

void SetAutosize(Object *object, bool autosize) {
	if (!object || object->autosize && autosize) return;
	object->autosize = autosize;
	if (!autosize) return;
	CheckAutosize(object);
	BuildBody(object);
}

void CheckAutosize(Object *object) {
	if (!object->autosize) return;
	short width = 0, height = 0;
	CalculateSizeOfContent(object->content, width, height);
	SetSize(object, width, height);
}

void CalculateSizeOfContent(char *content, short &width, short &height) {
	int count = 0;
	char **strings = GetStringsFromText(content, "\n", count);
	height = count; //количество строк в тексте
	width = 0; //максимальное количество букв в строке
	for (int i = 0, length = 0; i < height; i++) {
		length = GetLength(strings[i]);
		if (width < length) width = length;
	}
	DeleteArray(strings, height);
}

void BuildBody(Object *object) {
	if (!object) return;
	ClearBody(object);
	DrawContent(object);
	DrawFilling(object);
	DrawStroke(object);
}

void ClearBody(Object *object) {
	if (!object) return;
	for (int i = 0; i < object->height; i++)
		for (int j = 0; j < object->width; j++)
			object->body[i][j] = ' ';
}

void DrawContent(Object *object) {
	if (!object || !object->content) return;
	int count = 0;
	char **strings = GetStringsFromText(object->content, "\n", count);
	int m = 0;
	switch (object->contentVertAlign) {
	case ALIGN_CENTER:
		m = (count - object->height) / 2;
		break;
	case ALIGN_BOTTOM:
		m = count - object->height;
		break;
	case ALIGN_TOP:
	default:
		m = 0;
		break;
	}
	for (int i = 0, length = 0, n = 0; i < object->height; i++, m++) {
		if (m < 0 || m >= count) continue;
		length = GetLength(strings[m]);
		switch (object->contentHorizAlign) {
		case ALIGN_CENTER:
			n = (length - object->width) / 2;
			break;
		case ALIGN_RIGHT:
			n = length - object->width;
			break;
		case ALIGN_LEFT:
		default:
			n = 0;
			break;
		}
		for (int j = 0; j < object->width; j++, n++) {
			if (n < 0 || n >= length) continue;
			object->body[i][j] = strings[m][n];
		}
	}
	DeleteArray(strings, count);
}

void DrawFilling(Object *object) {
	if (!object || object->fill == ' ') return;
	for (int i = 0; i < object->height; i++)
		for (int j = 0; j < object->width; j++)
			if(object->body[i][j] == ' ')
				object->body[i][j] = object->fill;
}

void DrawStroke(Object *object) {
	if (!object || !object->body ||
		object->stroke != STROKE_THIN &&
		object->stroke != STROKE_SEMIBOLD &&
		object->stroke != STROKE_BOLD) return;
	char vert = 0;
	char top = 0;
	char bottom = 0;
	char leftTopConer = 0;
	char rightTopConer = 0;
	char leftBottomConer = 0;
	char rightBottomConer = 0;
	switch (object->stroke) {
	case STROKE_THIN:
		vert = CHAR_STICK_VERT;
		top = CHAR_STICK_HOR;
		bottom = CHAR_STICK_HOR;
		leftTopConer = CHAR_STICK_TOP_LEFT;
		rightTopConer = CHAR_STICK_TOP_RIGHT;
		leftBottomConer = CHAR_STICK_BOT_LEFT;
		rightBottomConer = CHAR_STICK_BOT_RIGHT;
		break;
	case STROKE_SEMIBOLD:
		vert = CHAR_DSTICK_VERT;
		top = CHAR_DSTICK_HOR;
		bottom = CHAR_DSTICK_HOR;
		leftTopConer = CHAR_DSTICK_TOP_LEFT;
		rightTopConer = CHAR_DSTICK_TOP_RIGHT;
		leftBottomConer = CHAR_DSTICK_BOT_LEFT;
		rightBottomConer = CHAR_DSTICK_BOT_RIGHT;
		break;
	case STROKE_BOLD:
		vert = CHAR_FULL;
		top = CHAR_FULL_TOP;
		bottom = CHAR_FULL_BOT;
		leftTopConer = CHAR_FULL;
		rightTopConer = CHAR_FULL;
		leftBottomConer = CHAR_FULL;
		rightBottomConer = CHAR_FULL;
		break;
	}
	if (object->width > 1 && object->height > 1) {
		object->body[0][0] = leftTopConer;
		object->body[0][object->width - 1] = rightTopConer;
		object->body[object->height - 1][0] = leftBottomConer;
		object->body[object->height - 1][object->width - 1] = rightBottomConer;
	}
	for (int i = 1; i < object->width - 1; i++) {
		object->body[0][i] = top;
		object->body[object->height - 1][i] = bottom;
	}
	for (int i = 1; i < object->height - 1; i++) {
		object->body[i][0] = vert;
		object->body[i][object->width - 1] = vert;
	}
}