/*
 * task_manager.hpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#pragma once

#include "task.hpp"

#include <vector>
#include <cstdint>
#include <memory>

/* Signleton for managing and executing tasks */
class TaskManager
{
public:
    TaskManager(const TaskManager &) = delete;
    /**
     * Get instance of TaskManager 
     */
    static TaskManager &get();
    /**
     * Method to be called in infinite loop for tasks handling
     */
    void handle_tasks();
    /**
     * Method to be called in timer callback to schedule tasks
     */
    void schedule_tasks();
    /**
     * Add single task to queue
     * @param task     task to be added
     */
    void add_to_queue(std::unique_ptr<Task> task);
    /**
     * Add periodic task to queue
     * @note            if task is already in scheduled, it will be replaced
     * @param task      task to be added
     * @param period    period in ms between tasks
     */
    void add_periodic_task(std::shared_ptr<Task> task, uint32_t period);
    /**
     * Remove periodic task from queue
     * @param task     task to be removed
     */
    void remove_periodic_task(Task task);

private:
    /* Struct for scheduled event with period and remaining period. */
    struct ScheduledTask
    {
        std::shared_ptr<Task> task;
        uint32_t period;
        uint32_t remaining_period;
    };
    TaskManager();
    /* Queue of pending tasks */
    std::vector<std::unique_ptr<Task>> queue;
    /* Vector of events to be periodically scheduler TODO: Change to struct with time */
    std::vector<ScheduledTask> scheduled_vec;
};
