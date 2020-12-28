/*
 * scheduler.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#include "scheduler.hpp"

void Scheduler::handle_events()
{
    if (queue.size() > 0)
    {
        queue.at(0)->Execute();
    }
}
void Scheduler::add_to_queue(std::shared_ptr<Event> &&event)
{

}

