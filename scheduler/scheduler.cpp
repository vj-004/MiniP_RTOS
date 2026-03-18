#include "scheduler.hpp"
#include "iostream"

std::set<int> Scheduler::prioritySchedule(const std::vector<TCB>& tasks) {

    int highest = -1;

    std::set<int> priotiyTasks;
    int n = tasks.size();
    for (int i = 0; i < n; i++) {

        if (tasks[i].state == TaskState::READY) {

            if(tasks[i].priority > highest){
                priotiyTasks.clear();    
                highest = tasks[i].priority;
            }
            if(tasks[i].priority == highest){
                priotiyTasks.insert(tasks[i].id);
            }
        }
    }

    // std :: cout << "Priority Tasks id list\n";
    // for(auto it: priotiyTasks){
    //     std:: cout <<  it << " ";
    // }

    return priotiyTasks;
}

int Scheduler::roundRobinSchedule(
    const std::vector<TCB>& tasks,
    int currentTask
) {

    int n = tasks.size();
    int idxofCT = -1;

    for(int i=0;i<n;i++){
        if(tasks[i].id == currentTask){
            idxofCT = i;
            break;
        }
    }

    if(n>0)
    {
        if(idxofCT == -1) return tasks[0].id;
        return tasks[(idxofCT+1)%n].id;
    }    

    
    return -1;
}