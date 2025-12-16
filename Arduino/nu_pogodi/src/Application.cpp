#include "Application.hpp"
#include "Picture.hpp"
#include "Arduino.h"
#include "Images.hpp"
#include "FontCirillic.hpp"

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
  delay(500);
  digitalWrite(LED_BUILTIN_TX, HIGH);
}

void Application::init()
{
  // Prepare physical display for work.
  // This takes approximately 0.3 seconds.
  display.init();

  //turnOffOledOnBoard();

  // set the output source (display buffer) to drawing system
  graphics.init(display.getBuffer());

  // init buttons
  controller.init({ this, &Application::pressDown });

  // init game core
  //core.init(controller, graphics);

  // init port for logs
  Serial.begin(1200);

  // clean display
  graphics.clear();
  display.update();
}
int x = 0;
void Application::update()
{
  delay(200);
  digitalWrite(LED_BUILTIN_RX, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN_RX, LOW);
  graphics.drawPixel({10 + x,20 + x} );
  ++x;
  if(x == 15){
    graphics.drawText("Жёлтая кнопка", {10,10}, FontCirillic{});
  }
  // // core.update();
  controller.update();
  display.update();
}

template<typename T, size_t S>
constexpr size_t size(T(&)[S]) { return S; }

void Application::pressDown(uint8_t button)
{
  FontCirillic font;
  font.isBold = false;
  Position pos = { (Display::WIDTH - graphics.calculateTextWidth("Ну Погоди", font)) / 2, 20 };
  switch (button) {
  case Controller::BUTTON_X: log("BUTTON_X"); break;
  case Controller::BUTTON_Y: log("BUTTON_Y"); break;
  case Controller::BUTTON_A: log("BUTTON_A"); break;
  case Controller::BUTTON_B: log("BUTTON_B"); break;
  }
}
