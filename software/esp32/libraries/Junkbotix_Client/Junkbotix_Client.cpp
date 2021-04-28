/*
    Junkbotix_Client.cpp - Class to model the client
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include "Arduino.h"
#include "Junkbotix_Client.h"

Junkbotix_Client::Junkbotix_Client() {}

void Junkbotix_Client::SetPosition(float latitude, float longitude, float heading) {
    _position = {latitude, longitude, heading};
}

Position Junkbotix_Client::GetPosition() {
    return _position;
}