/*
 * scheduler.hpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#pragma once

#include "events.hpp"

#include <vector>
#include <cstdint>

class Scheduler
{
public:
    Scheduler();
    /**
     * Method to be called in infinite loop for events handling
     */
    void handle_events();
    /**
     * Method to be called in timer callback to schedule events
     */
    void schedule_events();
    /**
     * Add single event to queue
     * @param event     event to be added
     */
    void add_to_queue(Event event);
    /**
     * Add periodic event to queue
     * @param event     event to be added
     * @param period    period in ms between events
     */
    void add_periodic_event(Event event, uint32_t period);
    /**
     * Remove periodic event from queue
     * @param event     event to be removed
     */
    void remove_periodic_event(Event event);

private:
    std::vector<void> queue;
};
