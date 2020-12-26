/*
 * led.hpp
 *
 *  Created on: Nov 26, 2020
 *      Author: juliusz
 */

#pragma once

#include "pins.hpp"

class Led
{
public:
    Led(pins::pins_DO pin);
    void set_state(bool state);

private:
    pins::pins_DO pin;
};
