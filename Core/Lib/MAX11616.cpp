/*
 * MAX11616.c
 *
 *  Created on: Nov 30, 2020
 *      Author: juliusz
 */

#include <stdlib.h>
#include "MAX11616.hpp"

#define MAX_READING 4095

MAX11616::MAX11616(I2C_HandleTypeDef *hi2c, uint8_t address)
    : hi2c(hi2c), address(address)
{
}
void MAX11616::configure()
{
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
std::array<float, MAX_PINS_NUM> MAX11616::measure_all_pins()
{
    std::array<float, MAX_PINS_NUM> return_arr;
    uint8_t data[24];
    int status = HAL_I2C_Master_Receive(this->hi2c, this->address, data, 24, I2C_TIMEOUT);
    for (int pin = MAX11616_pin::AIN0; pin <= MAX11616_pin::AIN11; pin++)
    {
        uint16_t upper = data[2 * pin] & 0x0F;
        uint16_t lower = data[2 * pin + 1];
        uint16_t combined_data = upper << 8 | lower;
        return_arr[pin] = (float)combined_data / (float) MAX_READING;
    }
    return return_arr;
}
