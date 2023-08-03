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
#define STACK_SIZE 16

using namespace std;

class Executor;

class Machine {
    private:
        bitset<BYTE_SIZE> memory[MEMORY_SIZE];
        bitset<BYTE_SIZE> general_registers[NUM_REGISTERS];
        bitset<WORD_SIZE> stack[STACK_SIZE];
        bitset<WORD_SIZE> vi;
        bitset<BYTE_SIZE> delay_timer;
        bitset<BYTE_SIZE> sound_timer;
        bitset<WORD_SIZE> pc;
        int sp;
        void print_memory() const;
        void print_memory_table_entry(int row, int col) const;
        Executor *executor;
        bool exit;
        void incr_sp();
        void dec_sp();
        bitset<WORD_SIZE> next_byte_to_pc();

    public:
        Machine();
        void print_state() const;
        void load_rom(ROM &rom);
        bitset<BYTE_SIZE> getMemoryState();
        void run();
        void print_registers() const;
        bitset<WORD_SIZE> get_current_instruction();
        void advance_pc();
        void set_exit_flag();
        void set_pc(int addr);
        bitset<WORD_SIZE> get_pc();
        std::string pc_to_string();
        bitset<WORD_SIZE> get_next_instruction();
        void push_to_stack(const bitset<WORD_SIZE>& addr);
        bitset<WORD_SIZE> pop_off_stack();
        bitset<WORD_SIZE>* get_stack();
        int get_sp();
        bitset<BYTE_SIZE> read_register(int reg);
        void set_register(int reg, int val);
        void set_register(int reg, const std::bitset<BYTE_SIZE>& val);
        void set_vi(const std::bitset<WORD_SIZE>& val);
        void set_vi(int val);
        std::bitset<WORD_SIZE> get_vi();
        std::bitset<BYTE_SIZE> get_dt();
        void set_dt(int val);
        std::bitset<BYTE_SIZE> get_st();
        void set_st(int val);
};