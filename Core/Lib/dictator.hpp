/*
 * dictator.hpp
 *
 *  Created on: Dec 18, 2020
 *      Author: juliusz
 */

/**
 * Master of all input and output devices with unlimited power
 * 
 * "One ring to rule them all, One ring to find them, One ring to bring them all and in the darkness bind them."
 */

#pragma once

#include "switch.hpp"
#include "joystick.hpp"
#include "potentiometer.hpp"
#include "led.hpp"
#include <vector>

/* Singleton for controlling IO devices */
class Dictator
{
public:
    Dictator(const Dictator &) = delete;
    /* Get instance of Dictator */
    static Dictator &get();
    enum Switches // Must match order in Dictator constructor
    {
        SWITCH_2POS_1,
        SWITCH_2POS_2,
        SWITCH_6POS_1,
    };
    enum Joysticks // Must match order in Dictator constructor
    {
        JOYSTICK_1,
    };
    enum Potentiometers // Must match order in Dictator constructor
    {
        POTENTIOMETER_1,
    };
    enum Leds // Must match order in Dictator constructor
    {
        LED_1,
    };
    std::vector<Switch> switches;
    std::vector<Joystick> joysticks;
    std::vector<Potentiometer> potentiometers;
    std::vector<Led> leds;

private:
    Dictator();
};
