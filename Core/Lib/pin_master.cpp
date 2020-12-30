/*
 * pin_master.c
 *
 *  Created on: Dec 10, 2020
 *      Author: juliusz
 */

#include "pin_master.hpp"
#include "mcp23017.hpp"
#include "max11616.hpp"

#include <array>
#include "stm32h7xx_hal.h"
#include "adc.h"
#include "i2c.h"

#define INTERNAL_ADC_MAX 65536.

PinMaster::PinMaster()
    : DI_DO_expanders{MCP23017{&hi2c1, MCP_ADDRESS_1}, MCP23017{&hi2c1, MCP_ADDRESS_2},
                      MCP23017{&hi2c1, MCP_ADDRESS_3}, MCP23017{&hi2c1, MCP_ADDRESS_4}},
      AI_expander(&hi2c2, MAX11616_ADDRESS)
{
    /* Reset DI pins */
    for (int pin = pins::SWITCH1; pin <= pins::SWITCH_12_L; ++pin)
    {
        pins_DI_states[pin] = false;
    }
    /* Reset DO pins */
    for (int pin = pins::LIGHT1; pin <= pins::LIGHT32; ++pin)
    {
        pins_DO_required_states[pin] = false;
    }
    /* Reset AI pins */
    for (int pin = pins::POT1; pin <= pins::JOY_MID_3; ++pin)
    {
        pins_AI_states[pin] = false;
    }

    /* All pins are asigned here since there will always be only one instance of pin_master_t */

    /* Assign values for internal input pins */
    internal_DI_pins[pins::SWITCH1] = (internal_pin){.port = GPIOA, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH2] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_10};
    internal_DI_pins[pins::SWITCH3] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_11};
    internal_DI_pins[pins::SWITCH4] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_12};
    internal_DI_pins[pins::SWITCH5] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_0};
    internal_DI_pins[pins::SWITCH6] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_1};
    internal_DI_pins[pins::SWITCH7] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH8] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH9] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_4};
    internal_DI_pins[pins::SWITCH10] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_5};
    internal_DI_pins[pins::SWITCH11] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_6};
    internal_DI_pins[pins::SWITCH12] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_7};
    internal_DI_pins[pins::SWITCH13] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_9};
    internal_DI_pins[pins::SWITCH14] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_10};
    internal_DI_pins[pins::SWITCH15] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_11};
    internal_DI_pins[pins::SWITCH16] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_12};
    internal_DI_pins[pins::SWITCH17] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_13};
    internal_DI_pins[pins::SWITCH18] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_14};
    internal_DI_pins[pins::SWITCH19] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH20] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH21] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_4};
    internal_DI_pins[pins::SWITCH22] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_5};
    internal_DI_pins[pins::SWITCH23] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_6};
    internal_DI_pins[pins::SWITCH24] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_7};
    internal_DI_pins[pins::SWITCH25] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_0};
    internal_DI_pins[pins::SWITCH26] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_1};
    internal_DI_pins[pins::SWITCH27] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH28] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH29] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_4};
    internal_DI_pins[pins::SWITCH30] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_5};
    internal_DI_pins[pins::SWITCH31] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_6};
    internal_DI_pins[pins::SWITCH32] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_13};
    internal_DI_pins[pins::SWITCH33] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_14};
    internal_DI_pins[pins::SWITCH34] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH35] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_0};
    internal_DI_pins[pins::SWITCH36] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_1};
    internal_DI_pins[pins::SWITCH37] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH38] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH39] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_4};
    internal_DI_pins[pins::SWITCH40] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_5};

    internal_DI_pins[pins::SWITCH_12v1] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_6};
    internal_DI_pins[pins::SWITCH_12v2] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_7};
    internal_DI_pins[pins::SWITCH_12v3] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_8};
    internal_DI_pins[pins::SWITCH_12v4] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_9};
    internal_DI_pins[pins::SWITCH_12v5] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_10};
    internal_DI_pins[pins::SWITCH_12v6] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_0};
    internal_DI_pins[pins::SWITCH_12v7] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_1};
    internal_DI_pins[pins::SWITCH_12v8] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH_12v9] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH_12v10] = (internal_pin){.port = GPIOA, .pin = GPIO_PIN_0};

    internal_DI_pins[pins::SWITCH_INSTA1] = (internal_pin){.port = GPIOA, .pin = GPIO_PIN_1};
    internal_DI_pins[pins::SWITCH_INSTA2] = (internal_pin){.port = GPIOA, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH_INSTA3] = (internal_pin){.port = GPIOA, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH_INSTA4] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH_INSTA5] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_11};

    internal_DI_pins[pins::SWITCH_3_A_1] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_12};
    internal_DI_pins[pins::SWITCH_3_B_1] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_13};
    internal_DI_pins[pins::SWITCH_3_A_2] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_14};
    internal_DI_pins[pins::SWITCH_3_B_2] = (internal_pin){.port = GPIOF, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH_3_A_3] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_0};
    internal_DI_pins[pins::SWITCH_3_B_3] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_1};
    internal_DI_pins[pins::SWITCH_3_A_4] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_7};
    internal_DI_pins[pins::SWITCH_3_B_4] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_8};
    internal_DI_pins[pins::SWITCH_3_A_5] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_9};
    internal_DI_pins[pins::SWITCH_3_B_5] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_10};

    internal_DI_pins[pins::SWITCH_4_A_1] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_11};
    internal_DI_pins[pins::SWITCH_4_B_1] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_12};
    internal_DI_pins[pins::SWITCH_4_C_1] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_13};
    internal_DI_pins[pins::SWITCH_4_D_1] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_14};
    internal_DI_pins[pins::SWITCH_4_A_2] = (internal_pin){.port = GPIOE, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH_4_B_2] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_12};
    internal_DI_pins[pins::SWITCH_4_C_2] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_13};
    internal_DI_pins[pins::SWITCH_4_D_2] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_14};
    internal_DI_pins[pins::SWITCH_4_A_3] = (internal_pin){.port = GPIOB, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH_4_B_3] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_14};
    internal_DI_pins[pins::SWITCH_4_C_3] = (internal_pin){.port = GPIOD, .pin = GPIO_PIN_15};
    internal_DI_pins[pins::SWITCH_4_D_3] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_2};
    internal_DI_pins[pins::SWITCH_4_A_4] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_3};
    internal_DI_pins[pins::SWITCH_4_B_4] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_4};
    internal_DI_pins[pins::SWITCH_4_C_4] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_5};
    internal_DI_pins[pins::SWITCH_4_D_4] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_6};
    internal_DI_pins[pins::SWITCH_4_A_5] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_7};
    internal_DI_pins[pins::SWITCH_4_B_5] = (internal_pin){.port = GPIOG, .pin = GPIO_PIN_8};
    internal_DI_pins[pins::SWITCH_4_C_5] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_8};
    internal_DI_pins[pins::SWITCH_4_D_5] = (internal_pin){.port = GPIOC, .pin = GPIO_PIN_9};

    /* Assign values for external input pins */
    external_DI_pins[pins::SWITCH_6_A_1 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPA0};
    external_DI_pins[pins::SWITCH_6_B_1 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPA1};
    external_DI_pins[pins::SWITCH_6_C_1 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPA2};
    external_DI_pins[pins::SWITCH_6_D_1 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPA3};
    external_DI_pins[pins::SWITCH_6_E_1 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPA4};
    external_DI_pins[pins::SWITCH_6_F_1 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPA5};
    external_DI_pins[pins::SWITCH_6_A_2 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPB0};
    external_DI_pins[pins::SWITCH_6_B_2 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPB1};
    external_DI_pins[pins::SWITCH_6_C_2 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPB2};
    external_DI_pins[pins::SWITCH_6_D_2 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPB3};
    external_DI_pins[pins::SWITCH_6_E_2 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPB4};
    external_DI_pins[pins::SWITCH_6_F_2 - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 4, .pin = MCP23017::MCP23017_pin::GPB5};

    external_DI_pins[pins::SWITCH_12_A - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPA0};
    external_DI_pins[pins::SWITCH_12_B - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPA1};
    external_DI_pins[pins::SWITCH_12_C - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPA2};
    external_DI_pins[pins::SWITCH_12_D - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPA3};
    external_DI_pins[pins::SWITCH_12_E - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPA4};
    external_DI_pins[pins::SWITCH_12_F - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPA5};
    external_DI_pins[pins::SWITCH_12_G - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPB0};
    external_DI_pins[pins::SWITCH_12_H - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPB1};
    external_DI_pins[pins::SWITCH_12_I - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPB2};
    external_DI_pins[pins::SWITCH_12_J - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPB3};
    external_DI_pins[pins::SWITCH_12_K - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPB4};
    external_DI_pins[pins::SWITCH_12_L - pins::SWITCH_6_A_1] = (external_pin){.exp_num = 3, .pin = MCP23017::MCP23017_pin::GPB5};

    /* Assign values for external output pins */
    external_DO_pins[pins::LIGHT1] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA0};
    external_DO_pins[pins::LIGHT2] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA1};
    external_DO_pins[pins::LIGHT3] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA2};
    external_DO_pins[pins::LIGHT4] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA3};
    external_DO_pins[pins::LIGHT5] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA4};
    external_DO_pins[pins::LIGHT6] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA5};
    external_DO_pins[pins::LIGHT7] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA6};
    external_DO_pins[pins::LIGHT8] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPA7};
    external_DO_pins[pins::LIGHT9] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB0};
    external_DO_pins[pins::LIGHT10] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB1};
    external_DO_pins[pins::LIGHT11] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB2};
    external_DO_pins[pins::LIGHT12] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB3};
    external_DO_pins[pins::LIGHT13] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB4};
    external_DO_pins[pins::LIGHT14] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB5};
    external_DO_pins[pins::LIGHT15] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB6};
    external_DO_pins[pins::LIGHT16] = (external_pin){.exp_num = 1, .pin = MCP23017::MCP23017_pin::GPB7};
    external_DO_pins[pins::LIGHT17] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA0};
    external_DO_pins[pins::LIGHT18] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA1};
    external_DO_pins[pins::LIGHT19] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA2};
    external_DO_pins[pins::LIGHT20] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA3};
    external_DO_pins[pins::LIGHT21] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA4};
    external_DO_pins[pins::LIGHT22] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA5};
    external_DO_pins[pins::LIGHT23] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA6};
    external_DO_pins[pins::LIGHT24] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPA7};
    external_DO_pins[pins::LIGHT25] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB0};
    external_DO_pins[pins::LIGHT26] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB1};
    external_DO_pins[pins::LIGHT27] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB2};
    external_DO_pins[pins::LIGHT28] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB3};
    external_DO_pins[pins::LIGHT29] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB4};
    external_DO_pins[pins::LIGHT30] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB5};
    external_DO_pins[pins::LIGHT31] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB6};
    external_DO_pins[pins::LIGHT32] = (external_pin){.exp_num = 2, .pin = MCP23017::MCP23017_pin::GPB7};

    /* Asign interrupt pins */
    interrupt_pins.push_back({pins::SWITCH1, false});
    interrupt_pins.push_back({pins::SWITCH2, false});
    interrupt_pins.push_back({pins::SWITCH3, false});
    interrupt_pins.push_back({pins::SWITCH4, false});
    interrupt_pins.push_back({pins::SWITCH5, false});
    interrupt_pins.push_back({pins::SWITCH6, false});
    interrupt_pins.push_back({pins::SWITCH7, false});
    interrupt_pins.push_back({pins::SWITCH8, false});
    interrupt_pins.push_back({pins::SWITCH9, false});
    interrupt_pins.push_back({pins::SWITCH10, false});

    /* Start DMA readings from internal ADC */
    HAL_ADC_Start_DMA(&hadc1, internal_AI_DMA_buffer, pins::POT8 - pins::POT1 + 1);

    /* Create and configure instances od DI / DO expanders */
    DI_DO_expanders[0].set_all_pins_as_output();
    DI_DO_expanders[1].set_all_pins_as_output();
    DI_DO_expanders[2].set_all_pins_as_input(true);
    DI_DO_expanders[3].set_all_pins_as_input(true);

    /* Create and configure instance of AI expander */
    AI_expander.configure();
}

void PinMaster::reload_inputs()
{
    /* Read internal DI pins */
    for (int pin = pins::SWITCH1; pin <= pins::SWITCH_4_D_5; ++pin)
    {
        pins_DI_states[pin] = HAL_GPIO_ReadPin(internal_DI_pins[pin].port, internal_DI_pins[pin].pin);
    }

    /* Apply interrupt latch */
    for (InterruptPinLatch &pin : interrupt_pins)
    {
        if (pin.fired)
        {
            pins_DI_states[pin.pin] = true;
            /* Clear latch */
            pin.fired = false;
        }
    }

    /* Read external DI pins */
    std::array<bool, MCP_PINS_NUM> states_first = DI_DO_expanders[2].get_all_pins();  // first input expander - no 3 (index 2)
    std::array<bool, MCP_PINS_NUM> states_second = DI_DO_expanders[3].get_all_pins(); // second input expander - no 4 (index 3)
    for (int pin = pins::SWITCH_6_A_1; pin <= pins::SWITCH_12_L; ++pin)
    {
        external_pin ext_pin = external_DI_pins[pin - pins::SWITCH_6_A_1];
        switch (ext_pin.exp_num)
        {
        case 3:
            pins_DI_states[pin] = states_first[ext_pin.pin];
            break;
        case 4:
            pins_DI_states[pin] = states_second[ext_pin.pin];
            break;
        }
    }

    /* Read internal AI pins */
    for (int pin = pins::POT1; pin <= pins::POT8; ++pin)
    {
        /* Reading are in good order in buffer */
        pins_AI_states[pin] = (float)(internal_AI_DMA_buffer[pin] & 0xFFFF) / INTERNAL_ADC_MAX; // TODO: calibration
    }

    /* Read external AI pins */
    std::array<float, MAX_PINS_NUM> states = AI_expander.measure_all_pins();
    for (int pin = pins::JOY_X_1; pin <= pins::JOY_MID_3; ++pin)
    {
        /* Reading are in good order */
        pins_AI_states[pin] = states[pin - pins::JOY_X_1];
    }
}

void PinMaster::reload_outputs()
{
    /* Set external DO pins */
    std::array<bool, MCP_PINS_NUM> states_first;
    std::array<bool, MCP_PINS_NUM> states_second;
    for (int pin = pins::LIGHT1; pin <= pins::LIGHT32; ++pin)
    {
        external_pin ext_pin = external_DO_pins[pin - pins::LIGHT1];
        switch (ext_pin.exp_num)
        {
        case 1:
            states_first[ext_pin.pin] = pins_DO_required_states[pin];
            break;
        case 2:
            states_second[ext_pin.pin] = pins_DO_required_states[pin];
            break;
        }
    }
    DI_DO_expanders[0].set_all_pins(states_first);  // first output expander - no 1 (index 0)
    DI_DO_expanders[1].set_all_pins(states_second); // second output expander - no 2 (index 1)
}

void PinMaster::set_outputs(const std::vector<StateReq> &req_states)
{
    for (StateReq request : req_states)
    {
        pins_DO_required_states[request.pin] = request.state;
    }
}
std::vector<StateRes> PinMaster::get_inputs(const std::vector<pins::pins_AI> &pins)
{
    std::vector<StateRes> response;
    for (pins::pins_AI pin : pins)
    {
        StateRes state;
        state.analog = {pin, this->pins_AI_states[pin]};
        response.push_back(state);
    }
    return response;
}
std::vector<StateRes> PinMaster::get_inputs(const std::vector<pins::pins_DI> &pins)
{
    std::vector<StateRes> response;
    for (pins::pins_DI pin : pins)
    {
        StateRes state;
        state.digital = {pin, this->pins_DI_states[pin]};
        response.push_back(state);
    }
    return response;
}

bool PinMaster::get_input(const pins::pins_DI &pin)
{
    return pins_DI_states[pin];
}
float PinMaster::get_input(const pins::pins_AI &pin)
{
    return pins_AI_states[pin];
}
void PinMaster::set_output(const pins::pins_DO &pin, bool state)
{
    pins_DO_required_states[pin] = state;
}

PinMaster &PinMaster::get()
{
    static PinMaster instance;
    return instance;
}

void PinMaster::handle_interrupt(uint16_t GPIO_Pin)
{
    for (InterruptPinLatch &pin : interrupt_pins)
    {
        if (GPIO_Pin == internal_DI_pins[pin.pin].pin)
        {
            pin.fired = true;
        }
    }
}
