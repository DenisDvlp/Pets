#include "Canvas.h"

void Canvas::info(CPoint & position, char character, COLOR color, COLOR background)
{
	info(position.x(), position.y(), character, color, background);
}

void Canvas::info(int x, int y, char character, COLOR color, COLOR background)
{
	if (x < 0 || y < 0 || x >= width() || y >= height() ||
		color == COLOR_TRANSPARENT && background == COLOR_TRANSPARENT) return;

	int index = y * width() + x;

	canvas[index].Char.UnicodeChar = color == COLOR_TRANSPARENT ? ' ' : character;

	if (color != COLOR_TRANSPARENT)
		canvas[index].Attributes = canvas[index].Attributes & 240 | color;

	if (background != COLOR_TRANSPARENT)
		canvas[index].Attributes = canvas[index].Attributes & 15 | background << 4;
}

Canvas::Canvas() {}
Canvas::Canvas(CSize size) {
	me.size(size);
}
Canvas::Canvas(int width, int height) {
	size(width, height);
}
Canvas::~Canvas() {
	size(0, 0);
}
Canvas& Canvas::clear(COLOR color) {
	for (int i = 0; i < size().square(); i++) {
		canvas[i].Char.UnicodeChar = ' ';
		canvas[i].Attributes = color;
	}
	return me;
}
Canvas& Canvas::size(int width, int height){
	if (width < 0) width = 0;
	if (height < 0) height = 0;
	int newSize = width * height;
	if (!newSize || newSize != size().square()) {
		delete[] canvas;
		canvas = nullptr;
	}
	if (!newSize || newSize == size().square()) return me;
	canvas = new CHAR_INFO[newSize];
	_size.set(width, height);
	clear(COLOR_BLACK);
	return me;
}
Canvas & Canvas::drawBorder(CRect &rect, char borders[8], COLOR color, COLOR background)
{
	return me;
}
Canvas & Canvas::drawText(CRect &rect, CStrings &strings, COLOR color, COLOR background, ALIGN align)
{
	CSize size = strings.drawingSize();
	int width = Min(rect.width(), size.width());
	int height = Min(rect.height(), size.height());
	repeat2(height, width)
		if (j >= strings[i].length()) break; else
			info(rect.x() + j, rect.y() + i, strings[i][j], color, background);
	return me;
}
Canvas & Canvas::drawRect(CRect &rect, char character, COLOR color, COLOR background)
{
	repeat(rect.height())
		drawHorizLine(rect.position().y(rect.position().y() + i), rect.width(), character, color, background);
	return me;
}
Canvas & Canvas::drawHorizLine(CPoint & position, int length, char character, COLOR color, COLOR background)
{
	int count = Min(width() - position.x(), length);
	repeat(count)
		info(position.x() + i, position.y(), character, color, background);
	return me;
}
Canvas & Canvas::drawVertLine(CPoint & position, int length, char character, COLOR color, COLOR background)
{
	int count = Min(height() - position.y(), length);
	repeat(count)
		info(position.x(), position.y() + i, character, color, background);
	return me;
}
