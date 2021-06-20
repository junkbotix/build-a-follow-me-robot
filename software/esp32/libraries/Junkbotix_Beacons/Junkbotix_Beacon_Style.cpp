/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Beacon_Style.cpp - Interface library for beacon styling
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include <Junkbotix_Beacon_Style.h>

/******************************************************************************/
/* Public Methods
/******************************************************************************/

/**
 * Set the name for the beacon style
 * 
 * @param name Name of the style
 */
void Junkbotix_Beacon_Style::setName(String name) { 
    _name = name;
}

/**
 * Set the number of repeated beacon actions per cycle for the beacon style
 * 
 * @param repeat Number of times to repeat actions per cycle
 */
void Junkbotix_Beacon_Style::setRepeat(unsigned int repeat) { 
    _repeat = repeat;
}

/**
 * Set the PWM step value for the beacon style (255 = Toggle between on and off states)
 * 
 * @param step Value to increase/decrease PWM value by for each tick
 */
void Junkbotix_Beacon_Style::setStep(unsigned int step) { 
    _step = step;
}

/**
 * Set the beacon style on-delay value
 * 
 * @param ondelay Number of milliseconds for beacon to wait between ticks when fading in
 */
void Junkbotix_Beacon_Style::setOnDelay(unsigned int ondelay) {
    _ondelay = ondelay;
}

/**
 * Set the beacon style off-delay value
 * 
 * @param offdelay Number of milliseconds for beacon to wait between ticks when fading out
 */
void Junkbotix_Beacon_Style::setOffDelay(unsigned int offdelay) {
    _offdelay = offdelay;
}

/**
 * Set the beacon style pause-delay value
 * 
 * @param pausedelay Number of milliseconds for beacon to pause after a full on/off cycle
 */
void Junkbotix_Beacon_Style::setPauseDelay(unsigned int pausedelay) {
    _pausedelay = pausedelay;
}

/**
 * Set the beacon style oneshot flag value
 * 
 * @param oneshot Set to true if the beacon is only meant to cycle one time
 */
void Junkbotix_Beacon_Style::setOneshot(bool oneshot = false) { 
    _oneshot = oneshot;
}

// Return the assigned name for the beacon style
String Junkbotix_Beacon_Style::getName() {
    return _name;
}

// Return the number of repeated beacon actions per cycle for the beacon style
unsigned int Junkbotix_Beacon_Style::getRepeat() {
    return _repeat;
}

// Return the PWM step value for the beacon style (255 = Toggle between on and off states)
unsigned int Junkbotix_Beacon_Style::getStep() {
    return _step;
}

// Return the beacon style on-delay value
unsigned int Junkbotix_Beacon_Style::getOnDelay() {
    return _ondelay;
}

// Return the beacon style off-delay value
unsigned int Junkbotix_Beacon_Style::getOffDelay() {
    return _offdelay;
}

// Return the beacon style pause-delay value
unsigned int Junkbotix_Beacon_Style::getPauseDelay() {
    return _pausedelay;
}

// Return the beacon style oneshot flag value
bool Junkbotix_Beacon_Style::getOneshot() {
    return _oneshot;
}

Junkbotix_Beacon_Style::Junkbotix_Beacon_Style() {
    _repeat = 1;
    _step = 255;
    _ondelay = 500;
    _offdelay = 500;
    _pausedelay = 0;
    _oneshot = false;
}