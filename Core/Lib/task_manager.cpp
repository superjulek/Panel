/*
 * task_manager.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#include "task_manager.hpp"

TaskManager::TaskManager()
{
}

TaskManager &TaskManager::get()
{
    static TaskManager instance;
    return instance;
}

void TaskManager::handle_tasks()
{
    if (queue.size() > 0)
    {
        queue.at(0)->execute();
    }
}
void TaskManager::add_to_queue(std::unique_ptr<Task> event)
{
    queue.push_back(std::move(event));
}

void TaskManager::add_periodic_task(std::shared_ptr<Task> task, uint32_t period)
{
    /* Construct ScheduledTask */
    ScheduledTask scheduled_task = {task, period, period};

    /* Check if event is already in vector */
    bool was_found = false;
    for (uint i = 0; i < scheduled_vec.size(); ++i)
    {
        if (scheduled_vec.at(i).task->get_type() == task->get_type())
        {
            scheduled_vec.at(i) = scheduled_task;
            was_found = true;
        }
    }
    if (!was_found)
    {
        scheduled_vec.push_back(scheduled_task);
    }
}
