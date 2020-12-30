#include "tasks.hpp"
#include "../pin_master.hpp"

void Tasks::LoadOutputs::execute()
{
    PinMaster::get().reload_outputs();
}

TasksTypes::TaskType Tasks::LoadOutputs::get_type()
{
    return TasksTypes::LOAD_OUTPUTS;
}
