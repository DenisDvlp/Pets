#include <Arduino.h>

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN_RX, OUTPUT);
  pinMode(LED_BUILTIN_TX, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN_RX, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN_TX, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN_RX, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN_TX, HIGH);   // turn the LED off by making the voltage LOW
  delay(500);                      // wait for a second
}
