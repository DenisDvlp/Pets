#pragma once
#include "components.h"
#include "dispatcher.h"

void SpinBones(void(*Refresh)(), Board *board, unsigned first, unsigned second);
void ChipMovement(void(*Refresh)(), Board *board, Chip *chip, int start, int count);
void ChangeBalance(void(*Refresh)(), Board *board, short index, int from, int to);
void Click(void(*Refresh)(), Button *button);
int ShowInfopanel(void(*Refresh)(), Infopanel *infopanel);
int ShowDialog(void(*Refresh)(), Dialog *dialog);