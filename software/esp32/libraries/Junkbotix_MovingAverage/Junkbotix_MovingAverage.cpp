/**
 *  Junkbotix_MovingAverage.cpp - Library for calculation of a moving average
 *  Copyright (c) 2021 by Junkbotix
 *  Licensed under the GNU Public License (GPL) Version 3
 *  http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "Arduino.h"
#include "Junkbotix_MovingAverage.h"

/** 
 * Add a new value to the running average and 
 * re-calculate, returning the new average 
 */
float Junkbotix_MovingAverage::calculate(float value) {
    static int vcount = 0;
    static int rcount = 0;

    float total = 0;

    /** 
     * Calculate and return the running
     * average while growing the array...
     */
    if (vcount < _moving_average_size) {
        _values[vcount] = value;

        for (int i = 0; i <= vcount; i++) {
            total += _values[i];
        }

        vcount++;

        return float (total / vcount);
    }

    /** 
     * Calculate and return the running 
     * average for the entire array 
     */
    _values[rcount] = value;

    rcount++;

    if (rcount >= _moving_average_size) rcount = 0;

    for (int i = 0; i < _moving_average_size; i++) {
        total += _values[i];
    }

    return float (total / _moving_average_size);
}

/** 
 * This constructor allows the ability to define the array 
 * size N for holding the N intermediate values for the 
 * calculation of the moving average: More values help to
 * reduce fluctuations, at the cost of speed to make the
 * calculation (adjusting the number may have benefits)
 */
Junkbotix_MovingAverage::Junkbotix_MovingAverage(int size) {
    _moving_average_size = size;
    Junkbotix_MovingAverage();
}

/** Constructor for the default size */
Junkbotix_MovingAverage::Junkbotix_MovingAverage() {
    // Zero the array
    for (int i = 0; i < MAX_MOVING_AVG_SIZE; i++) {
        _values[i] = 0;
    }
}