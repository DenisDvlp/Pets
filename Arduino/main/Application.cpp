#include "Application.h"
#include "Picture.h"
#include "Arduino.h"
#include "Images.h"
#include "FontCirillic.h"

void log(const char* str)
{
  Serial.println(str);
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

template<typename T, size_t S>
constexpr size_t size(T(&)[S]) { return S; }

void Application::pressDown(uint8_t button)
{
  static int x = 0, y = 0;
  graphics.clear();
  FontCirillic font;
  font.isBold = false;
  Position pos = { (Display::WIDTH - graphics.calculateTextWidth("Ну Погоди", font)) / 2, 20 };
  switch (button) {
  case Controller::BUTTON_X: graphics.drawText("Ну Погоди", {0,0}, font); break;
  //case Controller::BUTTON_Y: graphics.drawPicture(pic_hand, { x,y -= 10 }); break;
  //case Controller::BUTTON_A: graphics.drawPicture(pic_hand, { x,y += 10 }); break;
  //case Controller::BUTTON_B: graphics.drawPicture(pic_hand, { x += 10,y }); break;
  }
}