#include "tasks.hpp"
#include "stm32h7xx_hal.h"
#include "../../Inc/main.h"

void Tasks::FlashLed::execute()
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

TasksTypes::TaskType Tasks::FlashLed::get_type()
{
    return TasksTypes::FLASH_LED;
}
