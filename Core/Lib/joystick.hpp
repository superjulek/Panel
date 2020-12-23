/*
 * joystick.hpp
 *
 *  Created on: Dec 22, 2020
 *      Author: juliusz
 */

#pragma once

#include "pins.hpp"
#include <vector>

class Joystick
{
public:
    /**
     * Joystick constructor
     * 
     * @param pins      vector of pins used for subsequent axes
     */
    Joystick(const std::vector<pins::pins_AI> &pins);

    /**
     * Get vector of axes positions
     */
    std::vector<float> get_positions();

    /**
     * UNSUPPORTED
     * Check if middle button was clicked
     */
    //bool was_clicked();

    /**
     * Set current position as zero
     */
    void reset_position();

    /**
     * Set range
     * @param range     vector of range for subsequent axes
     */

    void set_range(std::vector<float> range);

private:
    std::vector<pins::pins_AI> pins;
    std::vector<float> zero_position;
    std::vector<float> range;
};