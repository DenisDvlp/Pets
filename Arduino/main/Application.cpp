#include "Application.h"
#include "Picture.h"
#include "Arduino.h"
#include "Images.h"


void log(const char* str) {
  Serial.print(str);
  Serial.print("\n");
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
  graphics.init(display.getBuffer());

  // init buttons
  controller.init({ this, &Application::pressDown });

  // init port for logs
  Serial.begin(9600);
  log("OLED Example\n");

  // clean display
  graphics.clear();
  display.refresh();
}

void Application::update()
{
  controller.update();

  display.refresh();
  // Do not overburden the CPU. It's enough for us to do the things at 100 FPS.
  delay(10);
}

void Application::pressDown(uint8_t button)
{
  graphics.clear();
  switch (button) {
  case Controller::BUTTON_X: graphics.drawPicture(pic_nupogodi, { 0,0 }); break;
  case Controller::BUTTON_Y: graphics.drawPicture(pic_nupogodi2, { 1,1 }); break;
  case Controller::BUTTON_A: graphics.drawPicture(pic_nupogodi11, { 2,2 }); break;
  case Controller::BUTTON_B: graphics.drawPicture(pic_nupogodi12, { 3,3 }); break;
  }
}