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

void Application::update()
{
  // core.update();
  controller.update();
}

void Application::draw()
{
  display.update();
}

template<typename T, size_t S>
constexpr size_t size(T(&)[S]) { return S; }

void Application::pressDown(uint8_t button)
{
  switch (button) {
  case Controller::BUTTON_X: graphics.drawText("Синяя кнопка", {10,10}, FontCirillic{}); break;
  case Controller::BUTTON_Y: graphics.drawText("Зеленая кнопка", {10,10}, FontCirillic{}); break;
  case Controller::BUTTON_A: graphics.drawText("Красная кнопка", {10,10}, FontCirillic{}); break;
  case Controller::BUTTON_B: /*graphics.drawText("Жёлтая кнопка", { 10,10 }, FontCirillic{});*/ graphics.drawCircle({ 20, 20 }, random(10, 30)); break;
  }
}
