/*
  Build A "Follow-Me" Robot:
  
  Part 10 - Controller and Basic Sensors

  Modified "Sweep" Test Harness
  
  (based on the original "sweep" servo code)
  
  This test harness is meant for use/testing with the 
  Victor-884 motor controller.
  
  1. It first sets the initial throttle to zero (servo 
     position of 90 degrees), then pauses.
  
  2. It then ramps the throttle up to full in one direction
     (servo position of 180 degrees), briefly pausing before 
     ramping down to zero throttle, and pauses again.
  
  3. It then ramps the throttle up to full in the opposite
     direction (servo position of 0 degrees), briefly pausing
     befor ramping down to zero throttle, where the cycle 
     repeats.
  
  By Junkbotix (2021.04.10)
*/
 
#include <ESP32Servo.h>

// Recommended PWM GPIO pins on the ESP32 include:
// 2, 4, 12-19, 21-23, 25-27, 32-33

#define MOTOR_1 32 // pin 7 for servo PWM output
#define MOTOR_2 33 // pin 8 for servo PWN output

// Using servo library to control two Victor-884 motor
// controllers that use servo PWM signals for control
Servo motor_1;
Servo motor_2;

void strobe() {
  pinMode(LED_BUILTIN, OUTPUT); // more for convenience than correctness
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(75);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(75);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

void initTimers() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);  
}

void initMotor(Servo &xyz, int gpio) {
  xyz.setPeriodHertz(50);
  xyz.attach(gpio, 800, 2200);
  xyz.write(90); // zero throttle
}

void rampMotor(Servo &xyz, int from, int to, int cycle_delay, int servo_delay) {

  // pause before moving
  delay(cycle_delay * 1000);

  strobe();
  
  // move throttle from one position to the new position
  if (from < to) {
    for (int pos = from; pos <= to; pos += 1) {
      xyz.write(pos);
      delay(servo_delay);
    }    
  }
  else {
    for (int pos = from; pos >= to; pos -= 1) {
      xyz.write(pos);
      delay(servo_delay);
    }        
  }
}

void setup() {
  initTimers();
  initMotor(motor_1, MOTOR_1);
  initMotor(motor_2, MOTOR_2);
}
 
void loop() {
  rampMotor(motor_1, 90, 180, 2, 4);
  rampMotor(motor_1, 180, 90, 1, 4);
  rampMotor(motor_1, 90, 0, 2, 4);
  rampMotor(motor_1, 0, 90, 1, 4);

  rampMotor(motor_2, 90, 180, 2, 4);
  rampMotor(motor_2, 180, 90, 1, 4);
  rampMotor(motor_2, 90, 0, 2, 4);
  rampMotor(motor_2, 0, 90, 1, 4);  
}
