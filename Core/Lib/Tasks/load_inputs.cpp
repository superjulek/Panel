#include "tasks.hpp"
#include "../pin_master.hpp"

void Tasks::LoadInputs::execute()
{
    PinMaster::get().reload_inputs();
}

TasksTypes::TaskType Tasks::LoadInputs::get_type()
{
    return TasksTypes::LOAD_INPUTS;
}
