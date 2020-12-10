/*
 * pins.h
 *
 *  Created on: Dec 10, 2020
 *      Author: juliusz
 */

#ifndef LIB_PINS_H_
#define LIB_PINS_H_

#include "general.h"
#include "stm32h7xx_hal.h"

/**
 * Naming convention:
 * pins_AB_t, where:
 * A        D for digital       A for analog
 * B        I for input         O for output
 */

typedef enum pins_DI_t pins_DI_t;
typedef enum pins_DO_t pins_DO_t;
typedef enum pins_AI_t pins_AI_t;
// no pins_IAO_t

typedef struct internal_pin_t internal_pin_t;
typedef struct external_pin_t external_pin_t;

enum pins_DI_t
{
    /* Standard switches */
    SWITCH1,
    SWITCH2,
    SWITCH3,
    SWITCH4,
    SWITCH5,
    SWITCH6,
    SWITCH7,
    SWITCH8,
    SWITCH9,
    SWITCH10,
    SWITCH11,
    SWITCH12,
    SWITCH13,
    SWITCH14,
    SWITCH15,
    SWITCH16,
    SWITCH17,
    SWITCH18,
    SWITCH19,
    SWITCH20,
    SWITCH21,
    SWITCH22,
    SWITCH23,
    SWITCH24,
    SWITCH25,
    SWITCH26,
    SWITCH27,
    SWITCH28,
    SWITCH29,
    SWITCH30,
    SWITCH31,
    SWITCH32,
    SWITCH33,
    SWITCH34,
    SWITCH35,
    SWITCH36,
    SWITCH37,
    SWITCH38,
    SWITCH39,
    SWITCH40,
    /* 12V switches */
    SWITCH_12v1,
    SWITCH_12v2,
    SWITCH_12v3,
    SWITCH_12v4,
    SWITCH_12v5,
    SWITCH_12v6,
    SWITCH_12v7,
    SWITCH_12v8,
    SWITCH_12v9,
    SWITCH_12v10,
    /* Instant switches */
    SWITCH_INSTA1,
    SWITCH_INSTA2,
    SWITCH_INSTA3,
    SWITCH_INSTA4,
    SWITCH_INSTA5,
    /* 3 position switches */
    SWITCH_3_A_1,
    SWITCH_3_B_1,
    SWITCH_3_A_2,
    SWITCH_3_B_2,
    SWITCH_3_A_3,
    SWITCH_3_B_3,
    SWITCH_3_A_4,
    SWITCH_3_B_4,
    SWITCH_3_A_5,
    SWITCH_3_B_5,
    /*4 position switches */
    SWITCH_4_A_1,
    SWITCH_4_B_1,
    SWITCH_4_C_1,
    SWITCH_4_D_1,
    SWITCH_4_A_2,
    SWITCH_4_B_2,
    SWITCH_4_C_2,
    SWITCH_4_D_2,
    SWITCH_4_A_3,
    SWITCH_4_B_3,
    SWITCH_4_C_3,
    SWITCH_4_D_3,
    SWITCH_4_A_4,
    SWITCH_4_B_4,
    SWITCH_4_C_4,
    SWITCH_4_D_4,
    SWITCH_4_A_5,
    SWITCH_4_B_5,
    SWITCH_4_C_5,
    SWITCH_4_D_5,
    /* 6 position switches (external) */
    SWITCH_6_A_1,
    SWITCH_6_B_1,
    SWITCH_6_C_1,
    SWITCH_6_D_1,
    SWITCH_6_E_1,
    SWITCH_6_F_1,
    SWITCH_6_A_2,
    SWITCH_6_B_2,
    SWITCH_6_C_2,
    SWITCH_6_D_2,
    SWITCH_6_E_2,
    SWITCH_6_F_2,
    /* 12 position switch (external) */
    SWITCH_12_A,
    SWITCH_12_B,
    SWITCH_12_C,
    SWITCH_12_D,
    SWITCH_12_E,
    SWITCH_12_F,
    SWITCH_12_G,
    SWITCH_12_H,
    SWITCH_12_I,
    SWITCH_12_J,
    SWITCH_12_K,
    SWITCH_12_L,
    /* unexisting, for total number */
    PINS_DI_NUM
};

enum pins_DO_t
{
    /* LED lights (external) */
    LIGHT1,
    LIGHT2,
    LIGHT3,
    LIGHT4,
    LIGHT5,
    LIGHT6,
    LIGHT7,
    LIGHT8,
    LIGHT9,
    LIGHT10,
    LIGHT11,
    LIGHT12,
    LIGHT13,
    LIGHT14,
    LIGHT15,
    LIGHT16,
    LIGHT17,
    LIGHT18,
    LIGHT19,
    LIGHT20,
    LIGHT21,
    LIGHT22,
    LIGHT23,
    LIGHT24,
    LIGHT25,
    LIGHT26,
    LIGHT27,
    LIGHT28,
    LIGHT29,
    LIGHT30,
    LIGHT31,
    LIGHT32,
    /* unexisting, for total number */
    PINS_DO_NUM
};

enum pins_AI_t
{
    /* Potentiometers */
    POT1,
    POT2,
    POT3,
    POT4,
    POT5,
    POT6,
    POT7,
    POT8,
    /* Potentiometers (external) */
    JOY_X_1,
    JOY_Y_1,
    JOY_Z_1,
    JOY_MID_1,
    JOY_X_2,
    JOY_Y_2,
    JOY_Z_2,
    JOY_MID_2,
    JOY_X_3,
    JOY_Y_3,
    JOY_Z_3,
    JOY_MID_3,
    /* unexisting, for total number */
    PINS_AI_NUM
};

struct internal_pin_t
{
    /**
     * Pin port
     */
    GPIO_TypeDef *port;

    /**
     * Pin number
     */
    uint16_t pin;
};

struct external_pin_t
{
    /**
     *  Expander number
     * */
    uint8_t exp_num;

    /**
     * Pin number
     */
    uint8_t pin;
};

#endif /* LIB_PINS_H_ */
