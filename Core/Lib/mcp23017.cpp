/*
 * MCP23017.c
 *
 *  Created on: Nov 27, 2020
 *      Author: juliusz
 */

#include <stdlib.h>
#include "mcp23017.hpp"

#define GPPUA_REQ 0x0C
#define GPPUB_REQ 0x0D
#define IODIRA_REG 0x00
#define IODIRB_REG 0x01
#define GPIOA_REG 0x12
#define GPIOB_REG 0x13
#define OLATA_REG 0x14
#define OLATB_REG 0x15

MCP23017::MCP23017(I2C_HandleTypeDef *hi2c, uint8_t address)
    : hi2c(hi2c), address(address)
{
}

void MCP23017::set_all_pins_as_output()
{
    uint8_t data[2] = {0x00, 0x00};
    HAL_I2C_Mem_Write(hi2c, address, IODIRA_REG, 1, data, 2, I2C_TIMEOUT);
}

void MCP23017::set_all_pins_as_input(bool pull_up)
{
    uint8_t data[2] = {0xFF, 0xFF};
    HAL_I2C_Mem_Write(hi2c, address, IODIRA_REG, 1, data, 2, I2C_TIMEOUT);
    if (pull_up)
    {
        HAL_I2C_Mem_Write(hi2c, address, GPPUA_REQ, 1, data, 2, I2C_TIMEOUT);
    }
}

void MCP23017::set_all_pins(std::array<bool, MCP_PINS_NUM> states)
{
    uint16_t data_combined = 0;
    uint8_t data[2];
    for (int pin = GPA7; pin <= GPB0; ++pin)
    {
        if (states[pin])
        {
            data_combined |= (1 << (15 - pin));
        }
    }
    data[0] = (data_combined >> 8);
    data[1] = data_combined;
    HAL_I2C_Mem_Write(hi2c, address, OLATA_REG, 1, data, 2, I2C_TIMEOUT);
}

std::array<bool, MCP_PINS_NUM> MCP23017::get_all_pins()
{
    uint8_t data[2];
    HAL_I2C_Mem_Read(hi2c, address, GPIOA_REG, 1, data, 2, I2C_TIMEOUT);
    uint16_t data_combined = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
    std::array<bool, MCP_PINS_NUM> pins_states;
    for (int pin = GPA7; pin <= GPB0; ++pin)
    {
        pins_states[pin] = ((data_combined & (1 << (15 - pin))) ? true : false);
    }
    return pins_states;
}
