#include "Machine.hpp"
#include "Executor.hpp"
#include <iostream>
#include <bitset>
#include <iomanip>
#include <sstream>

using namespace std;

Machine::Machine() {
    executor = new Executor(this);
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
    exit = false;
    sp = 0;
    vi = 0;
}

void Machine::run(){
    display.init();
    while (!exit) {
        auto currentInstruction = get_current_instruction();
        std::cout << "now executing: " << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << currentInstruction.to_ulong() << std::endl;
        executor->execute(currentInstruction);
    }

    std::cout << "exiting..." << std::endl;
    display.teardown();
}

bitset<WORD_SIZE> Machine::get_current_instruction() {
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

void Machine::advance_pc() {
    ulong temp_pc = pc.to_ulong();
    temp_pc += 2;
    pc = temp_pc;
}

bitset<WORD_SIZE> Machine::get_next_instruction() {
    bitset<BYTE_SIZE> upper = memory[pc.to_ulong() + 2];
    auto pc_offset_one_byte = next_byte_to_pc().to_ulong() + 2;
    bitset<BYTE_SIZE> lower = memory[pc_offset_one_byte];
    bitset<WORD_SIZE> ret((upper.to_ulong() << 8) + lower.to_ulong());
    return ret;
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

void Machine::incr_sp() {
    sp += 1;
}

void Machine::dec_sp() {
    sp -= 1;
}

bitset<WORD_SIZE> Machine::get_pc() {
    return pc;
}

void Machine::push_to_stack(const bitset<WORD_SIZE>& addr) {
    //CHIP-8 only allows for 16 levels of stack
    if(sp > 15 || sp < 0) {
        //fatal error
        //refactor into fatal error function to perform cleanup?
        std::cout << "too many values on the stack!" << std::endl;
        std::exit(0);
    } else {
        stack[sp] = addr;
        sp += 1;
    }
}

bitset<WORD_SIZE> Machine::pop_off_stack() {
    bitset<WORD_SIZE> ret(0);
    if(sp <= 0){
        std::cout << "error, cannot pop off stack any more!" << std::endl;
        std::exit(0);
    } else {
        ret = stack[sp].to_ulong();
        sp -= 1;
    }
    return ret;
}

bitset<WORD_SIZE>* Machine::get_stack() {
    return stack;
}

int Machine::get_sp() {
    return sp;
}

bitset<BYTE_SIZE> Machine::read_register(int reg) {
    return general_registers[reg];
}

// Note: For whatever reason, cannot give val as a hex value... weird...
void Machine::set_register(int reg, int val) {
    general_registers[reg] = val;
}

void Machine::set_register(int reg, const std::bitset<BYTE_SIZE>& val) {
    general_registers[reg] = val;
}

void Machine::set_vi(const std::bitset<WORD_SIZE>& val) {
    vi = val;
}

void Machine::set_vi(int val) {
    vi = val;
}

std::bitset<WORD_SIZE> Machine::get_vi() {
    return vi;
}

std::bitset<BYTE_SIZE> Machine::get_dt() {
    return delay_timer;
}

void Machine::set_dt(int val) {
    delay_timer = val;
}

std::bitset<BYTE_SIZE> Machine::get_st() {
    return sound_timer;
}

void Machine::set_st(int val) {
    sound_timer = val;
}

std::bitset<BYTE_SIZE> Machine::get_byte(int addr) {
    return memory[addr];
}