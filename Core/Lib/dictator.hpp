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
#include <vector>

class Dictator
{
    public:
    Dictator();
    enum Switches // Must match order in Dictator constructor
    {
        SWITCH_2POS_1,
        SWITCH_2POS_2,
        SWITCH_6POS_1,
    };
    std::vector<Switch> switches;
};

/**
 * One and only one instance of Dictator
 */
extern Dictator *dictator;
