/*
 * switch.hpp
 *
 *  Created on: Dec 18, 2020
 *      Author: juliusz
 */

#pragma once

#include "pins.hpp"
#include <cstdint>
#include <vector>

class Switch
{
public:
    /**
     * Switch constructor
     * 
     * @param pins              vector of pins used by this switch
     * @param position_table    vector of uint16_t maps of high pins corresponding to subsequent positions, LSB is for first pin
     */
    Switch(const std::vector<pins::pins_DI> &pins, const std::vector<uint16_t> &position_table);
    /**
     * Get position of switch
     * 
     * @return                  position of switch, 0 for unknown
     */
    uint8_t get_position();

private:
    std::vector<pins::pins_DI> pins;
    std::vector<uint16_t> position_table;
};
