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
    BreathBeacon.setDelays(10, 10, 0);

    // Setup default long-pulse audible beacon
    AudibleBeacon.setGPIO(AUD_BEACON, BEACON_TOGGLE, false);

    // Setup a short-pulse audible beacon
    AudibleFlashBeacon.setGPIO(AUD_BEACON, BEACON_TOGGLE, false);
    AudibleFlashBeacon.setRepeat(2);
    AudibleFlashBeacon.setDelays(75, 500, 1000);
}

void loop() {
    
    switch (FMRobot.getState()) {
        case WAIT_FOR_GPS:
            if (true) {
                // If the GPS is ready, flash and beep beacons 2x
                FlashBeacon.blink();
                AudibleFlashBeacon.blink();
                FMRobot.setState(INIT_WEB_SERVER);
            } else {
                // If the GPS isn't ready, fade in/out the LED beacon (breathing)
                BreathBeacon.breath();
            }

            break;

        case INIT_WEB_SERVER:
            // Initialize the webserver, then wait for a connection
            FMWebserver.init();
            FMRobot.setState(WAIT_FOR_STATION_CONNECT);
            break;

        case WAIT_FOR_STATION_CONNECT:
            if (FMWebserver.isConnected()) {
                // When a client (station) connects to the AP, flash/beep beacons 2x
                FlashBeacon.blink();
                AudibleFlashBeacon.blink();
                FMRobot.setState(CHECK_CLIENT_ESTOP);
            } else {
                // If a client is not connected yet, fade in/out the LED beacon (breathing)
                BreathBeacon.breath();
            }
            break;

        case CHECK_CLIENT_ESTOP:
            // By default, we need to get the client's last reported position
            FMRobot.setState(GET_CLIENT_GEO_POSITION);
            // But if an E-STOP request occurred, set a state to halt everything
            if (FMWebserver.isEStopped()) FMRobot.setState(HCF_HALT);
            break;

        case GET_CLIENT_GEO_POSITION:
            /*
            Read the client's GPS data (moving average filtered on client):
                Latitude
                Longitude
                Heading 
            Save the client's GPS data
            */
            FMRobot.setState(GET_ROBOT_GEO_POSITION);
            break;

        case GET_ROBOT_GEO_POSITION:
            /*
            Read Etrex (robot's) GPS data:
                Latitude
                Longitude
                Heading 
            Filter using moving average
            Save the robot's GPS data
            */
            FMRobot.setState(UPDATE_ROBOT_NAVIGATION);
            break;

        case UPDATE_ROBOT_NAVIGATION:
            FMRobot.setState(HANDLE_MOVEMENT);
            /*
            Get the robot's GPS data (Latitude, Longitude, Heading)
            Get the client's GPS data (Latitude, Longitude, Heading)
            
            Calculate  the robot's heading and distance to the client position

            If the distance is under the set threshold:
                Set the state to HANDLE_ARRIVAL
            */
            break;

        case HANDLE_MOVEMENT:
            // Update the robot's motor settings to move it toward the client's position
            FMRobot.setState(CHECK_CLIENT_ESTOP);
            break;

        case HANDLE_ARRIVAL:
            /*
            Flash and beep the beacons 4x
            
            Notes: 
            1. We probably need a new beacon for this
            2. How to properly "handle arrival" once?
            */
            FMRobot.halt();
            FMRobot.setState(CHECK_CLIENT_ESTOP);
            break;

        case HCF_HALT:
            // Break statement purposefully omitted...

        default:
            /*
            If halting, or anything that doesn't match a previously defined 
            state, halt all robot operations
            */
            FMWebserver.setClientMessage("!!! E-STOP - HALTED !!!");
            FMRobot.halt();
            BlinkBeacon.blink();

            // At this point power must be cycled (reset)
    }
}