/*
 * led.cpp
 *
 *  Created on: Nov 26, 2020
 *      Author: juliusz
 */

#include "led.hpp"
#include "pin_master.hpp"

Led::Led(pins::pins_DO pin)
    : pin(pin)
{
}

void Led::set_state(bool state)
{
    PinMaster::get().set_output(pin, state);
}
