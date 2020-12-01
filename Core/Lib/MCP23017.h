/*
 * MCP23017.h
 *
 *  Created on: Nov 27, 2020
 *      Author: juliusz
 */

#ifndef LIB_MCP23017_H_
#define LIB_MCP23017_H_

#include "stm32h7xx_hal.h"
#include "general.h"

typedef enum MCP23017_pin_t MCP23017_pin_t;
typedef struct MCP23017_t MCP23017_t;

enum MCP23017_pin_t // order matters
{
    GPA7,
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

struct MCP23017_t
{

    /**
     * Set all pins as output
    */
    void (*set_all_pins_as_output)(MCP23017_t *public);

    /**
     * Set all pins as input
     * @param pull_up       whether to pull up all inputs
    */
    void (*set_all_pins_as_input)(MCP23017_t *public, bool pull_up);

    /**
    * Set single pin state
    * @param pin            pin to be set
    * @param state          state to be set
    */
    void (*set_pin)(MCP23017_t *public, MCP23017_pin_t pin, bool state);

    /**
    * Get single pin state
    * @param pin            pin to be set
    * @return               state of pin
    */
    bool (*get_pin)(MCP23017_t *public, MCP23017_pin_t pin);

    /**
    * Get all pins state
    * @return               16 byte array of all pins states (bool), needs to be freed
    */
    bool *(*get_all_pins)(MCP23017_t *public);
};

/**
 * Constructor to create MCP23017 instance
 * 
 * @param hi2c              I2C handle type def
 * @param address           left shifted device address
 */
MCP23017_t *MCP23017_create(I2C_HandleTypeDef *hi2c, uint8_t address);

#endif /* LIB_MCP23017_H_ */
