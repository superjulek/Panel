/**
 * Header file for all events
 */

#include "../event.hpp"

namespace Events
{
    /**
 * Flashing built in LED
 */
    class FlashLight : public Event
    {
    public:
        void Execute();
    };
} // namespace Events