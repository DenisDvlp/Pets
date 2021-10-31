/*****************************************************************************
*
* File                : oled.ino
* Hardware Environment: Arduino UNO
* Build Environment   : Arduino
* Version             : V1.0.7
*
*                 (c) Copyright 2005-2017, WaveShare
*                      http://www.waveshare.com
*                      http://www.waveshare.net
*                         All Rights Reserved
*
*****************************************************************************/

#include "Graphics.h"
#include "Picture.h"

constexpr byte BUTTON_X = 4;
constexpr byte BUTTON_Y = 5;
constexpr byte BUTTON_A = 6;
constexpr byte BUTTON_B = 7;

void setup() {
  // Turn off LEDs on the board.
  delay(500);
  digitalWrite(LED_BUILTIN_RX, HIGH);
  digitalWrite(LED_BUILTIN_TX, HIGH);
  // Set Buttons.
  digitalWrite(BUTTON_X, INPUT_PULLUP);
  digitalWrite(BUTTON_Y, INPUT_PULLUP);
  digitalWrite(BUTTON_A, INPUT_PULLUP);
  digitalWrite(BUTTON_B, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.print("OLED Example\n");

  delay(2000);
}

bool x = false;
bool y = false;
bool a = false;
bool b = false;

void checkButton(bool &flag, uint8_t button, void(*pressDown)(), void(*pressUp)()) {
  bool click = !digitalRead(button);
  if (!flag && click) {
    flag = true;
    pressDown();
  }
  else if (flag && !click) {
    flag = false;
    pressUp();
  }
}

void pressDown() {
  Serial.print("pressDown\n");
}

void pressUp() {
  Serial.print("pressUp\n");
}


void loop() {
  checkButton(x, BUTTON_X, pressDown, pressUp);
  checkButton(y, BUTTON_Y, pressDown, pressUp);
  checkButton(a, BUTTON_A, pressDown, pressUp);
  checkButton(b, BUTTON_B, pressDown, pressUp);

  delay(10);
}
