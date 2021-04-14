/*
  Build A "Follow-Me" Robot:
  
  Part 10 - Controller and Basic Sensors

  Beacon and Motors Test Harness

  By Junkbotix (2021.04.11)
*/
 
#include <ESP32Servo.h>

// Recommended PWM GPIO pins on the ESP32 include:
// 2, 4, 12-19, 21-23, 25-27, 32-33

#define MOTOR_LEFT 32   // pin 7 (technically a servo output, but this is a test only)
#define MOTOR_RIGHT 33  // pin 8 (technically a servo output, but this is a test only)
#define BEACON 25       // pin 9 (activates TIP102 switch to flash LED beacon)
#define BUZZER 26       // pin 10 (activates TIP102 switch to sound the buzzer)

// Using servo library to control two Victor-884 motor
// controllers that use servo PWM signals for control
Servo motor_left;
Servo motor_right;

void init_timers() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);  
}

void init_motor(Servo &xyz, int gpio) {
  xyz.setPeriodHertz(50);
  xyz.attach(gpio, 800, 2200);
  xyz.write(90); // zero throttle
}

void strobe_led(int times) {
  pinMode(LED_BUILTIN, OUTPUT); // more for convenience than correctness

  for (int i=0; i < times; i++) {
    strobe_gpio(LED_BUILTIN);
  }  
}

void strobe_gpio(int gpio) {
  digitalWrite(gpio, HIGH);
  delay(75);
  digitalWrite(gpio, LOW);
  delay(500);
}

void strobe_beacon() {
  strobe_gpio(BEACON);
}

void strobe_buzzer() {
  strobe_gpio(BUZZER);
}

void ramp_motor(Servo &xyz, int from, int to, int cycle_delay, int servo_delay) {

  // pause before moving
  delay(cycle_delay * 1000);

  strobe_led(2);
  
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

void ramp(Servo &xyz) {
  ramp_motor(xyz, 90, 180, 2, 4);
  ramp_motor(xyz, 180, 90, 1, 4);
  ramp_motor(xyz, 90, 0, 2, 4);
  ramp_motor(xyz, 0, 90, 1, 4);  
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BEACON, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  init_timers();
  
  init_motor(motor_left, MOTOR_LEFT);
  init_motor(motor_right, MOTOR_RIGHT);
}

void loop() {
  strobe_led(4);
  
  strobe_beacon();
  
  ramp(motor_left);
  
  strobe_buzzer();
  
  ramp(motor_right);
}
