#include "rtos.hpp"
#include "../scheduler/scheduler.hpp"
#include <iostream>
#include <thread>
#include <chrono>

RTOS::RTOS() {


}


void RTOS::start(int totalTicks) {

    for (int i = 0; i < totalTicks; i++) {

        systemTick();
        
        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }
}