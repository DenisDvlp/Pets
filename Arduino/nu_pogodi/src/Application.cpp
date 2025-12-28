#include "Application.hpp"
#include "Arduino.hpp"
#include "Picture.hpp"
#include "Images.hpp"
#include "FontCirillic.hpp"

template<typename T>
void log(const T value)
{
  Serial.println(value);
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
  // init port for logs
  Serial.begin(1200);

  // Prepare physical display for work.
  // This takes approximately 0.3 seconds.
  display.init();

  turnOffOledOnBoard();

  // set the output source (display buffer) to drawing system
  graphics.init(display.getBuffer());

  // init game core
  core.init(controller, graphics);

  // clean display
  graphics.clear();
  display.update();
}

void Application::update()
{
  core.update();
}

void Application::draw()
{
  display.update();
}
