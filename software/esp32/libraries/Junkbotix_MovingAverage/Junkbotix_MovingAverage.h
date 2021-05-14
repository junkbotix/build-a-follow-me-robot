/**
 *  Junkbotix_MovingAverage.h - Library for calculation of a moving average
 *  Copyright (c) 2021 by Junkbotix
 *  Licensed under the GNU Public License (GPL) Version 3
 *  http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef Junkbotix_MovingAverage_h
#define Junkbotix_MovingAverage_h

#include "Arduino.h"

/** 
 * Define the array size "N" for holding the maximum potential "N"
 * intermediate values for the calculation of the moving average
 */
#define MAX_MOVING_AVG_SIZE  100

class Junkbotix_MovingAverage {
    private:
        int _moving_average_size = 10;
        float _values[MAX_MOVING_AVG_SIZE];

    public:
        Junkbotix_MovingAverage(int size);
        Junkbotix_MovingAverage();

        float calculate(float value);
};

#endif