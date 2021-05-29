/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Robot.cpp - Class to model the robot
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "Arduino.h"
#include "Junkbotix_Robot.h"

Junkbotix_Robot::Junkbotix_Robot(int state) {
    _state = state;
    halt(); // Turn off motors and beacons
}

void Junkbotix_Robot::setState(int state) {
    _state = state;
}

int Junkbotix_Robot::getState() {
    return _state;
}

void Junkbotix_Robot::halt() {}

void Junkbotix_Robot::setPosition(float latitude, float longitude, float heading) {
    _position = {latitude, longitude, heading};
}

Position Junkbotix_Robot::getPosition() {
    return _position;
}