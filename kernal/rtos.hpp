#pragma once
#include "../task/task.hpp"
#include <vector>

class RTOS {

private:

    std::vector<TCB> tasks;
    int currentTask;
    int tick;
    int quantum;

public:

    RTOS();

    void createTask(
        int id, 
        int priority,
        std::function<void()> func
    );

    void start(int totalTicks);

private:

    void systemTick();

    void schedule();

    void contextSwitch(int nextTask);

    void updateDelays();
};