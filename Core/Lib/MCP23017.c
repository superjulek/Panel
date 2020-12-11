/*
 * MCP23017.c
 *
 *  Created on: Nov 27, 2020
 *      Author: juliusz
 */

#include <stdlib.h>
#include "MCP23017.h"

#define GPPUA_REQ   0x0C
#define GPPUB_REQ   0x0D
#define IODIRA_REG  0x00
#define IODIRB_REG  0x01
#define GPIOA_REG   0x12
#define GPIOB_REG   0x13
#define OLATA_REG   0x14
#define OLATB_REG   0x15

#define MAX_PIN 15

typedef struct private_MCP23017_t private_MCP23017_t;

struct private_MCP23017_t
{
    /**
     * Public interface
     */
    MCP23017_t public;

    /**
     * I2C handle type def
     */
    I2C_HandleTypeDef *hi2c;

    /**
     * I2C address
     */
    uint8_t address;
};

static void set_all_pins_as_output(MCP23017_t *public)
{
    private_MCP23017_t *this = (private_MCP23017_t *)public;
    uint8_t data[2] = {0x00, 0x00};
    HAL_I2C_Mem_Write(this->hi2c, this->address, IODIRA_REG, 1, data, 2, I2C_TIMEOUT);
}

static void set_all_pins_as_input(MCP23017_t *public, bool pull_up)
{
    private_MCP23017_t *this = (private_MCP23017_t *)public;
    uint8_t data[2] = {0xFF, 0xFF};
    HAL_I2C_Mem_Write(this->hi2c, this->address, IODIRA_REG, 1, data, 2, I2C_TIMEOUT);
    if (pull_up)
    {
        HAL_I2C_Mem_Write(this->hi2c, this->address, GPPUA_REQ, 1, data, 2, I2C_TIMEOUT);
    }
}

static void set_pin(MCP23017_t *public, MCP23017_pin_t pin, bool state)
{
    private_MCP23017_t *this = (private_MCP23017_t *)public;
    if (pin > MAX_PIN)
    {
        return;
    }
    if (state > 1)
    {
        state = 1;
    }
    uint8_t data[2];
    HAL_I2C_Mem_Read(this->hi2c, this->address, OLATA_REG, 1, data, 2, I2C_TIMEOUT);
    uint16_t data_combined = data[0] << 8 | data[1];
    data_combined &= 0xFF - 1 << (15 - pin);
    data_combined |= state << (15 - pin);
    data[0] = (data_combined >> 8);
    data[1] = data_combined;
    HAL_I2C_Mem_Write(this->hi2c, this->address, OLATA_REG, 1, data, 2, I2C_TIMEOUT);
}

static bool get_pin(MCP23017_t *public, MCP23017_pin_t pin)
{
    private_MCP23017_t *this = (private_MCP23017_t *)public;
    if (pin > MAX_PIN)
    {
        return 0;
    }
    uint8_t data[2];
    HAL_I2C_Mem_Read(this->hi2c, this->address, GPIOA_REG, 1, data, 2, I2C_TIMEOUT);
    uint16_t data_combined = data[0] << 8 | data[1];
    return data_combined & (1 << (15 - pin));
}

static bool *get_all_pins(MCP23017_t *public)
{
    private_MCP23017_t *this = (private_MCP23017_t *)public;
    uint8_t data[2];
    HAL_I2C_Mem_Read(this->hi2c, this->address, GPIOA_REG, 1, data, 2, I2C_TIMEOUT);
    uint16_t data_combined = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
    bool *pins_states;
    pins_states = malloc((MAX_PIN + 1) * sizeof(bool));
    for(int pin = 0; pin <= MAX_PIN; ++pin)
    {
        pins_states[pin] = ((data_combined & (1 << (15 - pin))) ? TRUE : FALSE);
    }
    return pins_states;
}

MCP23017_t *MCP23017_create(I2C_HandleTypeDef *hi2c, uint8_t address)
{
    private_MCP23017_t *this = malloc(sizeof(private_MCP23017_t));
    *this = (private_MCP23017_t){
        .public = {
            .set_all_pins_as_output = set_all_pins_as_output,
            .set_all_pins_as_input = set_all_pins_as_input,
            .set_pin = set_pin,
            .get_pin = get_pin,
            .get_all_pins = get_all_pins,
        },
        .hi2c = hi2c,
        .address = address,
    };
    return &(this->public);
}
