/*
 * max11616.hpp
 *
 *  Created on: Nov 30, 2020
 *      Author: juliusz
 */

#ifndef LIB_MAX11616_H_
#define LIB_MAX11616_H_

#include "stm32h7xx_hal.h"
#include <array>
#include <cstdint>
#include "general.hpp"

#define MAX_PINS_NUM 12

class MAX11616
{
public:
    MAX11616(I2C_HandleTypeDef *hi2c, uint8_t address);
    ~MAX11616();
    void configure();
    std::array<float, MAX_PINS_NUM> measure_all_pins();
    enum MAX11616_pin : uint8_t
    {
        AIN0 = 0,
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

private:
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
};

#endif /* LIB_MAX11616_H_ */
