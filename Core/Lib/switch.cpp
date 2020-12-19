/*
 * switch.cpp
 *
 *  Created on: Dec 18, 2020
 *      Author: juliusz
 */

#include "switch.hpp"
#include "pin_master.hpp"

Switch::Switch(const std::vector<pins::pins_DI> &pins, const std::vector<uint16_t> &position_table)
    : pins(pins), position_table(position_table)
{
}

uint8_t Switch::get_position()
{
    std::vector<StateRes> states = pin_master->get_inputs(pins);
    uint16_t table = 0;
    for (uint8_t pin = 0; pin < states.size(); ++pin)
    {
        table |= states.at(pin).digital.state << pin;
    }
    for (uint8_t position = 0; position < position_table.size(); ++position)
    {
        if (table == position_table.at(position))
        {
            return position + 1; // To start from 1
        }
    }
    return 0;
}
