/*
 * MAX11616.c
 *
 *  Created on: Nov 30, 2020
 *      Author: juliusz
 */

#include <stdlib.h>
#include "MAX11616.h"

#define MAX_PIN 11
#define MAX_READING 4095

typedef struct private_MAX11616_t private_MAX11616_t;

struct private_MAX11616_t
{
    /**
     * Public interface
     */
    MAX11616_t public;

    /**
     * I2C handle type def
     */
    I2C_HandleTypeDef *hi2c;

    /**
     * I2C address
     */
    uint8_t address;
};

static void configure(MAX11616_t *public)
{
    private_MAX11616_t *this = (private_MAX11616_t *)public;
    uint8_t data[2];
    /**
     * Setup byte
     * Bit 7 (MSB)      register bit        1 for setup
     * Bit 6 % 4        voltage ref         000 for VDD
     * Bit 3            clock               1 for external clock
     * Bit 2            bipolar / unipolar  0 for unipolar
     * Bit 1            reset               0 for reset
     * Bit 0            don't care
     */
    data[0] = 0b10001000;
    /**
     * Configuration byte
     * Bit 7 (MSB)      register bit        0 for configuration
     * Bit 6%5          scan select         00 for scanning from AIN0
     * Bit 4%1          channel select      1011 for all channels
     * Bit 0            differential mode   0 single-ended mode
     */
    data[1] = 0b00010111;
    HAL_I2C_Master_Transmit(this->hi2c, this->address, data, 2, I2C_TIMEOUT);
}
static float *measure_all_pins(MAX11616_t *public)
{
    private_MAX11616_t *this = (private_MAX11616_t *)public;
    uint8_t data[24];
    int status = HAL_I2C_Master_Receive(this->hi2c, this->address, data, 24, I2C_TIMEOUT);
    float *result = malloc((MAX_PIN + 1) * sizeof(float));
    for (int pin = 0; pin <= MAX_PIN; pin++)
    {
        uint16_t upper = data[2 * pin] & 0x0F;
        uint16_t lower = data[2 * pin + 1];
        uint16_t combined_data = upper << 8 | lower;
        result[pin] = (float)combined_data / (float)MAX_READING;
    }
    return result;
}

MAX11616_t *MAX11616_create(I2C_HandleTypeDef *hi2c, uint8_t address)
{
    private_MAX11616_t *this = malloc(sizeof(private_MAX11616_t));
    *this = (private_MAX11616_t){
        .public = {
            .configure = configure,
            .measure_all_pins = measure_all_pins,
        },
        .hi2c = hi2c,
        .address = address,
    };
    return &(this->public);
}
