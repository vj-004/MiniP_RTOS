#pragma once
#include "../task/task.hpp"
#include <vector>
#include <map>
#include <queue>

class RTOS {

private:

    std::vector<TCB> tasks;
    std::map<int,TCB> task;
    std::map<int,std::queue<int>> task_queues;
    int currentTaskId;
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