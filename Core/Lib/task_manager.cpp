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
