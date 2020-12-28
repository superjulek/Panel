/*
 * event.hpp
 *
 *  Created on: Dec 24, 2020
 *      Author: juliusz
 */

#pragma once

class Event
{
public:
    Event();
    Event(Event &&other) noexcept;
    virtual void Execute();

private:
    bool test;
};
