/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * FMController.h - Firmware for the Junkbotix Build A "Follow-Me" Robot
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef FMController_h
#define FMController_h

// Framework Class Libraries
#include <Junkbotix_Common.h>
#include <Junkbotix_Robot.h>
#include <Junkbotix_Client.h>
#include <Junkbotix_Webserver.h>
#include <Junkbotix_Beacons.h>
#include <Junkbotix_Beacon_Style.h>
#include <Junkbotix_Victor884.h>
#include <Junkbotix_Etrex.h>

/******************************************************************************/
/* Define various GPIO pins
/* Recommended PWM GPIO pins on the ESP32 include:
/*      2, 4, 12-19, 21-23, 25-27, 32-33
/******************************************************************************/

#define LEFT_MOTOR      32  // pin 7  (servo PPM output for Victor-884)
#define RIGHT_MOTOR     33  // pin 8  (servo PPM output for Victor-884)
#define VIS_BEACON      25  // pin 9  (TIP102 switch to flash LED beacon)
#define AUD_BEACON      26  // pin 10 (TIP102 switch to beep the audible beacon)

#define ETREX_RX        16  // pin 27 (connected to MAX3232 converter TX pin)
#define ETREX_TX        17  // pin 28 (connected to MAX3232 converter RX pin)

/******************************************************************************/
/* State Machine States
/******************************************************************************/

#define WAIT_FOR_GPS                0x001
#define INIT_WEB_SERVER             0x002
#define WAIT_FOR_STATION_CONNECT    0x004
#define ACK_STATION_CONNECT         0x008

#define RESET_BEACONS               0x010

#define CHECK_CLIENT_ESTOP          0x020
#define GET_CLIENT_GEO_POSITION     0x040
#define GET_ROBOT_GEO_POSITION      0x080
#define UPDATE_ROBOT_NAVIGATION     0x100

#define HANDLE_MOVEMENT             0x200
#define HANDLE_ARRIVAL              0x400

#define HCF_HALT                    0xFFF

#endif                                        