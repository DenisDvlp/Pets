#include <SPI.h>
#include "Graphics.h"
#include "Picture.h"
#include "Display.h"

constexpr byte BUTTON_X = 4;
constexpr byte BUTTON_Y = 5;
constexpr byte BUTTON_A = 6;
constexpr byte BUTTON_B = 7;

Display display;
Graphics graphics(display.getBuffer());

void turnOffOledOnBoard() {
  // Turn off LEDs on the board.
  delay(500);
  digitalWrite(LED_BUILTIN_RX, HIGH);
  digitalWrite(LED_BUILTIN_TX, HIGH);
}

void initButton(uint8_t button) {
  digitalWrite(button, INPUT_PULLUP);
}

void setup() {
  display.init();

  turnOffOledOnBoard();

  // Set Buttons.
  initButton(BUTTON_X);
  initButton(BUTTON_Y);
  initButton(BUTTON_A);
  initButton(BUTTON_B);


  Serial.begin(9600);
  Serial.print("OLED Example\n");

  graphics.clearBuffer();
  display.update();
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
  graphics.clearBuffer();
  graphics.drawPicture(pic_eggs, {0,0});
  display.update();
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
