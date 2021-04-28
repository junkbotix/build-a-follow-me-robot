/*
    Build A "Follow-Me" Robot: Part 11 - Software

    FMController.cpp - Firmware for the Junkbotix Build A "Follow-Me" Robot
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

/* Framework Class Libraries */
#include <Junkbotix_Common.h>
#include <Junkbotix_Robot.h>
#include <Junkbotix_Client.h>
#include <Junkbotix_Victor884.h>
#include <Junkbotix_Beacons.h>
#include <Junkbotix_Etrex.h>

/* Various defined constants for controller and state machine logic */
#include "FMController.h"

// Instantiate robot and client model objects
Junkbotix_Robot FMRobot(WAIT_FOR_GPS);
Junkbotix_Client FMClient();

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
    /*
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(750);
    */
    
    switch (FMRobot.GetState()) {
        case WAIT_FOR_GPS:
            if (true) {
                // Valid GPS: Flash/Beep Beacons 2x
                FMRobot.SetState(WAIT_FOR_CLIENT_REQUEST);                
            } else {
                // Invalid GPS: Fade in/out LED Beacon (LED breathing)
            }

            break;

        case WAIT_FOR_CLIENT_REQUEST:
            if (true) {
                /* 
                Controller Page Requested:
                    Send client browser Controller page
                    Set Current Message (NO_MESSAGE)
                */
                FMRobot.SetState(GET_ONBOARD_GPS_DATA);                
            } else {
                // Controller Page Not Requested: Fade in/out LED Beacon (LED breathing)
            }

            break;

        case GET_ONBOARD_GPS_DATA:
            /*
            Save GPS Data (use running average filter for each):
                Latitude
                Longitude
                Heading 

            Get Current Message

            If Message Received:
                Set State VALIDATE_CREDS
                Save Message as Current Message
            */
            break;

        case VALIDATE_CREDS:
            FMRobot.SetState(HANDLE_INVALID_CREDS);
            /*
            Set State HANDLE_INVALID_CREDS

            Get Credentials (from Current Message)

            If Valid Credentials:
                Send Response VALID_CREDENTIALS
                Set State HANDLE_CURRENT_MESSAGE
            */
            break;

        case HANDLE_INVALID_CREDS:
            /*
            Send Response INVALID_CREDENTIALS
            */
            FMRobot.SetState(WAIT_FOR_GPS);
            break;

        case HANDLE_CURRENT_MESSAGE:
            FMRobot.SetState(HANDLE_INVALID_MESSAGE);
            /*
            If Message == POSITION_UPDATE:
                Set State HANDLE_POSITION_UPDATE

            If Message == MANUAL_CONTROL:
                Set State HANDLE_MANUAL_CONTROL
            */
            break;

        case HANDLE_INVALID_MESSAGE:
            /*
            Send Response INVALID_MESSAGE
            */
            FMRobot.SetState(WAIT_FOR_GPS);
            break;

        case HANDLE_POSITION_UPDATE:
            /*
            Save Client Latitude/Longitude/Heading from Message
            Send Response NAVIGATING_MESSAGE
            */
            FMRobot.SetState(HANDLE_NAVIGATION);
            break;

        case HANDLE_MANUAL_CONTROL:
            FMRobot.SetState(GET_ONBOARD_GPS_DATA);
            /*
            Save Command from Message
            Send Response MANUAL_CONTROL_MESSAGE

            If Command == E_STOP:
                Send Response E_STOP_MESSAGE
                Set State HCF_HALT
            */

            /*
                # Potential future manual control commands:

                # Stop 
                # Blink 
                # Beep

                # Forward/Right
                # Forward
                # Forward/Left

                # Reverse/Right
                # Reverse
                # Reverse/Left
            */           
            break;

        case HANDLE_NAVIGATION:
            FMRobot.SetState(HANDLE_MOVEMENT);
            /*
            Get Robot GPS Data (Latitude, Longitude, Heading)
            
            Calculate Robot Heading and Distance from Robot to Client

            If Distance is under Threshold:
                Set State HANDLE_ARRIVAL
            */
            break;

        case HANDLE_MOVEMENT:
            /*
            Set Robot Motors to Move Toward Client Position
            */
            FMRobot.SetState(GET_ONBOARD_GPS_DATA);
            break;

        case HANDLE_ARRIVAL:
            /*
            Send Response ARRIVAL_MESSAGE
            Flash/Beep Beacons 4x
            */
            FMRobot.Halt();
            FMRobot.SetState(GET_ONBOARD_GPS_DATA);
            break;

        case HCF_HALT:
            // NOTE: break statement purposefully omitted...
        default:
            // Anything that doesn't match a previously defined state, 
            // if it gets here, halt all robot operations
            FMRobot.Halt();
            // At this point power must be cycled (reset)
    }
}