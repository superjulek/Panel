/*
 * MCP23017.h
 *
 *  Created on: Nov 27, 2020
 *      Author: juliusz
 */

#ifndef LIB_MCP23017_H_
#define LIB_MCP23017_H_

#include "stm32h7xx_hal.h"
#include <array>
#include <cstdint>
#include "general.hpp"

#define MCP_PINS_NUM 16

class MCP23017
{
public:
    MCP23017(I2C_HandleTypeDef *hi2c, uint8_t address);
    MCP23017();
    ~MCP23017();
    void set_all_pins_as_output();
    void set_all_pins_as_input(bool pull_up);
    void set_all_pins(std::array<bool, MCP_PINS_NUM> states);
    std::array<bool, MCP_PINS_NUM> get_all_pins();
    enum MCP23017_pin // order matters
    {
        GPA7 = 0,
        GPA6,
        GPA5,
        GPA4,
        GPA3,
        GPA2,
        GPA1,
        GPA0,
        GPB7,
        GPB6,
        GPB5,
        GPB4,
        GPB3,
        GPB2,
        GPB1,
        GPB0,
    };

private:
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
};

#endif /* LIB_MCP23017_H_ */
