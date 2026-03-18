#include "kernal/rtos.hpp"
#include <iostream>

int main() {

    RTOS rtos;

    rtos.createTask(
        1,
        2,
        []() {
            std::cout << "Task 1 executing\n";
        }
    );

    rtos.createTask(
        2,
        1,
        []() {
            std::cout << "Task 2 executing\n";
        }
    );

    rtos.createTask(
        3,
        3,
        []() {
            std::cout << "Task 3 executing\n";
        }
    );

    std:: cout << "Created Tasks: " << std::endl;

    rtos.start(10);

}