#pragma once
#include "Button.hpp"

class Controller {
public:

#ifdef ARDUINO
  // button physical positions
  //        |------|
  // (X)(Y) |      | (A)(B)
  //        |______|
  static constexpr uint8_t BUTTON_X = 4; // digital pin on the board
  static constexpr uint8_t BUTTON_Y = 5; // digital pin on the board
  static constexpr uint8_t BUTTON_B = 6; // digital pin on the board
  static constexpr uint8_t BUTTON_A = 7; // digital pin on the board
#else
  // Simulated buttons key codes
  static constexpr uint8_t BUTTON_X = 0x51; // 'Q' key
  static constexpr uint8_t BUTTON_Y = 0x57; // 'W' key
  static constexpr uint8_t BUTTON_A = 0x45; // 'E' key
  static constexpr uint8_t BUTTON_B = 0x52; // 'R' key
#endif // ARDUINO

private:
  Button buttons[4];
public:
  void init(Callback pressDownCallback = Callback(), Callback pressUpCallback = Callback());
  void update();
};
