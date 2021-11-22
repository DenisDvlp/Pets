#include "Application.h"
#include "Picture.h"
#include "Arduino.h"
#include "Images.h"

void log(const char* str)
{
  Serial.print(str);
  Serial.print("\n");
}

// Turn off LEDs on the board.
void turnOffOledOnBoard()
{
  // We need this delay to give the board some time to calm.
  delay(500);
  digitalWrite(LED_BUILTIN_RX, HIGH);
  digitalWrite(LED_BUILTIN_TX, HIGH);
}

void Application::init()
{
  // Prepare physical display for work.
  // This takes approximately 0.3 seconds.
  display.init();

  turnOffOledOnBoard();

  // set the output source (display buffer) to drawing system
  graphics.init(display.getBuffer());

  // init buttons
  controller.init({ this, &Application::pressDown });

  // init game core
  core.init();

  // init port for logs
  Serial.begin(9600);
  log("OLED Example\n");

  // clean display
  graphics.clear();
  display.update();
}

void Application::update()
{
  core.update();
  controller.update();
  display.update();
}

void Application::pressDown(uint8_t button)
{
  static int x = 0, y = 0;
  graphics.clear();
  switch (button) {
  case Controller::BUTTON_X: graphics.drawPicture(pic_hand, { x -= 10,y }); break;
  case Controller::BUTTON_Y: graphics.drawPicture(pic_hand, { x,y -= 10 }); break;
  case Controller::BUTTON_A: graphics.drawPicture(pic_hand, { x,y += 10 }); break;
  case Controller::BUTTON_B: graphics.drawPicture(pic_hand, { x += 10,y }); break;
  }
}