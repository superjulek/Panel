/*
 * task.hpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#pragma once

namespace TasksTypes
{
    enum TaskType
    {
        UNIMPLEMENTED,
        FLASH_LED,
        LOAD_INPUTS,
        LOAD_OUTPUTS,
        TEST_TASK,
    };
} // namespace TasksTypes

class Task
{
public:
    Task();
    Task(Task &&other) noexcept;
    virtual void execute();
    virtual TasksTypes::TaskType get_type();
};
