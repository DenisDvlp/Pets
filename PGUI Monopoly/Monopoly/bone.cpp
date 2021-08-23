#include "components.h"

Bone* CreateBone() {
	Bone *bone = new Bone;
	bone->number = 0;
	bone->x = 0;
	bone->y = 0;

	bone->body = CreateObject();
	SetSize(bone->body, 12, 7);
	bone->body->backgroundColor = COLOR_WHITE;
	SetStroke(bone->body, STROKE_THIN);
	bone->body->transparent = true;

	bone->dots = CreateObject();
	bone->dots->x = 1;
	bone->dots->y = 1;
	SetSize(bone->dots, 10, 5);
	bone->dots->transparent = true;

	SetParent(bone->dots, bone->body);
	return bone;
}

void DestroyBone(Bone *&bone) {
	DestroyObject(bone->body);
	delete bone;
	bone = 0;
}

void SetPosition(Bone *bone, short x, short y) {
	bone->x = x;
	bone->y = y;
	bone->body->x = x;
	bone->body->y = y;
}

void SetNumber(Bone *bone, unsigned number) {
	bone->number = number;
	char t = CHAR_FULL_TOP;
	char m = CHAR_FULL;
	char b = CHAR_FULL_BOT;
	char oOoMID[] = { ' ', ' ', ' ', ' ', m, m, ' ', ' ', ' ', ' ', '\n', 0 };
	char OoOTOP[] = { ' ', t, t, ' ', ' ', ' ', ' ', t, t, ' ', '\n', 0 };
	char OoOMID[] = { ' ', m, m, ' ', ' ', ' ', ' ', m, m, ' ', '\n', 0 };
	char OoOBOT[] = { ' ', b, b, ' ', ' ', ' ', ' ', b, b, ' ', '\n', 0 };
	char OooTOP[] = { ' ', t, t, ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n', 0 };
	char OooBOT[] = { ' ', b, b, ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n', 0 };
	char ooOTOP[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', t, t, ' ', '\n', 0 };
	char ooOBOT[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', b, b, ' ', '\n', 0 };
	char empty[] = "          \n";
	char *content = 0;
	switch (number) {
	case 1: 
		content = ConcatStrings(5,
			empty,
			empty,
			oOoMID,
			empty,
			empty);
		break;
	case 2:
		content = ConcatStrings(5,
			OooBOT,
			OooTOP,
			empty,
			ooOBOT,
			ooOTOP);
		break;
	case 3:
		content = ConcatStrings(5,
			OooBOT,
			OooTOP,
			oOoMID,
			ooOBOT,
			ooOTOP);
		break;
	case 4:
		content = ConcatStrings(5,
			OoOBOT,
			OoOTOP,
			empty,
			OoOBOT,
			OoOTOP);
		break;
	case 5:
		content = ConcatStrings(5,
			OoOBOT,
			OoOTOP,
			oOoMID,
			OoOBOT,
			OoOTOP);
		break;
	case 6:
		content = ConcatStrings(5,
			OoOBOT,
			OoOTOP,
			OoOMID,
			OoOBOT,
			OoOTOP);
		break;
	}
	SetContent(bone->dots, content);
	DeleteArray(content);
}