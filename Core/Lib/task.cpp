/*
 * task.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#include "task.hpp"

Task::Task()
{
}

Task::Task(Task &&other) noexcept
{
}

void Task::execute()
{
    return;
}

TasksTypes::TaskType Task::get_type()
{
    return TasksTypes::UNIMPLEMENTED;
}
