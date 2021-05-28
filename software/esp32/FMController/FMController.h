/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * FMController.h - Firmware for the Junkbotix Build A "Follow-Me" Robot
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * Recommended PWM GPIO pins on the ESP32 include:
 * 2, 4, 12-19, 21-23, 25-27, 32-33
 */

#ifndef FMController_h
#define FMController_h

// Framework Class Libraries
#include <Junkbotix_Common.h>
#include <Junkbotix_Robot.h>
#include <Junkbotix_Client.h>
#include <Junkbotix_Webserver.h>
#include <Junkbotix_Beacons.h>
#include <Junkbotix_Victor884.h>
#include <Junkbotix_Etrex.h>

/******************************************************************************/

#define LEFT_MOTOR      32  // pin 7  (servo PPM output for Victor-884)
#define RIGHT_MOTOR     33  // pin 8  (servo PPM output for Victor-884)
#define LED_BEACON      25  // pin 9  (TIP102 switch to flash LED beacon)
#define AUD_BEACON      26  // pin 10 (TIP102 switch to beep the audible beacon)

#define ETREX_RX        16  // pin 27 (connected to MAX3232 converter TX pin)
#define ETREX_TX        17  // pin 28 (connected to MAX3232 converter RX pin)

/******************************************************************************/
/* State Machine States
/******************************************************************************/

#define WAIT_FOR_GPS                0x001
#define INIT_WEB_SERVER             0x002
#define WAIT_FOR_STATION_CONNECT    0x004

#define CHECK_CLIENT_ESTOP          0x008
#define GET_CLIENT_GEO_POSITION     0x010
#define GET_ONBOARD_GEO_POSITION    0x020

#define HANDLE_POSITION_UPDATE      0x040
#define HANDLE_NAVIGATION           0x080
#define HANDLE_MOVEMENT             0x100
#define HANDLE_ARRIVAL              0x200

#define HCF_HALT                    0xFFF

/******************************************************************************/
/* Messages (Default and from Client Browser)
/******************************************************************************/

#define NO_MESSAGE                  0x1   // Default message
#define POSITION_UPDATE             0x2   // From client browser, sent once per second, lat/lon/bearing
#define MANUAL_CONTROL              0x4   // From client browser, sent ad-hoc, per user selection

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

#endif                                        