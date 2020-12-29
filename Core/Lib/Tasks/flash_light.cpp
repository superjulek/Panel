#include "tasks.hpp"

void Tasks::FlashLed::execute()
{
}

TasksTypes::TaskType Tasks::FlashLed::get_type()
{
    return TasksTypes::FLASH_LED;
}
