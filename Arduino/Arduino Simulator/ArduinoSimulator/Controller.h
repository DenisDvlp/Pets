#pragma once
#include "Button.h"

class Controller {
public:
  // button physical positions
  //        |------|
  // (X)(Y) |      | (A)(B)
  //        |______|
  static constexpr uint8_t BUTTON_X = 0; // digital pin on the board
  static constexpr uint8_t BUTTON_Y = 1; // digital pin on the board
  static constexpr uint8_t BUTTON_A = 2; // digital pin on the board
  static constexpr uint8_t BUTTON_B = 3; // digital pin on the board

private:
  Button buttons[4];
public:
  void init(Callback pressDownCallback = Callback(), Callback pressUpCallback = Callback());
  void update();
};