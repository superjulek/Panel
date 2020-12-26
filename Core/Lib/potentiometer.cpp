/**
*
* potentiometer.cpp
*
*  Created on: Dec 24, 2020
*      Author: juliusz
*/

#include "potentiometer.hpp"
#include "pin_master.hpp"

Potentiometer::Potentiometer(pins::pins_AI pin)
    : pin(pin)
{
    range = 1.;
}

float Potentiometer::get_position()
{
    return PinMaster::get().get_input(pin) * range;
}

void Potentiometer::set_range(float range)
{
    this->range = range;
}
