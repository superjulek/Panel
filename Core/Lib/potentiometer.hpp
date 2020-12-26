/*
 * potentiometer.hpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#pragma once

#include "pins.hpp"

class Potentiometer
{
public:
    Potentiometer(pins::pins_AI pin);
    float get_position();
    void set_range(float range);

private:
    pins::pins_AI pin;
    float range;
};