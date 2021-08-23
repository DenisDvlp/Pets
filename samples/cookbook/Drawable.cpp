#include "Drawable.h"

void Drawable::SetPosition(POINT position)
{
	this->position = position;
}

void Drawable::SetX(int x)
{
	position.x = x;
}

void Drawable::SetY(int y)
{
	position.y = y;
}

void Drawable::SetSize(POINT size)
{
	SetWidth(size.x);
	SetHeight(size.y);
}

void Drawable::SetWidth(int width)
{
	size.x = width < 0 ? 0 : width;
}

void Drawable::SetHeight(int height)
{
	size.y = height < 0 ? 0 : height;
}

void Drawable::SetContent(string content)
{
	this->content = content;
	SetAutosize(autosize);
}

void Drawable::SetColor(COLOR color)
{
	this->color = color;
}

void Drawable::SetBackground(COLOR background)
{
	this->background = background;
}

void Drawable::SetVisible(bool value)
{
	this->visible = value;
}

void Drawable::SetAutosize(bool value)
{
	this->autosize = value;
	if (!value) return;
	SetSize(TextDrawSize(content));
}

POINT Drawable::Position()
{
	return position;
}

POINT Drawable::Size()
{
	return size;
}

string Drawable::Content()
{
	return content;
}

COLOR Drawable::Color()
{
	return color;
}

COLOR Drawable::Background()
{
	return background;
}

bool Drawable::Visible()
{
	return visible;
}

bool Drawable::Autosize()
{
	return autosize;
}

POINT Drawable::TextDrawSize(string text)
{
	int width = 1;
	int height = 0;
	int len = 0;
	for (int i = 0; i < text.size(); i++) {
		if (text[i] != '\n') {
			len++;
			continue;
		}
		width++;
		if (len > height) height = len;
		len = 0;
	}
	if (len > height) height = len;
	return { height , width };
}
