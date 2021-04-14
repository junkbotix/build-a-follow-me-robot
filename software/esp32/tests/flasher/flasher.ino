/*
  Build A "Follow-Me" Robot:
  
  Part 10 - Controller and Basic Sensors

  Flasher Test Harness

  "Strobes" one or more pins, repeatedly, to test ESP32 
  controller board for the Junkbotix Follow-Me Robot 
  implementation.
  
  Based off the Blink code example for the Arduino.
  
  Turns one or more GPIO pin(s) on for 75 milliseconds, 
  then off for one-half second, repeatedly.

  By Junkbotix (2021.04.08)
*/

#define LEFT_MOTOR 32   // pin 7 (technically a servo output, but this is a test only)
#define RIGHT_MOTOR 33  // pin 8 (technically a servo output, but this is a test only)
#define BEACON 25       // pin 9 (activates TIP102 switch to flash LED beacon)
#define BUZZER 26       // pin 10 (activates TIP102 switch to sound the buzzer)

void strobe(int gpio) {
  digitalWrite(gpio, HIGH);
  delay(75);
  digitalWrite(gpio, LOW);
  delay(500);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BEACON, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
}

void loop() {
  strobe(LED_BUILTIN);
  
  strobe(BEACON);
  strobe(BUZZER);
  strobe(LEFT_MOTOR);
  strobe(RIGHT_MOTOR);  
}
