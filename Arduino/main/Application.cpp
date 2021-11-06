#include "Application.h"
#include "Picture.h"
#include "Arduino.h"
#include "Graphics.h"
#include "Display.h"
#include "Button.h"
#include "Images.h"

// button physical positions
//        |------|
// (X)(Y) |      | (A)(B)
//        |______|
static constexpr uint8_t BUTTON_X = 4; // digital pin on the board
static constexpr uint8_t BUTTON_Y = 5; // digital pin on the board
static constexpr uint8_t BUTTON_A = 6; // digital pin on the board
static constexpr uint8_t BUTTON_B = 7; // digital pin on the board

static Graphics graphics;
static Display display;
static Button buttons[4];

void log(const char* str) {
  Serial.print(str);
  Serial.print("\n");
}

void pressDown(uint8_t button) {
  //graphics.clear();
  switch (button) {
  case BUTTON_X: graphics.drawPicture(pic_nupogodi, { 0,0 }); break;
  case BUTTON_Y: graphics.drawPicture(pic_nupogodi2, { 0,0 }); break;
  case BUTTON_A: graphics.drawPicture(pic_nupogodi11, { 0,0 }); break;
  case BUTTON_B: graphics.drawPicture(pic_nupogodi12, { 0,0 }); break;
  }
}

void turnOffOledOnBoard() {
  // Turn off LEDs on the board.
  delay(500);
  digitalWrite(LED_BUILTIN_RX, HIGH);
  digitalWrite(LED_BUILTIN_TX, HIGH);
}

void Application::init()
{
  // prepare physical display for work
  display.init();

  turnOffOledOnBoard();

  // set the output source (display buffer) to drawing system
  graphics.init(Buffer(display.getBuffer(), display.getWidth(), display.getHeight()));

  // init buttons
  buttons[0].init(BUTTON_X, pressDown);
  buttons[1].init(BUTTON_Y, pressDown);
  buttons[2].init(BUTTON_A, pressDown);
  buttons[3].init(BUTTON_B, pressDown);

  // init port for logs
  Serial.begin(9600);
  Serial.print("OLED Example\n");

  // clean display
  graphics.clear();
  display.refresh();
}

void Application::update()
{
  // handle button pressing
  for (auto& b : buttons)
  {
    b.update();
  }

  display.refresh();
  // Do not overburden the CPU. It's enough for us to do the things at 100 FPS.
  delay(10);
}
