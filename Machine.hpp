#pragma once
#include <cstddef>

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16

using namespace std;

class Machine {
    private:
        byte memory[MEMORY_SIZE];
        byte general_registers[NUM_REGISTERS];
        unsigned short vi;
        byte delay_timer;
        byte sound_timer;
        byte sp;
        unsigned short pc;

    public:
        Machine();
        void print_state();
};