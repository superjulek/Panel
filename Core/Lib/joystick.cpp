#include "joystick.hpp"
#include "pin_master.hpp"

Joystick::Joystick(const std::vector<pins::pins_AI> &pins)
    : pins(pins)
{
    for (uint8_t i = 0; i < pins.size(); ++i)
    {
        range.push_back(1.);          // default range
        zero_position.push_back(0.5); // default zero position
    }
}

std::vector<float> Joystick::get_positions()
{
    std::vector<float> positions;
    std::vector<StateRes> states = PinMaster::get().get_inputs(pins);
    for (uint8_t axis = 0; axis < pins.size(); ++axis)
    {
        positions.push_back((states[axis].analog.value) - zero_position[axis] * range[axis]);
    }
    return positions;
}

void Joystick::reset_position()
{
    std::vector<StateRes> states = PinMaster::get().get_inputs(pins);
    for (uint8_t axis = 0; axis < pins.size(); ++axis)
    {
        zero_position[axis] = states[axis].analog.value;
    }
}

void Joystick::set_range(std::vector<float> range)
{
    for (uint8_t axis = 0; axis < pins.size(); ++axis)
    {
        this->range[axis] = range[axis];
    }
}
