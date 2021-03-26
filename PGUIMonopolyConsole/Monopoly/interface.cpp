#include "interface.h"
#include <time.h>

struct GlobalInterface {
	Display display;
	Board *board;
	Infopanel *infopanel;
	Dialog *dialog;
	Core *core;
} gInterface = { 0 };

void Run();
void CreateScene();
bool ConfirmExitWithDialog(void(*Refresh)(), Board *board, Dialog *dialog);
void PlayerTurn(void(*Refresh)(), Board *board, Infopanel *infopanel, Dialog *dialog, Core *core);
void AssociateInfopanelType(Infopanel *infopanel, Core *core);


Interface CreateInterface() {
	CreateScene();
	srand(time(NULL));
	Interface interface;
	interface.Run = Run;
	return interface;
}

void CreateScene() {
	//создали информационную панель
	gInterface.infopanel = CreateInfopanel();
	gInterface.infopanel->dialog->body->visible = false;
	SetSize(gInterface.infopanel, 50, 20);

	//создали диалог
	gInterface.dialog = CreateDialog();
	gInterface.dialog->body->visible = false;
	SetSize(gInterface.dialog, 45, 10);

	//создали игровое поле
	gInterface.board = CreateBoard();
	SetCardSize(gInterface.board, 16, 8);

	//создали дисплей для вывода на экран
	gInterface.display = CreateDisplay(gInterface.board->body->width, gInterface.board->body->height, 14, COLOR_GRAY);
	Object *parent = gInterface.display.mainParent;
	SetParent(gInterface.board->body, parent);
	SetParent(gInterface.infopanel->dialog->body, parent);
	SetParent(gInterface.dialog->body, parent);

	//создали игровой движок
	gInterface.core = CreateCore();
	for (int i = 0; i < gInterface.core->gamecardCount; i++) {
		Card *card = gInterface.board->cards[i];
		Gamecard *gamecard = gInterface.core->gamecards[i];
		InitCard(card, gamecard->name, gamecard->cost, gamecard->cardType, gamecard->colorCaption, gamecard->colorCard);
	}
	//раздаём деньги игрокам
	SetPlayerBalance(gInterface.board, 0, gInterface.core->startMoney);
	SetPlayerBalance(gInterface.board, 1, gInterface.core->startMoney);
	//выделяем игрока, который будет ходить первым
	SetActivePlayer(gInterface.board, gInterface.core->currentPlayerIndex);
}

void DestroyInterface() {
	DestroyDialog(gInterface.dialog);
	DestroyInfopanel(gInterface.infopanel);
	DestroyBoard(gInterface.board);
	DestroyDisplay();
	DestroyCore(gInterface.core);
}

void Run() {
	Board *board = gInterface.board;
	Infopanel *infopanel = gInterface.infopanel;
	Dialog *dialog = gInterface.dialog;
	Core *core = gInterface.core;
	void(*Refresh)() = gInterface.display.Refresh;

	int answer = 0;
	while (true) {
		answer = KeyHandler(Refresh, board, DispatcherBoard);
		switch (answer) {
		case ANSWER_BOARD_EXIT:
			if (ConfirmExitWithDialog(Refresh, board, dialog)) return;
			break;
		case ANSWER_BOARD_THROW:
			PlayerTurn(Refresh, board, infopanel, dialog, core);
			break;
		}
	}
}

bool ConfirmExitWithDialog(void(*Refresh)(), Board *board, Dialog *dialog) {
	SetContent(dialog->message, "вы действительно хотите\n выйти?");
	SetButtons(dialog, "да", "нет");
	if (ShowDialog(Refresh, dialog) == ANSWER_DIALOG_FIRST) {
		board->body->visible = false;
		Refresh();
		return true;
	}
	return false;
}

void PlayerTurn(void(*Refresh)(), Board *board, Infopanel *infopanel, Dialog *dialog, Core *core) {
	//извлекаем значения выпавших костей
	short first = board->bones[0]->number;
	short second = board->bones[1]->number;
	short sum = first + second;
	//игроки
	short playerIndex = core->currentPlayerIndex; // индекс активного игрока
	short competitorIndex = (playerIndex + 1) % core->playerCount; // индекс соперника
	Player *player = core->players[playerIndex]; // активный игрок
	Player *competitor = core->players[competitorIndex]; // соперник
	//карты
	short nextCardIndex = (player->currentCard + sum) % 24; // индекс выпавшей карты
	Gamecard *currentCard = core->gamecards[nextCardIndex];
	//выпал дубль, если сидел в тюрьме - больше не сидит
	if (first == second) {
		if (player->jailCount) {
			SetContent(dialog->message, "выпал дубль!\n вас амнистировали!");
			SetButtons(dialog, "отлично");
			ShowDialog(Refresh, dialog);
		}
		player->jailCount = 0;
	}
	//проверяем игрока, не сидит ли он в тюрьме
	if (player->jailCount) {
		SetContent(dialog->message, "вы всё ещё сидите в тюрьме.\nпередайте ход следующему игроку.");
		SetButtons(dialog, "жаль");
		ShowDialog(Refresh, dialog);
		player->jailCount--;
		core->currentPlayerIndex = competitorIndex;
		SetActivePlayer(board, competitorIndex);
		return;
	}
	//движение фишки по полю
	ChipMovement(Refresh, board, board->chip[playerIndex], player->currentCard, sum);
	//проверка, прошла ли фишка старт
	if (nextCardIndex < player->currentCard) {
		player->balance += core->lapMoney; //деньги за старт
		char *money = IntToStr(core->lapMoney);
		char *text = ConcatStrings(3, "новый круг!\nполучите ", money, "!");
		SetContent(dialog->message, text);
		DeleteArray(money);
		DeleteArray(text);
		SetButtons(dialog, "спасибо");
		ShowDialog(Refresh, dialog);
		ChangeBalance(Refresh, board, playerIndex, player->balance - core->lapMoney, player->balance);
	}
	player->currentCard = nextCardIndex;
	//инициализация информационной панели
	InitCard(infopanel->card, board->cards[nextCardIndex]);
	AssociateInfopanelType(infopanel, core);
	//показ панели
	int answer = ShowInfopanel(Refresh, infopanel);
	int rent = 0;
	char *number = 0;
	char *text = 0;
	switch (answer) {
	case ANSWER_INFOPANEL_ACCEPT:
		switch (currentCard->type) {
		case GAMECARD_COMMON:
		case GAMECARD_PRIVATE:
			if (!currentCard->owner) {
				if (player->balance - currentCard->cost >= 0) {
					player->balance -= core->gamecards[nextCardIndex]->cost;
					AddCard(player, core->gamecards[nextCardIndex]);
					SetContent(dialog->message, "поздравляем с покупкой нового бизнеса!");
					SetButtons(dialog, "спасибо");
					ShowDialog(Refresh, dialog);
					ChangeBalance(Refresh, board, playerIndex, player->balance + currentCard->cost, player->balance);
				}
			}
			else {
				if (player != currentCard->owner)
					if (player->balance - currentCard->cost / 10 >= 0) {
						rent = currentCard->cost / 10;
						number = IntToStr(rent);
						text = ConcatStrings(2, "ваш баланс уменьшился на ", number);
						SetContent(dialog->message, text);
						DeleteArray(text);
						DeleteArray(number);
						SetButtons(dialog, "ок");
						ShowDialog(Refresh, dialog);
						ChangeBalance(Refresh, board, playerIndex, player->balance, player->balance - rent);
						ChangeBalance(Refresh, board, competitorIndex, competitor->balance, competitor->balance + rent);
						player->balance -= rent;
						competitor->balance += rent;
					}
					else {
						SetContent(dialog->message, "вы проиграли!");
						SetButtons(dialog, "ок");
						ShowDialog(Refresh, dialog);
						board->body->visible = false;
						Refresh();
						return;
					}
			}
			break;
		case GAMECARD_MINUS10:
			rent = (player->balance / 10 > currentCard->cost) ? currentCard->cost : player->balance / 10;
			number = IntToStr(rent);
			text = ConcatStrings(2, "ваш баланс уменьшился на ", number);
			SetContent(dialog->message, text);
			DeleteArray(text);
			DeleteArray(number);
			SetButtons(dialog, "ок");
			ShowDialog(Refresh, dialog);
			ChangeBalance(Refresh, board, playerIndex, player->balance, player->balance - rent);
			player->balance -= rent;
			break;
		case GAMECARD_PLUS10:
			rent = (player->balance / 10 > currentCard->cost) ? currentCard->cost : player->balance / 10;
			number = IntToStr(rent);
			text = ConcatStrings(2, "ваш баланс увеличился на ", number);
			SetContent(dialog->message, text);
			DeleteArray(text);
			DeleteArray(number);
			SetButtons(dialog, "ок");
			ShowDialog(Refresh, dialog);
			ChangeBalance(Refresh, board, playerIndex, player->balance, player->balance + rent);
			player->balance += rent;
			break;
		case GAMECARD_START:
			rent = core->lapMoney;
			number = IntToStr(rent);
			text = ConcatStrings(2, "получите дополнительные ", number);
			SetContent(dialog->message, text);
			DeleteArray(text);
			DeleteArray(number);
			SetButtons(dialog, "отлично");
			ShowDialog(Refresh, dialog);
			ChangeBalance(Refresh, board, playerIndex, player->balance, player->balance + rent);
			player->balance += rent;
		case GAMECARD_JAIL:
			player->jailCount = 2;
			break;
		}
		break;
	case ANSWER_INFOPANEL_DENY:
		break;
	case ANSWER_INFOPANEL_EXIT:
		break;
	}
	//передача хода
	SetContent(dialog->message, "передайте ход следующему игроку");
	SetButtons(dialog, "ок");
	ShowDialog(Refresh, dialog);
	//выделяем игрока, который будет ходить
	core->currentPlayerIndex = competitorIndex;
	SetActivePlayer(board, competitorIndex);
}

void AssociateInfopanelType(Infopanel *infopanel, Core *core) {
	Player *player = core->players[core->currentPlayerIndex]; // активный игрок
	Gamecard *currentCard = core->gamecards[player->currentCard];
	char *number = 0;
	char *text = 0;
	switch (currentCard->type) {
	case GAMECARD_PLUS10:
		SetInfopanelInfo(infopanel, "дивиденды", core->plusminus[0], "получить", 0);
		break;
	case GAMECARD_MINUS10:
		SetInfopanelInfo(infopanel, "налог", core->plusminus[1], "оплатить", 0);
		break;
	case GAMECARD_INFO:
		SetInfopanelInfo(infopanel, "извещение", core->info[0], "ок", 0);
		break;
	case GAMECARD_BONUS:
		SetInfopanelInfo(infopanel, "бонус", core->bonus[0], "ок", 0);
		break;
	case GAMECARD_JAIL:
		SetInfopanelInfo(infopanel, "тюрьма", "проводится следствие.\nпропускаете 2 хода.", "ок", 0);
		break;
	case GAMECARD_REST:
		SetInfopanelInfo(infopanel, "отдых", "вы отправились на викенд!", "ок", 0);
		break;
	case GAMECARD_START:
		number = IntToStr(core->lapMoney);
		text = ConcatStrings(2, "вы прошли круг и попали на старт!\nполучите дополнительные ", number);
		SetInfopanelInfo(infopanel, "старт", text, "получить", 0);
		DeleteArray(text);
		DeleteArray(number);
		break;
	case GAMECARD_COMMON:
	case GAMECARD_PRIVATE:
		if (!currentCard->owner) {
			if (player->balance - currentCard->cost >= 0)
				SetInfopanelInfo(infopanel, "бизнес", "вам поступило предложение\n на приобретение собственности.", "купить", "отказаться");
			else
				SetInfopanelInfo(infopanel, "бизнес", "вам поступило предложение\n на приобретение собственности.\nу вас не хватает средств.", "отказаться", 0);
		}
		else {
			if (player == currentCard->owner)
				SetInfopanelInfo(infopanel, "бизнес", "это ваша собственность.\nможете отдохнуть.", "хорошо", 0);
			else
			if (player->balance - currentCard->cost / 10 >= 0) {
				number = IntToStr(currentCard->cost / 10);
				text = ConcatStrings(2, "вы должны оплатить аренду\nв размере ", number);
				SetInfopanelInfo(infopanel, "бизнес", text, "оплатить", 0);
				DeleteArray(text);
				DeleteArray(number);
			}else
				SetInfopanelInfo(infopanel, "бизнес", "вы должны оплатить аренду.\nу вас не хватает средств.\nвы банкрот!", "банкрот", 0);
		}
		break;
	}
}