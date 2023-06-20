#pragma once
#include <bitset>

#include "ROM.hpp"

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define BYTE_SIZE 8
#define WORD_SIZE 16
#define MEMORY_TABLE_COLS 8 //Must be in a power of 2
#define MEMORY_TABLE_ROWS MEMORY_SIZE / MEMORY_TABLE_COLS
#define INITIAL_LOAD_ADDR 0x200

using namespace std;

class Machine {
    private:
        bitset<BYTE_SIZE> memory[MEMORY_SIZE];
        bitset<BYTE_SIZE> general_registers[NUM_REGISTERS];
        bitset<WORD_SIZE> vi;
        bitset<BYTE_SIZE> delay_timer;
        bitset<BYTE_SIZE> sound_timer;
        bitset<BYTE_SIZE> sp;
        bitset<WORD_SIZE> pc;

        void print_registers();
        void print_memory();
        void print_memory_table_entry(int row, int col);

    public:
        Machine();
        void print_state();
        void load_rom(ROM &rom);
};