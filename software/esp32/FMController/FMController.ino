/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * FMController.ino - Firmware for the Junkbotix Build A "Follow-Me" Robot 
 * Copyright (c) 2021 by Junkbotix 
 * Licensed under the GNU Public License (GPL) Version 3 
 * http://www.gnu.org/licenses/gpl-3.0.en.html 
 */ 

// Various defined constants for controller and state machine logic
#include "FMController.h"

// Instantiate robot and client model objects
Junkbotix_Robot FMRobot(WAIT_FOR_GPS);
Junkbotix_Client FMClient();

// Instantiate on-board webserver
Junkbotix_Webserver FMWebserver;

// Instantiate motor controller interface objects
Junkbotix_Victor884 LeftMotor(LEFT_MOTOR);
Junkbotix_Victor884 RightMotor(RIGHT_MOTOR);

// Instantiate visible (LED) beacon interface objects 
Junkbotix_Beacons BlinkBeacon;
Junkbotix_Beacons FlashBeacon;
Junkbotix_Beacons BreathBeacon;

// Instantiate audible beacon interface objects
Junkbotix_Beacons AudibleBeacon;
Junkbotix_Beacons AudibleFlashBeacon;

// Instantiate Etrex interface object
Junkbotix_Etrex EtrexGPS(ETREX_TX, ETREX_RX);

void setup() {

    // Setup a "flashing" LED beacon
    FlashBeacon.setGPIO(LED_BEACON, BEACON_TOGGLE, false);
    FlashBeacon.setRepeat(2);
    FlashBeacon.setDelays(75, 500, 1000);

    // Setup a "breathing" LED beacon
    BreathBeacon.setGPIO(LED_BEACON, BEACON_BREATH, false);
    FlashBeacon.setDelays(10, 10, 0);

    // Setup default long-pulse audible beacon
    AudibleBeacon.setGPIO(AUD_BEACON, BEACON_TOGGLE, false);

    // Setup a short-pulse audible beacon
    AudibleFlashBeacon.setGPIO(AUD_BEACON, BEACON_TOGGLE, false);
    AudibleFlashBeacon.setRepeat(2);
    AudibleFlashBeacon.setDelays(75, 500, 1000);
}

void loop() {
    
    switch (FMRobot.GetState()) {
        case WAIT_FOR_GPS:
            if (true) {
                // Valid GPS: Flash/Beep Beacons 2x
                FlashBeacon.blink();
                AudibleFlashBeacon.blink();
                FMRobot.SetState(INIT_WEB_SERVER);
            } else {
                // Invalid GPS: Fade in/out LED Beacon (LED breathing)
                BreathBeacon.breath();
            }

            break;

        case INIT_WEB_SERVER:
            // Initialize the webserver, then wait for a connection
            FMWebserver.init();
            FMRobot.SetState(WAIT_FOR_STATION_CONNECT);
            break;

        case WAIT_FOR_STATION_CONNECT:
            if (FMWebserver.isConnected()) {
                // Client connected: Flash/Beep Beacons 2x
                FlashBeacon.blink();
                AudibleFlashBeacon.blink();
                FMRobot.SetState(CHECK_CLIENT_ESTOP);
            } else {
                // Client not connected: Fade in/out LED Beacon (LED breathing)
                BreathBeacon.breath();
            }
            break;


        case CHECK_CLIENT_ESTOP:
            if (FMWebserver.isEStopped()) {
                FMRobot.SetState(HCF_HALT);
            } else {
                FMRobot.SetState(GET_CLIENT_GEO_POSITION);
            }
            break;

        case GET_CLIENT_GEO_POSITION:
            FMRobot.SetState(GET_ONBOARD_GEO_POSITION);
            break;

        case GET_ONBOARD_GEO_POSITION:
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

        case HANDLE_POSITION_UPDATE:
            /*
            Save Client Latitude/Longitude/Heading from Message
            Send Response NAVIGATING_MESSAGE
            */
            FMRobot.SetState(HANDLE_NAVIGATION);
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
            FMRobot.SetState(CHECK_CLIENT_ESTOP);
            break;

        case HANDLE_ARRIVAL:
            /*
            Send Response ARRIVAL_MESSAGE
            Flash/Beep Beacons 4x
            */
            FMRobot.Halt();
            FMRobot.SetState(CHECK_CLIENT_ESTOP);
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