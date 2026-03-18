#pragma once
#include <functional>

enum class TaskState {
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
};

struct TCB {
    int id;
    int priority;
    TaskState state;
    int delayTicks;
    int timeSlice;
    std::function<void()> taskFunction;

    // Default Constructor
    TCB()
    : id(0), priority(0), state(TaskState::READY),
        delayTicks(0), timeSlice(0), taskFunction(nullptr) {}

    // Constructor sets defaults automatically
    TCB(int tid, int pri, std::function<void()> func, int ts = 0)
        : id(tid),
          priority(pri),
          state(TaskState::READY),  // READY by default
          delayTicks(0),
          timeSlice(ts),            // Default time slice = 0
          taskFunction(func) {}
};