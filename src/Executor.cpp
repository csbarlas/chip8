/*
    Comments detailing information about each instruction used Cowgod's
    Chip-8 technical reference.
    Source: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Dxyn
*/

#include <string>
#include <sstream>
#include <iomanip>

#include "Executor.hpp"
#include "Machine.hpp"

Executor::Executor(Machine *m){
    machine = m;
}

/*
    Helper function that returns specified bytes from the given instruction
    as a string.
    NOTE: Byte 0 is the LSB as shown below
    -----------------------------
    |   byte 1    |    byte 0   |
    -----------------------------
*/
std::string Executor::bytes_to_str(const std::bitset<16>& instr, int from, int to) const {
    std::stringstream stream;

    int start_pos = (3 - to) * 4;
    int ending_pos = 15 - (4 * from);
    std::string temp = instr.to_string();
    temp = temp.substr(start_pos, ending_pos + 1);
    stream << std::setfill('0') << std::setw((to - from) + 1) << std::uppercase << std::hex << stoi(temp, nullptr, 2);
    return stream.str();
}

int Executor::bytes_to_int(const std::bitset<16>& instr, int from, int to){
    std::string temp_str = bytes_to_str(instr, from, to);
    int ret = std::stoi(temp_str, nullptr, 16);
    return ret;
}

/*
    Main execution function
*/
void Executor::execute(const std::bitset<16>& instr) {
    int opcode = (int) (instr >> 12).to_ulong();
    switch (opcode) {
        case 0:
            exec_opcode_zero(instr);
            break;
        case 1:
            exec_jump(instr);
            break;
        default:
            std::cout << "Unimplemented opcode for " << std::hex << instr.to_ulong() << std::endl;
            machine->set_exit_flag();
            break;
    }
}

/*
    Function that decides the correct way to execute an instruction starting with
    x0
*/
void Executor::exec_opcode_zero(const std::bitset<16>& instr) {
    std::string three_lsb = bytes_to_str(instr, 0, 2);
    if (three_lsb == "0E0") exec_clear_screen(instr);
    else if (three_lsb == "0EE") exec_ret_from_subroutine(instr);
    else if (three_lsb == "0FD") exec_exit(instr);
    else if (three_lsb == "000") machine->set_exit_flag(); //probably executing arbitrary memory... abort!
    else exec_subroutine(instr);
}

/*
    Format: 0x0nnn
    ASM: SYS addr
    Desc: Jump to machine code routine (ignored by most compilers)
*/
void Executor::exec_subroutine(const std::bitset<16>& instr) {
    std::cout << "hello from exec subroutine!" << std::endl;
    machine->pc_to_next_instruction();
}

/*
    Format: 0x00E0
    ASM: CLS
    Desc: Clear the graphics display
*/
void Executor::exec_clear_screen(const std::bitset<16>& instr) {
    std::cout << "hello from clear screen!" << std::endl;
    machine->pc_to_next_instruction();
}

/*
    Format: 0x00EE
    ASM: RET
    Desc: Return from subroutine
*/
void Executor::exec_ret_from_subroutine(const std::bitset<16>& instr) {
    std::cout << "hello from ret!" << std::endl;
    machine->pc_to_next_instruction();
}

/*
    Format: 0x00FD
    ASM: EXIT
    Desc: Super Chip-48 instruction that exits program
*/
void Executor::exec_exit(const std::bitset<16>& instr){
    std::cout << "hello from exit!" << std::endl;
    machine->set_exit_flag();
}

void Executor::exec_jump(const std::bitset<16>& instr){
    std::cout << "hello from jump!" << std::endl;
    int addr = bytes_to_int(instr, 0, 2);
    machine->set_pc(addr);
}