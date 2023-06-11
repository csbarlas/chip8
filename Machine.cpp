#include "Machine.hpp"
#include <iostream>
#include <bitset>
#include <iomanip>

using namespace std;

Machine::Machine() {}

void Machine::print_state() {
    print_registers();
    print_memory();
}

void Machine::print_registers() {
    cout << "registers: " << endl;
    for(int i = 0; i < NUM_REGISTERS; i++) {
        cout << "V" << hex << i << ": " << general_registers[i] << endl;
    }

    cout << setw(13) << "Vi: " << vi << endl;
    cout << "delay timer: " << delay_timer << endl;
    cout << "sound timer: " << sound_timer << endl;
    cout << setw(13) << "stack ptr: " << sp << endl;
    cout << setw(13) << "pc: " << pc << endl;
}

void Machine::print_memory() {
    std::cout << "memory: " << std::endl;
    for(int i = 0; i < MEMORY_TABLE_ROWS; i++) {
        for(int j = 0; j < MEMORY_TABLE_COLS - 1; j++)
        {
            print_memory_table_entry(i, j);
            std::cout << " | ";
        }
        print_memory_table_entry(i, MEMORY_TABLE_COLS - 1);
        std::cout << std::endl;
    }
}

void Machine::print_memory_table_entry(int row, int col) {
    int entry = row + (col * MEMORY_TABLE_ROWS);
    std::cout << std::setfill('0') << std::setw(3) << std::hex << entry << ": " << memory[entry];
}

void Machine::load_rom(ROM rom) {
    
}