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
    pins::pins_DO pin;
    bool state;
};

// Response with DI and AI states

union StateRes
{
    struct
    {
        pins::pins_DI DI_pin;
        bool state;
    } digital;
    struct
    {
        pins::pins_AI AI_pin;
        float value;
    } analog;
};

class PinMaster
{
public:
    PinMaster();
    ~PinMaster();
    void reload_inputs();
    void reload_outputs();
    void reset_outputs();
    void set_outputs(const std::vector<StateReq> &req_states);
    std::vector<StateRes> get_inputs(const std::vector<pins::pins_AI> &pins);
    std::vector<StateRes> get_inputs(const std::vector<pins::pins_DI> &pins);
    bool get_input(const pins::pins_DI &pin);
    float get_input(const pins::pins_AI &pin);
    void set_output(const pins::pins_DO &pin, bool state);
    void handle_interrupt(); // TODO: implement

private:
    std::array<bool, pins::PINS_DI_NUM> pins_DI_states;
    std::array<float, pins::PINS_AI_NUM> pins_AI_states;
    std::array<bool, pins::PINS_DO_NUM> pins_DO_required_states;
    std::array<internal_pin, pins::SWITCH_4_D_5 - pins::SWITCH1 + 1> internal_DI_pins;
    std::array<external_pin, pins::SWITCH_12_L - pins::SWITCH_6_A_1 + 1> external_DI_pins;
    std::array<external_pin, pins::LIGHT32 - pins::LIGHT1 + 1> external_DO_pins;
    uint32_t internal_AI_DMA_buffer[pins::POT8 - pins::POT1 + 1];
    std::array<MCP23017, 4> DI_DO_expanders;
    MAX11616 AI_expander;
};

/**
 * One and only one instance of Dictator
 */
extern PinMaster *pin_master;
