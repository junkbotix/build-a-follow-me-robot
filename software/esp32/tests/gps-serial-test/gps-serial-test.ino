/*
  Build A "Follow-Me" Robot:
  
  Part 10 - Controller and Basic Sensors

  Garmin eTrex GPS Test Harness

  Sets up Serial Port 2 on ESP32 to receive data from 
  the Garmin eTrex (via a MAX232 level-converter), then 
  dumps it out the default serial port.

  By Junkbotix (2021.04.10)
*/
 
#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

  // The format for setting a serial port is as follows: 
  //   Serial2.begin(baud-rate, protocol, RX pin, TX pin);

  Serial2.begin(4800, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }
}
