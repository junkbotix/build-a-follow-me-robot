/*
    Build A "Follow-Me" Robot: Part 11 - Software

    FMController.cpp - Firmware for the Junkbotix Build A "Follow-Me" Robot
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include <Junkbotix_Victor884.h>
#include <Junkbotix_Beacons.h>
#include <Junkbotix_Etrex.h>

// Recommended PWM GPIO pins on the ESP32 include:
// 2, 4, 12-19, 21-23, 25-27, 32-33
#define LED_BUILTIN   2   // pin 24 (controls ESP32 on-board LED)

#define LEFT_MOTOR    32  // pin 7  (servo PPM output for Victor-884)
#define RIGHT_MOTOR   33  // pin 8  (servo PPM output for Victor-884)
#define LED_BEACON    25  // pin 9  (TIP102 switch to flash LED beacon)
#define AUD_BEACON    26  // pin 10 (TIP102 switch to sound the audible beacon)

#define ETREX_RX      16  // pin 27 (connected to MAX3232 converter TX pin)
#define ETREX_TX      17  // pin 28 (connected to MAX3232 converter RX pin)

// Instantiate motor controller interface objects
Junkbotix_Victor884 LeftMotor(LEFT_MOTOR);
Junkbotix_Victor884 RightMotor(RIGHT_MOTOR);

// Instantiate LED and audible beacon interface objects
Junkbotix_Beacons LedBeacon(LED_BEACON);
Junkbotix_Beacons AudBeacon(AUD_BEACON);

// Instantiate Etrex interface object
Junkbotix_Etrex EtrexGPS(ETREX_TX, ETREX_RX);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(750);
}
