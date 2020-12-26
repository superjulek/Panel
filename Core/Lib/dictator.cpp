/*
 * dictator.cpp
 *
 *  Created on: Dec 18, 2020
 *      Author: juliusz
 */

#include "dictator.hpp"

Dictator::Dictator()
{
    /* Initialization of all used switches, must match Switches enum */
    switches.push_back(Switch({pins::SWITCH1}, {0b0, 0b1}));
    switches.push_back(Switch({pins::SWITCH2}, {0b0, 0b1}));
    switches.push_back(Switch({pins::SWITCH_6_A_1, pins::SWITCH_6_B_1, pins::SWITCH_6_C_1, pins::SWITCH_6_D_1, pins::SWITCH_6_E_1, pins::SWITCH_6_F_1},
                              {0b111110, 0b111101, 0b111011, 0b110111, 0b101111, 0b011111}));

    /* Initialization of all used joysticks, must match Joysticks enum */
    joysticks.push_back(Joystick({pins::JOY_X_1, pins::JOY_Y_1, pins::JOY_Z_1}));

    /* Initialization of all used switches, must match Potentiometers enum */
    potentiometers.push_back(Potentiometer(pins::POT1));

    /* Initialization of all used switches, must match Leds enum */
    leds.push_back(Led(pins::LIGHT1));
}

Dictator &Dictator::get()
{
    static Dictator instance;
    return instance;
}
