#pragma once
#include <functional>

enum class TaskState {
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
};

const int maxTicks = 3;

struct TCB {
    int id;
    std::string name;
    int priority;
    TaskState state;
    int delayTicks;
    int timeSlice;
    int ticksRemaining;
    int burstTime;
    std::function<void(void*)> taskFunction;
    int burstTime;
    void* taskArgs;

    TCB()
        : id(0), name(""), priority(0), state(TaskState::READY),
          delayTicks(0), timeSlice(maxTicks), ticksRemaining(maxTicks),
          taskFunction(nullptr), taskArgs(nullptr) {}

    TCB(int tid, std::string tname, int pri,
        std::function<void(void*)> func,
        void* args = nullptr, int ts = maxTicks)
        : id(tid), name(std::move(tname)), priority(pri),
          state(TaskState::READY), delayTicks(0),
          timeSlice(ts), ticksRemaining(ts),
          taskFunction(func), taskArgs(args) {}
};