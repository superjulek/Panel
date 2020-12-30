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

    /**
     * Reloading inputs
     */
    class LoadInputs : public Task
    {
    public:
        void execute() override;
        TasksTypes::TaskType get_type() override;
    };

    /**
     * Reloading outputs
     */
    class LoadOutputs : public Task
    {
    public:
        void execute() override;
        TasksTypes::TaskType get_type() override;
    };

    /**
     * Test task for debug
     */
    class TestTask : public Task
    {
    public:
        void execute() override;
        TasksTypes::TaskType get_type() override;
    };

} // namespace Tasks
