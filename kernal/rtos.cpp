#include "rtos.hpp"
#include "../scheduler/scheduler.hpp"
#include <iostream>
#include <thread>
#include <chrono>

RTOS::RTOS() {
    currentTaskId = -1;
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

    task[id] = t;
    task_queues[priority].push(id);

}

void RTOS::systemTick() {

    tick++;

    std::cout << "\n[TICK " << tick << "]\n";

    // what is this function doing?
    updateDelays();

    if (currentTaskId != -1)
        task[currentTaskId].timeSlice--;
    

    if(currentTaskId != -1){
        if(task[currentTaskId].timeSlice == 0){
            task[currentTaskId].state = TaskState::TERMINATED;
            currentTaskId = -1;
        }
    }

    schedule();

    if (currentTaskId != -1)
        task[currentTaskId].taskFunction();
}

void RTOS::schedule() {


    if (currentTaskId == -1 ||
        tasks[currentTaskId].timeSlice <= 0) {
            
        int next = -1;
        
        while(task_queues.size() > 0){
            int maxPriority = task_queues.rbegin()->first;
            next = task_queues[maxPriority].front();
            while(task_queues[maxPriority].size() > 0 && task[next].state == TaskState::TERMINATED){
                task_queues[maxPriority].pop();         
                next = task_queues[maxPriority].front();       
            }
            if(task_queues[maxPriority].size() == 0){
                task_queues.erase(maxPriority);
            }

        }    
        
        
        

        if (next != -1)
            contextSwitch(next);
    }
}

void RTOS::contextSwitch(int nextTask) {

    if (currentTaskId != -1 &&
        tasks[currentTaskId].state ==
        TaskState::RUNNING) {

        tasks[currentTaskId].state = TaskState::READY;
    }

    currentTaskId = nextTask;

    tasks[currentTaskId].state = TaskState::RUNNING;

    tasks[currentTaskId].timeSlice = quantum;

    std::cout << "Context Switch -> Task "
              << tasks[currentTaskId].id
              << std::endl;
}

void RTOS::updateDelays() {

    for (auto &t : task) {

        if (t.second.state == TaskState::BLOCKED) {

            t.second.delayTicks--;

            if (t.second.delayTicks <= 0)
                t.second.state = TaskState::READY;
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