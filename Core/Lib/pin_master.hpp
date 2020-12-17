/*
 * pin_master.hpp
 *
 *  Created on: Dec 10, 2020
 *      Author: juliusz
 */

#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include "pins.hpp"
#include "general.hpp"
#include "mcp23017.hpp"
#include "max11616.hpp"

// Request for DO pins
struct StateReq
{
    pins_DO pin;
    bool state;
};

// Response with DI and AI states

struct StateRes
{
    union
    {
        struct
        {
            pins_DI DI_pin;
            bool state;
        } digital;
        struct
        {
            pins_AI AI_pin;
            float value;
        } analog;
    };
};

class PinMaster
{
public:
    PinMaster();
    ~PinMaster();
    void reload_inputs();
    void reload_outputs();
    void reset_outputs();
    void set_inputs(const std::vector<StateReq> &req_states);
    std::vector<StateRes> get_inputs(const std::vector<pins_AI> &pins);
    std::vector<StateRes> get_inputs(const std::vector<pins_DI> &pins);

private:
    std::array<bool, PINS_DI_NUM> pins_DI_states;
    std::array<float, PINS_AI_NUM> pins_AI_states;
    std::array<bool, PINS_DO_NUM> pins_DO_required_states;
    std::array<internal_pin, SWITCH_4_D_5 - SWITCH1 + 1> internal_DI_pins;
    std::array<external_pin, SWITCH_12_L - SWITCH_6_A_1 + 1> external_DI_pins;
    std::array<external_pin, LIGHT32 - LIGHT1 + 1> external_DO_pins;
    uint32_t internal_AI_DMA_buffer[POT8 - POT1 + 1];
    std::array<MCP23017, 4> DI_DO_expanders;
    MAX11616 AI_expander;
};
