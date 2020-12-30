#include "tasks.hpp"
#include "../dictator.hpp"

void Tasks::TestTask::execute()
{
    uint8_t position = Dictator::get().switches[Dictator::Switches::SWITCH_2POS_2].get_position();
    if (position == 2)
    {
        Dictator::get().leds[Dictator::Leds::LED_1].set_state(true);
    }
    else
    {
        Dictator::get().leds[Dictator::Leds::LED_1].set_state(false);
    }
}

TasksTypes::TaskType Tasks::TestTask::get_type()
{
    return TasksTypes::TEST_TASK;
}
