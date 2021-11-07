#pragma once
#include "Button.h"

class Controller {
public:
  // button physical positions
  //        |------|
  // (X)(Y) |      | (A)(B)
  //        |______|
  static constexpr uint8_t BUTTON_X = 4; // digital pin on the board
  static constexpr uint8_t BUTTON_Y = 5; // digital pin on the board
  static constexpr uint8_t BUTTON_A = 6; // digital pin on the board
  static constexpr uint8_t BUTTON_B = 7; // digital pin on the board

private:
  Button buttons[4];
public:
  void init(Callback pressDownCallback = Callback(), Callback pressUpCallback = Callback());
  void update();
};