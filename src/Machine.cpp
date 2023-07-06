#include "Machine.hpp"
#include "Executor.hpp"
#include <iostream>
#include <bitset>
#include <iomanip>
#include <sstream>

using namespace std;

Machine::Machine() {
    executor = new Executor(this);
    exit = false;
}

void Machine::print_state() const {
    cout << "Machine state: " << endl;
    print_registers();
    print_memory();
}

void Machine::print_registers() const{
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

void Machine::print_memory() const{
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

void Machine::print_memory_table_entry(int row, int col) const {
    int entry = row + (col * MEMORY_TABLE_ROWS);
    std::cout << std::setfill('0') << std::setw(3) << std::hex << entry << ": " << setfill('0') << setw(2) << hex << memory[entry].to_ulong();
}

void Machine::load_rom(ROM &rom) {
    int rom_size = rom.size();
    int load_addr = INITIAL_LOAD_ADDR;
    for(int i = 0; i < rom_size; i++) {
        memory[load_addr] = (int) rom.get_byte(i).to_ulong();
        load_addr++;
    }
    pc = 0x200;
}

void Machine::run(){
    while (!exit) {
        auto currentInstruction = get_next_instruction();
        std::cout << "now executing: " << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << currentInstruction.to_ulong() << std::endl;
        executor->execute(currentInstruction);
    }

    std::cout << "exiting..." << std::endl;
}

bitset<WORD_SIZE> Machine::get_next_instruction() {
    bitset<BYTE_SIZE> upper = memory[pc.to_ulong()];
    auto pc_offset_one_byte = next_byte_to_pc().to_ulong();
    bitset<BYTE_SIZE> lower = memory[pc_offset_one_byte];
    bitset<WORD_SIZE> ret((upper.to_ulong() << 8) + lower.to_ulong());
    return ret;
}

bitset<WORD_SIZE> Machine::next_byte_to_pc() {
    ulong temp_pc = pc.to_ulong();
    temp_pc++;
    bitset<WORD_SIZE> ret(temp_pc);
    return ret;
}

void Machine::pc_to_next_instruction() {
    ulong temp_pc = pc.to_ulong();
    temp_pc += 2;
    pc = temp_pc;
}

void Machine::set_exit_flag() {
    exit = true;
}

void Machine::set_pc(int addr) {
    pc = addr;
}

std::string Machine::pc_to_string() {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << pc.to_ulong();
    return stream.str();
}