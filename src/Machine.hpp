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

class Executor;

class Machine {
    private:
        bitset<BYTE_SIZE> memory[MEMORY_SIZE];
        bitset<BYTE_SIZE> general_registers[NUM_REGISTERS];
        bitset<WORD_SIZE> vi;
        bitset<BYTE_SIZE> delay_timer;
        bitset<BYTE_SIZE> sound_timer;
        bitset<BYTE_SIZE> sp;
        bitset<WORD_SIZE> pc;
        void print_memory() const;
        void print_memory_table_entry(int row, int col) const;
        Executor *executor;
        bool exit;

    public:
        Machine();
        void print_state() const;
        void load_rom(ROM &rom);
        bitset<BYTE_SIZE> getMemoryState();
        void run();
        void print_registers() const;
        bitset<WORD_SIZE> next_byte_to_pc();
        bitset<WORD_SIZE> get_next_instruction();
        void pc_to_next_instruction();
        void set_exit_flag();
        void set_pc(int addr);
        std::string pc_to_string();
};