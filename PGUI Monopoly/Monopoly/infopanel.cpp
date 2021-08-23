#include "components.h"

Infopanel* CreateInfopanel() {
	Infopanel *infopanel = new Infopanel;
	infopanel->x = 0;
	infopanel->y = 0;
	infopanel->width = 0;
	infopanel->height = 0;

	infopanel->dialog = CreateDialog();
	SetVerticalAlign(infopanel->dialog->message, ALIGN_TOP);

	infopanel->caption = CreateObject();
	infopanel->caption->x = 1;
	infopanel->caption->y = 1;
	infopanel->caption->transparent = true;
	infopanel->caption->contentColor = COLOR_CYAN;
	SetHorizontalAlign(infopanel->caption, ALIGN_CENTER);
	SetParent(infopanel->caption, infopanel->dialog->body);

	infopanel->card = CreateCard();
	infopanel->card->details->backgroundColor = COLOR_GRAY;
	SetSize(infopanel->card, 16, 9);
	SetParent(infopanel->card->body, infopanel->dialog->body);

	return infopanel;
}

void DestroyInfopanel(Infopanel *&infopanel) {
	DestroyCard(infopanel->card);
	DestroyDialog(infopanel->dialog);
	delete infopanel;
	infopanel = 0;
}

void SetSize(Infopanel *infopanel, short width, short height) {
	SetSize(infopanel->dialog, width, height);
	infopanel->dialog->message->y = 3;
	SetSize(infopanel->dialog->message, infopanel->dialog->message->width, height - infopanel->card->height - 6);
	SetSize(infopanel->caption, width - 2, 1);
	SetPosition(infopanel->card, (width - infopanel->card->width) / 2, height - infopanel->card->height - 5);
}

void SetPosition(Infopanel *infopanel, short x, short y) {
	infopanel->x = x;
	infopanel->y = y;
	SetPosition(infopanel->dialog, x, y);
}

void SetInfopanelInfo(Infopanel *infopanel, char *caption, char *message, char *button1, char *button2) {
	SetContent(infopanel->caption, caption);
	SetContent(infopanel->dialog->message, message);
	SetButtons(infopanel->dialog, button1, button2);
}