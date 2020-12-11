/*
 * pin_master.c
 *
 *  Created on: Dec 10, 2020
 *      Author: juliusz
 */

#include "pin_master.h"
#include "MCP23017.h"
#include "MAX11616.h"

#include "stdlib.h"
#include "stm32h7xx_hal.h"
#include "adc.h"
#include "i2c.h"

typedef struct private_pin_master_t private_pin_master_t;

struct private_pin_master_t
{
    /**
     * Public interface.
     */
    pin_master_t public;

    /**
     * Last states of DI pins.
     */
    bool pins_DI_states[PINS_DI_NUM];

    /**
     * Last states of AI pins.
     */
    float pins_AI_states[PINS_AI_NUM];

    /**
     * Last required stated of DO pins.
     */
    bool pins_DO_required_states[PINS_DO_NUM];

    /**
     * Internal digital input pins.
     */
    internal_pin_t internal_DI_pins[SWITCH_4_D_5 - SWITCH1 + 1];

    /**
     * External digital input pins.
     */
    external_pin_t external_DI_pins[SWITCH_12_L - SWITCH_6_A_1 + 1];

    /**
     * External digital output pins.
     */
    external_pin_t external_DO_pins[LIGHT32 - LIGHT1 + 1];

    /**
     * Buffer for DMA ADC readings.
     */
    uint16_t internal_AI_DMA_buffer[POT8 - POT1 + 1];

    /**
     * MCP23017 instances
     */
    MCP23017_t *DI_DO_expanders[4];

    /**
     * MAX11616 instance
     */
    MAX11616_t *AI_expander;
};

static void reload_inputs(pin_master_t *public)
{
    private_pin_master_t *this = (private_pin_master_t *)public;

    for (uint8_t pin = SWITCH1; pin <= SWITCH_4_D_5; ++pin)
    {
        this->pins_DI_states[pin] = HAL_GPIO_ReadPin(this->internal_DI_pins[pin].port, this->internal_DI_pins[pin].pin);
    }
}

static void reload_outputs(pin_master_t *public)
{
    private_pin_master_t *this = (private_pin_master_t *)public;
}

pin_master_t *pin_master_create()
{
    private_pin_master_t *this = (private_pin_master_t *)malloc(sizeof(private_pin_master_t));
    *this = (private_pin_master_t){
        .public = {
            .reload_inputs = reload_inputs,
            .reload_outputs = reload_outputs,
        },
    };
    /* Reset DI pins */
    for (uint8_t pin; pin <= SWITCH_12_L; ++pin)
    {
        this->pins_DI_states[pin] = FALSE;
    }
    /* Reset DO pins */
    for (uint8_t pin; pin <= LIGHT32; ++pin)
    {
        this->pins_DO_required_states[pin] = FALSE;
    }
    /* Reset AI pins */
    for (uint8_t pin; pin <= JOY_MID_3; ++pin)
    {
        this->pins_AI_states[pin] = FALSE;
    }

    /* All pins are asigned here since there will always be only one instance of pin_master_t */

    /* Assign values for internal input pins */
    this->internal_DI_pins[SWITCH1] = (internal_pin_t){.port = GPIOA, .pin = 15};
    this->internal_DI_pins[SWITCH2] = (internal_pin_t){.port = GPIOC, .pin = 10};
    this->internal_DI_pins[SWITCH3] = (internal_pin_t){.port = GPIOC, .pin = 11};
    this->internal_DI_pins[SWITCH4] = (internal_pin_t){.port = GPIOC, .pin = 12};
    this->internal_DI_pins[SWITCH5] = (internal_pin_t){.port = GPIOD, .pin = 0};
    this->internal_DI_pins[SWITCH6] = (internal_pin_t){.port = GPIOD, .pin = 1};
    this->internal_DI_pins[SWITCH7] = (internal_pin_t){.port = GPIOD, .pin = 2};
    this->internal_DI_pins[SWITCH8] = (internal_pin_t){.port = GPIOD, .pin = 3};
    this->internal_DI_pins[SWITCH9] = (internal_pin_t){.port = GPIOD, .pin = 4};
    this->internal_DI_pins[SWITCH10] = (internal_pin_t){.port = GPIOD, .pin = 5};
    this->internal_DI_pins[SWITCH11] = (internal_pin_t){.port = GPIOD, .pin = 6};
    this->internal_DI_pins[SWITCH12] = (internal_pin_t){.port = GPIOD, .pin = 7};
    this->internal_DI_pins[SWITCH13] = (internal_pin_t){.port = GPIOG, .pin = 9};
    this->internal_DI_pins[SWITCH14] = (internal_pin_t){.port = GPIOG, .pin = 10};
    this->internal_DI_pins[SWITCH15] = (internal_pin_t){.port = GPIOG, .pin = 11};
    this->internal_DI_pins[SWITCH16] = (internal_pin_t){.port = GPIOG, .pin = 12};
    this->internal_DI_pins[SWITCH17] = (internal_pin_t){.port = GPIOG, .pin = 13};
    this->internal_DI_pins[SWITCH18] = (internal_pin_t){.port = GPIOG, .pin = 14};
    this->internal_DI_pins[SWITCH19] = (internal_pin_t){.port = GPIOG, .pin = 15};
    this->internal_DI_pins[SWITCH20] = (internal_pin_t){.port = GPIOB, .pin = 3};
    this->internal_DI_pins[SWITCH21] = (internal_pin_t){.port = GPIOB, .pin = 4};
    this->internal_DI_pins[SWITCH22] = (internal_pin_t){.port = GPIOB, .pin = 5};
    this->internal_DI_pins[SWITCH23] = (internal_pin_t){.port = GPIOB, .pin = 6};
    this->internal_DI_pins[SWITCH24] = (internal_pin_t){.port = GPIOB, .pin = 7};
    this->internal_DI_pins[SWITCH25] = (internal_pin_t){.port = GPIOE, .pin = 0};
    this->internal_DI_pins[SWITCH26] = (internal_pin_t){.port = GPIOE, .pin = 1};
    this->internal_DI_pins[SWITCH27] = (internal_pin_t){.port = GPIOE, .pin = 2};
    this->internal_DI_pins[SWITCH28] = (internal_pin_t){.port = GPIOE, .pin = 3};
    this->internal_DI_pins[SWITCH29] = (internal_pin_t){.port = GPIOE, .pin = 4};
    this->internal_DI_pins[SWITCH30] = (internal_pin_t){.port = GPIOE, .pin = 5};
    this->internal_DI_pins[SWITCH31] = (internal_pin_t){.port = GPIOE, .pin = 6};
    this->internal_DI_pins[SWITCH32] = (internal_pin_t){.port = GPIOC, .pin = 13};
    this->internal_DI_pins[SWITCH33] = (internal_pin_t){.port = GPIOC, .pin = 14};
    this->internal_DI_pins[SWITCH34] = (internal_pin_t){.port = GPIOC, .pin = 15};
    this->internal_DI_pins[SWITCH35] = (internal_pin_t){.port = GPIOF, .pin = 0};
    this->internal_DI_pins[SWITCH36] = (internal_pin_t){.port = GPIOF, .pin = 1};
    this->internal_DI_pins[SWITCH37] = (internal_pin_t){.port = GPIOF, .pin = 2};
    this->internal_DI_pins[SWITCH38] = (internal_pin_t){.port = GPIOF, .pin = 3};
    this->internal_DI_pins[SWITCH39] = (internal_pin_t){.port = GPIOF, .pin = 4};
    this->internal_DI_pins[SWITCH40] = (internal_pin_t){.port = GPIOF, .pin = 5};

    this->internal_DI_pins[SWITCH_12v1] = (internal_pin_t){.port = GPIOF, .pin = 6};
    this->internal_DI_pins[SWITCH_12v2] = (internal_pin_t){.port = GPIOF, .pin = 7};
    this->internal_DI_pins[SWITCH_12v3] = (internal_pin_t){.port = GPIOF, .pin = 8};
    this->internal_DI_pins[SWITCH_12v4] = (internal_pin_t){.port = GPIOF, .pin = 9};
    this->internal_DI_pins[SWITCH_12v5] = (internal_pin_t){.port = GPIOF, .pin = 10};
    this->internal_DI_pins[SWITCH_12v6] = (internal_pin_t){.port = GPIOC, .pin = 0};
    this->internal_DI_pins[SWITCH_12v7] = (internal_pin_t){.port = GPIOC, .pin = 1};
    this->internal_DI_pins[SWITCH_12v8] = (internal_pin_t){.port = GPIOC, .pin = 2};
    this->internal_DI_pins[SWITCH_12v9] = (internal_pin_t){.port = GPIOC, .pin = 3};
    this->internal_DI_pins[SWITCH_12v10] = (internal_pin_t){.port = GPIOA, .pin = 0};

    this->internal_DI_pins[SWITCH_INSTA1] = (internal_pin_t){.port = GPIOA, .pin = 1};
    this->internal_DI_pins[SWITCH_INSTA2] = (internal_pin_t){.port = GPIOA, .pin = 2};
    this->internal_DI_pins[SWITCH_INSTA3] = (internal_pin_t){.port = GPIOA, .pin = 3};
    this->internal_DI_pins[SWITCH_INSTA4] = (internal_pin_t){.port = GPIOB, .pin = 2};
    this->internal_DI_pins[SWITCH_INSTA5] = (internal_pin_t){.port = GPIOF, .pin = 11};

    this->internal_DI_pins[SWITCH_3_A_1] = (internal_pin_t){.port = GPIOF, .pin = 12};
    this->internal_DI_pins[SWITCH_3_B_1] = (internal_pin_t){.port = GPIOF, .pin = 13};
    this->internal_DI_pins[SWITCH_3_A_2] = (internal_pin_t){.port = GPIOF, .pin = 14};
    this->internal_DI_pins[SWITCH_3_B_2] = (internal_pin_t){.port = GPIOF, .pin = 15};
    this->internal_DI_pins[SWITCH_3_A_3] = (internal_pin_t){.port = GPIOG, .pin = 0};
    this->internal_DI_pins[SWITCH_3_B_3] = (internal_pin_t){.port = GPIOG, .pin = 1};
    this->internal_DI_pins[SWITCH_3_A_4] = (internal_pin_t){.port = GPIOE, .pin = 7};
    this->internal_DI_pins[SWITCH_3_B_4] = (internal_pin_t){.port = GPIOE, .pin = 8};
    this->internal_DI_pins[SWITCH_3_A_5] = (internal_pin_t){.port = GPIOE, .pin = 9};
    this->internal_DI_pins[SWITCH_3_B_5] = (internal_pin_t){.port = GPIOE, .pin = 10};

    this->internal_DI_pins[SWITCH_4_A_1] = (internal_pin_t){.port = GPIOE, .pin = 11};
    this->internal_DI_pins[SWITCH_4_B_1] = (internal_pin_t){.port = GPIOE, .pin = 12};
    this->internal_DI_pins[SWITCH_4_C_1] = (internal_pin_t){.port = GPIOE, .pin = 13};
    this->internal_DI_pins[SWITCH_4_D_1] = (internal_pin_t){.port = GPIOE, .pin = 14};
    this->internal_DI_pins[SWITCH_4_A_2] = (internal_pin_t){.port = GPIOE, .pin = 15};
    this->internal_DI_pins[SWITCH_4_B_2] = (internal_pin_t){.port = GPIOB, .pin = 12};
    this->internal_DI_pins[SWITCH_4_C_2] = (internal_pin_t){.port = GPIOB, .pin = 13};
    this->internal_DI_pins[SWITCH_4_D_2] = (internal_pin_t){.port = GPIOB, .pin = 14};
    this->internal_DI_pins[SWITCH_4_A_3] = (internal_pin_t){.port = GPIOB, .pin = 15};
    this->internal_DI_pins[SWITCH_4_B_3] = (internal_pin_t){.port = GPIOD, .pin = 14};
    this->internal_DI_pins[SWITCH_4_C_3] = (internal_pin_t){.port = GPIOD, .pin = 15};
    this->internal_DI_pins[SWITCH_4_D_3] = (internal_pin_t){.port = GPIOG, .pin = 2};
    this->internal_DI_pins[SWITCH_4_A_4] = (internal_pin_t){.port = GPIOG, .pin = 3};
    this->internal_DI_pins[SWITCH_4_B_4] = (internal_pin_t){.port = GPIOG, .pin = 4};
    this->internal_DI_pins[SWITCH_4_C_4] = (internal_pin_t){.port = GPIOG, .pin = 5};
    this->internal_DI_pins[SWITCH_4_D_4] = (internal_pin_t){.port = GPIOG, .pin = 6};
    this->internal_DI_pins[SWITCH_4_A_5] = (internal_pin_t){.port = GPIOG, .pin = 7};
    this->internal_DI_pins[SWITCH_4_B_5] = (internal_pin_t){.port = GPIOG, .pin = 8};
    this->internal_DI_pins[SWITCH_4_C_5] = (internal_pin_t){.port = GPIOC, .pin = 8};
    this->internal_DI_pins[SWITCH_4_D_5] = (internal_pin_t){.port = GPIOC, .pin = 9};

    /* Assign values for external input pins */
    this->external_DI_pins[SWITCH_6_A_1 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPA0};
    this->external_DI_pins[SWITCH_6_B_1 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPA1};
    this->external_DI_pins[SWITCH_6_C_1 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPA2};
    this->external_DI_pins[SWITCH_6_D_1 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPA3};
    this->external_DI_pins[SWITCH_6_E_1 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPA4};
    this->external_DI_pins[SWITCH_6_F_1 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPA5};
    this->external_DI_pins[SWITCH_6_A_2 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPB0};
    this->external_DI_pins[SWITCH_6_B_2 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPB1};
    this->external_DI_pins[SWITCH_6_C_2 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPB2};
    this->external_DI_pins[SWITCH_6_D_2 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPB3};
    this->external_DI_pins[SWITCH_6_E_2 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPB4};
    this->external_DI_pins[SWITCH_6_F_2 - SWITCH_6_A_1] = (external_pin_t){.exp_num = 4, .pin = GPB5};

    this->external_DI_pins[SWITCH_12_A - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPA0};
    this->external_DI_pins[SWITCH_12_B - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPA1};
    this->external_DI_pins[SWITCH_12_C - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPA2};
    this->external_DI_pins[SWITCH_12_D - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPA3};
    this->external_DI_pins[SWITCH_12_E - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPA4};
    this->external_DI_pins[SWITCH_12_F - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPA5};
    this->external_DI_pins[SWITCH_12_G - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPB0};
    this->external_DI_pins[SWITCH_12_H - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPB1};
    this->external_DI_pins[SWITCH_12_I - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPB2};
    this->external_DI_pins[SWITCH_12_J - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPB3};
    this->external_DI_pins[SWITCH_12_K - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPB4};
    this->external_DI_pins[SWITCH_12_L - SWITCH_6_A_1] = (external_pin_t){.exp_num = 3, .pin = GPB5};

    /* Assign values for external output pins */
    this->external_DO_pins[LIGHT1] = (external_pin_t){.exp_num = 1, .pin = GPA0};
    this->external_DO_pins[LIGHT2] = (external_pin_t){.exp_num = 1, .pin = GPA1};
    this->external_DO_pins[LIGHT3] = (external_pin_t){.exp_num = 1, .pin = GPA2};
    this->external_DO_pins[LIGHT4] = (external_pin_t){.exp_num = 1, .pin = GPA3};
    this->external_DO_pins[LIGHT5] = (external_pin_t){.exp_num = 1, .pin = GPA4};
    this->external_DO_pins[LIGHT6] = (external_pin_t){.exp_num = 1, .pin = GPA5};
    this->external_DO_pins[LIGHT7] = (external_pin_t){.exp_num = 1, .pin = GPA6};
    this->external_DO_pins[LIGHT8] = (external_pin_t){.exp_num = 1, .pin = GPA7};
    this->external_DO_pins[LIGHT9] = (external_pin_t){.exp_num = 1, .pin = GPA0};
    this->external_DO_pins[LIGHT10] = (external_pin_t){.exp_num = 1, .pin = GPB1};
    this->external_DO_pins[LIGHT11] = (external_pin_t){.exp_num = 1, .pin = GPB2};
    this->external_DO_pins[LIGHT12] = (external_pin_t){.exp_num = 1, .pin = GPB3};
    this->external_DO_pins[LIGHT13] = (external_pin_t){.exp_num = 1, .pin = GPB4};
    this->external_DO_pins[LIGHT14] = (external_pin_t){.exp_num = 1, .pin = GPB5};
    this->external_DO_pins[LIGHT15] = (external_pin_t){.exp_num = 1, .pin = GPB6};
    this->external_DO_pins[LIGHT16] = (external_pin_t){.exp_num = 1, .pin = GPB7};
    this->external_DO_pins[LIGHT17] = (external_pin_t){.exp_num = 2, .pin = GPA0};
    this->external_DO_pins[LIGHT18] = (external_pin_t){.exp_num = 2, .pin = GPA1};
    this->external_DO_pins[LIGHT19] = (external_pin_t){.exp_num = 2, .pin = GPA2};
    this->external_DO_pins[LIGHT20] = (external_pin_t){.exp_num = 2, .pin = GPA3};
    this->external_DO_pins[LIGHT21] = (external_pin_t){.exp_num = 2, .pin = GPA4};
    this->external_DO_pins[LIGHT22] = (external_pin_t){.exp_num = 2, .pin = GPA5};
    this->external_DO_pins[LIGHT23] = (external_pin_t){.exp_num = 2, .pin = GPA6};
    this->external_DO_pins[LIGHT24] = (external_pin_t){.exp_num = 2, .pin = GPA7};
    this->external_DO_pins[LIGHT25] = (external_pin_t){.exp_num = 2, .pin = GPA0};
    this->external_DO_pins[LIGHT26] = (external_pin_t){.exp_num = 2, .pin = GPB1};
    this->external_DO_pins[LIGHT27] = (external_pin_t){.exp_num = 2, .pin = GPB2};
    this->external_DO_pins[LIGHT28] = (external_pin_t){.exp_num = 2, .pin = GPB3};
    this->external_DO_pins[LIGHT29] = (external_pin_t){.exp_num = 2, .pin = GPB4};
    this->external_DO_pins[LIGHT30] = (external_pin_t){.exp_num = 2, .pin = GPB5};
    this->external_DO_pins[LIGHT31] = (external_pin_t){.exp_num = 2, .pin = GPB6};
    this->external_DO_pins[LIGHT32] = (external_pin_t){.exp_num = 2, .pin = GPB7};

    /* Start DMA readings from internal ADC */
    HAL_ADC_Start_DMA(&hadc1, this->internal_AI_DMA_buffer, POT8 - POT1 + 1);

    /* Create and configure instances od DI / DO expanders */
    this->DI_DO_expanders[0] = MCP23017_create(&hi2c1, MCP_ADDRESS_1);
    this->DI_DO_expanders[0]->set_all_pins_as_output(this->DI_DO_expanders[0]);
    this->DI_DO_expanders[1] = MCP23017_create(&hi2c1, MCP_ADDRESS_2);
    this->DI_DO_expanders[1]->set_all_pins_as_output(this->DI_DO_expanders[1]);
    this->DI_DO_expanders[2] = MCP23017_create(&hi2c1, MCP_ADDRESS_3);
    this->DI_DO_expanders[2]->set_all_pins_as_input(this->DI_DO_expanders[2], TRUE);
    this->DI_DO_expanders[3] = MCP23017_create(&hi2c1, MCP_ADDRESS_4);
    this->DI_DO_expanders[3]->set_all_pins_as_input(this->DI_DO_expanders[3], TRUE);

    /* Create and configure instance of AI expander */
    this->AI_expander = MAX11616_create(&hi2c2, MAX11616_ADDRESS);
    this->AI_expander->configure(this->AI_expander);

    return &this->public;
}
