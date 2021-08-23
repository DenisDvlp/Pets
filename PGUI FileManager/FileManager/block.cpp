#include "pseudoGUI.h"

Block CreateBlock(unsigned short width, unsigned short height, unsigned char contentColor, unsigned char backgroundColor) {
	Block block;
	block.x = 0;
	block.y = 0;
	block.width = 0;
	block.height = 0;
	block.contentColor = contentColor;
	block.backgroundColor = backgroundColor;
	block.visible = true;
	block.transparent = false;
	block.parent = 0;//NULL
	block.children = 0;
	block.childrenCount = 0;//NULL
	Resize(block, width, height);
	Clear(block);
	return block;
}

void DestroyBlock(Block &block) {
	SetParent(block, 0);
	for (int i = 0; i < block.childrenCount; i++)
		DestroyBlock(*(block.children[i]));
	for (int i = 0; i < block.height; i++)
		delete[] block.content[i];
	if (block.height)
		delete[] block.content;
	block.width = block.height = 0;
}

int GetAbsoluteX(Block &block) {
	char x = block.x;
	if (block.parent)
		x += GetAbsoluteX(*(block.parent));
	return x;
}

int GetAbsoluteY(Block &block) {
	char y = block.y;
	if (block.parent)
		y += GetAbsoluteY(*(block.parent));
	return y;
}

void Resize(Block &block, unsigned short width, unsigned short height) {
	for (int i = 0; i < block.height; i++)
		delete[] block.content[i];
	if(block.height)
		delete[] block.content;
	block.content = 0;//NULL
	block.width = width;
	block.height = height;
	if (width == 0 || height == 0) return;
	block.content = new char*[height];
	for (int i = 0; i < height; i++)
		block.content[i] = new char[width];
	Clear(block);
}

void SetParent(Block &block, Block *parent) {
	if (parent)
		AddChild(*parent, block);
	else 
		if(block.parent)
			DeleteChild(*(block.parent), block);
	block.parent = parent;
}

void AddChild(Block &block, Block &child) {
	Block **newChildren = new Block*[block.childrenCount + 1];
	for (int i = 0; i < block.childrenCount; i++)
		newChildren[i] = block.children[i];
	newChildren[block.childrenCount++] = &child;
	if (block.childrenCount)
		delete[] block.children;
	block.children = newChildren;
}

void DeleteChild(Block &block, Block &child) {
	if (!block.childrenCount) return;
	for (int i = 0, j = 0; i < block.childrenCount; i++)
		if (block.children[i] != &child)
			block.children[j++] = block.children[i];
	block.childrenCount--;
}

void Clear(Block &block) {
	for (int i = 0; i < block.height; i++)
		for (int j = 0; j < block.width; j++)
			block.content[i][j] = ' ';
}