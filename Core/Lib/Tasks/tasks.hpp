/**
 * Header file for all tasks
 */

#include "../task.hpp"

namespace Tasks
{
    /**
 * Flashing built in LED
 */
    class FlashLed : public Task
    {
    public:
        void execute() override;
        TasksTypes::TaskType get_type() override;
    };
} // namespace Tasks
