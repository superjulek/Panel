/*
 * pin_master.hpp
 *
 *  Created on: Dec 10, 2020
 *      Author: juliusz
 */

#pragma once

#include <array>
#include <cstdint>
#include "pins.hpp"
#include "general.hpp"
#include "mcp23017.hpp"
#include "max11616.hpp"

class PinMaster
{
public:
    PinMaster();
    ~PinMaster();
    void reload_inputs();
    void reload_outputs();

private:
    std::array<bool, PINS_DI_NUM> pins_DI_states;
    std::array<bool, PINS_AI_NUM> pins_AI_states;
    std::array<bool, PINS_DO_NUM> pins_DO_required_states;
    std::array<internal_pin, SWITCH_4_D_5 - SWITCH1 + 1> internal_DI_pins;
    std::array<external_pin, SWITCH_12_L - SWITCH_6_A_1 + 1> external_DI_pins;
    std::array<external_pin, LIGHT32 - LIGHT1 + 1> external_DO_pins;
    uint32_t internal_AI_DMA_buffer[POT8 - POT1 + 1];
    std::array<MCP23017, 4> DI_DO_expanders;
    MAX11616 AI_expander;
};
