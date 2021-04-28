/*
    Build A "Follow-Me" Robot: Part 11 - Software

    FMController.h - Firmware for the Junkbotix Build A "Follow-Me" Robot
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html

    Recommended PWM GPIO pins on the ESP32 include:
    2, 4, 12-19, 21-23, 25-27, 32-33
*/

/******************************************************************************/

#define LED_BUILTIN     2   // pin 24 (controls ESP32 on-board LED)

#define LEFT_MOTOR      32  // pin 7  (servo PPM output for Victor-884)
#define RIGHT_MOTOR     33  // pin 8  (servo PPM output for Victor-884)
#define LED_BEACON      25  // pin 9  (TIP102 switch to flash LED beacon)
#define AUD_BEACON      26  // pin 10 (TIP102 switch to beep the audible beacon)

#define ETREX_RX        16  // pin 27 (connected to MAX3232 converter TX pin)
#define ETREX_TX        17  // pin 28 (connected to MAX3232 converter RX pin)

/******************************************************************************/
/* State Machine States
/******************************************************************************/

#define WAIT_FOR_GPS                1
#define WAIT_FOR_CLIENT_REQUEST     2
#define GET_ONBOARD_GPS_DATA        4
#define VALIDATE_CREDS              8

#define HANDLE_INVALID_CREDS        16
#define HANDLE_CURRENT_MESSAGE      32
#define HANDLE_INVALID_MESSAGE      64
#define HANDLE_POSITION_UPDATE      128
#define HANDLE_MANUAL_CONTROL       256
#define HANDLE_NAVIGATION           512
#define HANDLE_MOVEMENT             1024
#define HANDLE_ARRIVAL              2048

#define HCF_HALT                    9999

/******************************************************************************/
/* Messages (Default and from Client Browser)
/******************************************************************************/

#define NO_MESSAGE                  1   // Default message
#define POSITION_UPDATE             2   // From client browser, sent once per second, lat/lon/bearing
#define MANUAL_CONTROL              4   // From client browser, sent ad-hoc, per user selection

/******************************************************************************/
/* Robot Server Responses
/******************************************************************************/

#define CONTROLLER_PAGE             0   // Actual response is HTML/CSS/JS

#define VALID_CREDENTIALS           1   // Sent back when credentials from the
                                        // controller page match on-board values

#define INVALID_CREDENTIALS         2   // Sent back when credentials from the 
                                        // controller page do not match the 
                                        // on-board values

#define INVALID_MESSAGE             4   // Sent back when the message received 
                                        // doesn't match valid message types: 
                                        //      NO_MESSAGE, 
                                        //      POSITION_UPDATE, 
                                        //      MANUAL_CONTROL

#define NAVIGATING_MESSAGE          8   // Sent back when the robot is 
                                        // navigating to the client's position

#define MANUAL_CONTROL_MESSAGE      16  // Sent back when the client is using 
                                        // the manual controls 

#define ARRIVAL_MESSAGE             32  // Sent back when the robot arrives at 
                                        // the client's location

#define E_STOP_MESSAGE              999 // Sent back when the client manual 
                                        // control selected is the emergency 
                                        // stop button