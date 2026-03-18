#pragma once
#include "../task/task.hpp"
#include <vector>
#include<set>

class Scheduler {

public:

    static std::set<int> prioritySchedule(const std::vector<TCB>& tasks);

    static int roundRobinSchedule(
        const std::vector<TCB>& tasks,
        int currentTask
    );
};