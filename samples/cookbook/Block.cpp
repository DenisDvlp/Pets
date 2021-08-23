#include "Block.h"

void Block::SetParent(Block *parent)
{
	if (this->parent == parent) return;
	if (this->parent) {
		auto &children = this->parent->children;
		auto toDelete = find(children.begin(), children.end(), this);
		children.erase(toDelete);
	}
	if (parent) 
		parent->children.push_back(this);
	this->parent = parent;
}

void Block::BringToFront()
{
	if (!parent) return;
	Block* tmp = parent;
	SetParent(nullptr);
	SetParent(tmp);
}

void Block::SendToBack()
{
	if (!parent) return;
	Block* tmp = parent;
	SetParent(nullptr);
	parent = tmp;
	parent->children.emplace(parent->children.begin(), this);
}

void Block::Realign()
{
	if (parent) {

		POINT psize = parent->size;
		RECT ppadding = parent->padding;

		if HASFLAG(align, ALIGN_CENTER) {
			position.x = (psize.x - size.x) / 2 + ppadding.left - ppadding.right;
			position.y = (psize.y - size.y) / 2 + ppadding.top - ppadding.bottom;
		}

		if HASFLAG(align, ALIGN_LEFT)
			position.x = ppadding.left;

		if HASFLAG(align, ALIGN_RIGHT) {
			if HASFLAG(align, ALIGN_LEFT)
				size.x = psize.x - ppadding.left - ppadding.right;
			else
				position.x = psize.x - size.x - ppadding.right;
		}

		if HASFLAG(align, ALIGN_TOP)
			position.y = ppadding.top;

		if HASFLAG(align, ALIGN_BOTTOM) {
			if HASFLAG(align, ALIGN_TOP)
				size.y = psize.y - ppadding.top - ppadding.bottom;
			else
				position.y = psize.y - size.y - ppadding.bottom;
		}
		if (size.x < 0) size.x = 0;
		if (size.y < 0) size.y = 0;
	}

	for_each(children.begin(), children.end(), [](Block* block) {block->Realign(); });
}

void Block::Draw()
{
	if (!parent) return;
	for_each(children.begin(), children.end(), [](Block* block) {block->Draw(); });
}

POINT Block::PositionAbsolute()
{
	POINT pos = { 0 };
	if (parent) {
		pos = parent->PositionAbsolute();
		pos.x += parent->padding.left;
		pos.y += parent->padding.top;
	}
	return {0,0};
}

void Block::SetSize(POINT size)
{
	if (size.x < 0) size.x = 0;
	if (size.y < 0) size.y = 0;
	this->size = size;
}

void Block::SetWidth(int width)
{
	SetSize({ width , size.y });
}

void Block::SetHeight(int height)
{
	SetSize({ size.x , height });
}
