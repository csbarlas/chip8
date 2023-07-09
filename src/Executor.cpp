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
    temp = temp.substr(start_pos, (to - from + 1) * 4);
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
        case 2:
            exec_call(instr);
            break;
        case 3:
            exec_skip_equal_byte(instr);
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
    machine->advance_pc();
}

/*
    Format: 0x00E0
    ASM: CLS
    Desc: Clear the graphics display
*/
void Executor::exec_clear_screen(const std::bitset<16>& instr) {
    std::cout << "hello from clear screen!" << std::endl;
    machine->advance_pc();
}

/*
    Format: 0x00EE
    ASM: RET
    Desc: Return from subroutine
*/
void Executor::exec_ret_from_subroutine(const std::bitset<16>& instr) {
    std::cout << "hello from ret!" << std::endl;
    machine->advance_pc();
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


/*
    Format: 0x1nnn
    ASM: JP addr
    Desc: Sets PC to nnn
*/
void Executor::exec_jump(const std::bitset<16>& instr){
    std::cout << "hello from jump!" << std::endl;
    int addr = bytes_to_int(instr, 0, 2);
    machine->set_pc(addr);
}

/*
    Format: 2nnn
    ASM: CALL addr
    Desc: Sets pc to nnn and saves current PC on the stack
*/
void Executor::exec_call(const std::bitset<16>& instr) {
    auto current_pc = machine->get_pc();
    machine->push_to_stack(current_pc);
    int addr_int = bytes_to_int(instr, 0, 2);
    machine->set_pc(addr_int);
}

/*
    Format: 3xkk
    ASM: SE Vx, byte
    Desc: Skip next instruction if Vx = kk
*/
void Executor::exec_skip_equal_byte(const std::bitset<16>& instr) {
    int reg_index = bytes_to_int(instr, 2, 2);
    int reg_val = (int) machine->read_register(reg_index).to_ulong();
    int byte_val = bytes_to_int(instr, 0, 1);
    if(byte_val == reg_val) {
        //skip next instr
        machine->advance_pc();
    }
    //always advance at least once regardless of comparison
    machine->advance_pc();
}
