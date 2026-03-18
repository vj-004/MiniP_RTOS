#include "rtos.hpp"
#include "../scheduler/scheduler.hpp"
#include <iostream>
#include <thread>
#include <chrono>

RTOS::RTOS() {

    currentTask = -1;
    tick = 0;
    quantum = 3;
}

void RTOS::createTask(
    int id,
    int priority,
    std::function<void()> func
) {

    TCB t;

    t.id = id;
    t.priority = priority;
    t.state = TaskState::READY;
    t.delayTicks = 0;
    t.timeSlice = quantum;
    t.taskFunction = func;

    tasks.push_back(t);
}

void RTOS::systemTick() {

    tick++;

    std::cout << "\n[TICK " << tick << "]\n";

    updateDelays();

    if (currentTask != -1)
        tasks[currentTask].timeSlice--;
    

    if(currentTask != -1){
        if(tasks[currentTask].timeSlice == 0){
            tasks[currentTask].state = TaskState::TERMINATED;
            currentTask = -1;
        }
    }

    schedule();

    if (currentTask != -1)
        tasks[currentTask].taskFunction();
}

void RTOS::schedule() {


    if (currentTask == -1 ||
        tasks[currentTask].timeSlice <= 0) {

        std::set<int> taskIds =
            Scheduler::prioritySchedule(tasks);
        
        std:: cout << std:: endl;

        std::vector<TCB> rrTasks;
        
        for(auto task: tasks){
            if(taskIds.find(task.id) != taskIds.end()){
                rrTasks.push_back(task);
            }
        }
        
        int next = -1;
        if (taskIds.size() > 0){
            int identity =  
                Scheduler::roundRobinSchedule(
                    rrTasks,
                    currentTask
                );
                
            if(identity != -1){
                int n = tasks.size();
                for(int i=0;i<n;i++){
                    if(tasks[i].id == identity){
                        next = i;
                        break;
                    }
                }
            }  
        }
        
        // std::cout << "next is: " << next << '\n';

        if (next != -1)
            contextSwitch(next);
    }
}

void RTOS::contextSwitch(int nextTask) {

    if (currentTask != -1 &&
        tasks[currentTask].state ==
        TaskState::RUNNING) {

        tasks[currentTask].state = TaskState::READY;
    }

    currentTask = nextTask;

    tasks[currentTask].state = TaskState::RUNNING;

    tasks[currentTask].timeSlice = quantum;

    std::cout << "Context Switch -> Task "
              << tasks[currentTask].id
              << std::endl;
}

void RTOS::updateDelays() {

    for (auto &t : tasks) {

        if (t.state == TaskState::BLOCKED) {

            t.delayTicks--;

            if (t.delayTicks <= 0)
                t.state = TaskState::READY;
        }
    }
}

void RTOS::start(int totalTicks) {

    for (int i = 0; i < totalTicks; i++) {

        systemTick();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }
}