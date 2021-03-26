#include "components.h"

Chip* CreateChip() {
	Chip *chip = new Chip;
	chip->x = 0;
	chip->y = 0;
	chip->body = CreateObject();
	SetChipType(chip, CHIP_FIRST);
	SetStroke(chip->body, STROKE_BOLD);
	SetVerticalAlign(chip->body, ALIGN_CENTER);
	SetHorizontalAlign(chip->body, ALIGN_CENTER);
	SetSize(chip->body, 7, 5);
	return chip;
}

void DestroyChip(Chip *&chip) {
	DestroyObject(chip->body);
	delete chip;
	chip = 0;
}

void SetChipType(Chip *chip, ChipType type) {
	chip->type = type;
	char t[2] = { CHAR_FULL_TOP, 0 };
	char f[2] = { CHAR_FULL, 0 };
	char b[2] = { CHAR_FULL_BOT, 0 };
	char *content = 0;
	switch (type) {
	case CHIP_FIRST:
		content = ConcatStrings(8,
			b, f, " \n ", f, " \n", b, f, b);
		break;
	case CHIP_SECOND:
		content = ConcatStrings(10,
			f, t, f, "\n ", b, t, "\n", f, b, b);
		break;
	}
	SetContent(chip->body, content);
	DeleteArray(content);
}

void SetPosition(Chip *chip, short x, short y) {
	chip->x = x;
	chip->y = y;
	chip->body->x = x;
	chip->body->y = y;
}