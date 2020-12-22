#include "joystick.hpp"
#include "pin_master.hpp"

Joystick::Joystick(const std::vector<pins::pins_AI> &pins)
    : pins(pins)
{
}

std::vector<float> Joystick::get_positions()
{
    std::vector<float> positions;
    std::vector<StateRes> states = PinMaster::get().get_inputs(pins);
    // Przeliczenie na pozycje
    return positions;
}
