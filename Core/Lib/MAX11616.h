/*
 * MAX11616.h
 *
 *  Created on: Nov 30, 2020
 *      Author: juliusz
 */

#ifndef LIB_MAX11616_H_
#define LIB_MAX11616_H_

#include "stm32h7xx_hal.h"
#include "general.h"

typedef enum MAX11616_pin_t MAX11616_pin_t;
typedef struct MAX11616_t MAX11616_t;

enum MAX11616_pin_t // order matters
{
    AIN0,
    AIN1,
    AIN2,
    AIN3,
    AIN4,
    AIN5,
    AIN6,
    AIN7,
    AIN8,
    AIN9,
    AIN10,
    AIN11,
};

struct MAX11616_t
{
    /* Configure ADC */
    void (*configure)(MAX11616_t *public);

    /** Get all pins state
     * 
     * @return 12 byte array of all pins states (float), needs to be freed
     */
    float *(*measure_all_pins)(MAX11616_t *public);
};

/**
 * Constructor to create MAX11616 instance
 * 
 * @param hi2c              I2C handle type def
 * @param address           left shifted device address
 */
MAX11616_t *MAX11616_create(I2C_HandleTypeDef *hi2c, uint8_t address);

#endif /* LIB_MAX11616_H_ */
