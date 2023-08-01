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

int Executor::byte_to_int(const std::bitset<16>& instr, int byte) {
    return bytes_to_int(instr, byte, byte);
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
        case 4:
            exec_skip_not_equal_byte(instr);
            break;
        case 5:
            exec_skip_equal_reg(instr);
            break;
        case 6:
            exec_load_imm(instr);
            break;
        case 7:
            exec_add_imm(instr);
            break;
        case 8:
            exec_opcode_eight(instr);
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

/*
    Format: 4xkk
    ASM: SNE Vx, byte
    Desc: Skip next instruction if Vx != kk
*/
void Executor::exec_skip_not_equal_byte(const std::bitset<16>& instr) {
    int reg_index = bytes_to_int(instr, 2, 2);
    int reg_val = (int) machine->read_register(reg_index).to_ulong();
    int byte_val = bytes_to_int(instr, 0, 1);
    if(byte_val != reg_val) {
        //skip next instr
        machine->advance_pc();
    }
    //always advance at least once regardless of comparison
    machine->advance_pc();
}

/*
    Format: 5xy0
    ASM: SE Vx, Vy
    Desc: Skip next instruction if Vx = Vy
*/
void Executor::exec_skip_equal_reg(const std::bitset<16>& instr) {
    int reg1_index = bytes_to_int(instr, 2, 2);
    int reg2_index = bytes_to_int(instr, 1, 1);

    int reg1_val = machine->read_register(reg1_index).to_ulong();
    int reg2_val = machine->read_register(reg2_index).to_ulong();

    if(reg1_val == reg2_val) {
        machine->advance_pc();
    }

    machine->advance_pc();
}

/*
    Format: 6xkk
    ASM: LD Vx, byte (kk)
    Desc: Load immediate byte into Vx
*/
void Executor::exec_load_imm(const std::bitset<16>& instr) {
    int imm_val = bytes_to_int(instr, 0, 1);
    int reg_index = bytes_to_int(instr, 2, 2);
    machine->set_register(reg_index, imm_val);
    machine->advance_pc();
}

/*
    Format: 7xkk
    ASM: ADD Vx, byte (kk)
    Desc: Vx = Vx + byte (kk)
*/
void Executor::exec_add_imm(const std::bitset<16>& instr) {
    int imm_val = bytes_to_int(instr, 0, 1);
    int reg_index = bytes_to_int(instr, 2, 2);
    int reg_val = machine->read_register(reg_index).to_ulong();
    int result = reg_val + imm_val;
    machine->set_register(reg_index, result);
    machine->advance_pc();
}

/*
    Figures out which specific exec function to call based on the 
    last byte of the instr "selector"
*/
void Executor::exec_opcode_eight(const std::bitset<16>& instr) {
    int selector = bytes_to_int(instr, 0, 0);
    switch (selector) {
        case 0:
            exec_load_regs(instr);
            break;
        case 1:
            exec_bitwise_or(instr);
            break;
        case 2:
            exec_bitwise_and(instr);
            break;
        case 3:
            exec_bitwise_xor(instr);
            break;
        case 4:
            exec_add_regs(instr);
            break;
        case 5:
            exec_sub_regs(instr);
            break;
        case 6:
            exec_shift_r(instr);
            break;
        case 7:
            exec_sub_regs_flipped(instr);
            break;
        case 14:
            exec_shift_l(instr);
            break;
        default:
            std::cout << "error!" << std::endl;
    }
}

/*
    Format: 8xy0
    ASM: LD Vx, Vy
    Desc: Vx = Vy
*/
void Executor::exec_load_regs(const std::bitset<16>& instr) {
    int source_index = byte_to_int(instr, 2);
    int dest_index = byte_to_int(instr, 1);
    int source_val = machine->read_register(source_index).to_ulong();
    machine->set_register(dest_index, source_val);
    machine->advance_pc();
}

/*
    Format: 8xy1
    ASM: OR Vx, Vy
    Desc: Vx = Vx | Vy (bitwise OR)
*/
void Executor::exec_bitwise_or(const std::bitset<16>& instr){
    int dest_index = byte_to_int(instr, 2);
    int src_index = byte_to_int(instr, 1);
    auto dest_val = machine->read_register(dest_index);
    auto src_val = machine->read_register(src_index);
    auto result = dest_val | src_val;
    machine->set_register(dest_index, result);
    machine->advance_pc();
}

/*
    Format: 8xy2
    ASM: AND Vx, Vy
    Desc: Vx = Vx & Vy (bitwise AND)
*/
void Executor::exec_bitwise_and(const std::bitset<16>& instr){
    int vx = byte_to_int(instr, 2);
    int vy = byte_to_int(instr, 1);
    auto vx_val = machine->read_register(vx);
    auto vy_val = machine->read_register(vy);
    auto result = vx_val & vy_val;
    machine->set_register(vx, result);
    machine->advance_pc();
}

/*
    Format: 8xy3
    ASM: XOR Vx, Vy
    Desc: Vx = Vx XOR Vy
*/
void Executor::exec_bitwise_xor(const std::bitset<16>& instr){
    int vx = byte_to_int(instr, 2);
    int vy = byte_to_int(instr, 1);
    auto vx_val = machine->read_register(vx);
    auto vy_val = machine->read_register(vy);
    auto result = vx_val ^ vy_val;
    machine->set_register(vx, result);
    machine->advance_pc();
}

/*
    Format: 8xy4
    ASM: ADD Vx, Vy
    Desc: Vx = Vx + Vy and VF gets set if there is a carry bit
*/
void Executor::exec_add_regs(const std::bitset<16>& instr){
    int vx = byte_to_int(instr, 2);
    int vy = byte_to_int(instr, 1);
    int vx_val = machine->read_register(vx).to_ulong();
    int vy_val = machine->read_register(vy).to_ulong();
    std::bitset<BYTE_SIZE + 1> result(vx_val + vy_val);
    if (result.test(8)) {
        machine->set_register(15, 1);
    } else {
        machine->set_register(15, 0);
    }
    std::bitset<BYTE_SIZE + 1> mask(255);
    result = result & mask;
    machine->set_register(vx, result.to_ulong());
    machine->advance_pc();
}

/*
    Format: 8xy5
    ASM: SUB Vx, Vy
    Desc: Vx = Vx - Vy and VF = NOT borrow
*/
void Executor::exec_sub_regs(const std::bitset<16>& instr) {
    int vx = byte_to_int(instr, 2);
    int vy = byte_to_int(instr, 1);
    int vx_val = machine->read_register(vx).to_ulong();
    int vy_val = machine->read_register(vy).to_ulong();
    if (vx_val > vy_val) {
        machine->set_register(15, 1);
    } else {
        machine->set_register(15, 0);
    }
    machine->set_register(vx, vx_val - vy_val);
    machine->advance_pc();
}

/*
    Format: 8xy6
    ASM: SHR Vx (Vy not used?)
    Desc: Shift Vx right by one, set VF to LSb
*/
void Executor::exec_shift_r(const std::bitset<16>& instr) {
    int vx = byte_to_int(instr, 2);
    auto vx_bitset = machine->read_register(vx);
    if (vx_bitset.test(0)) {
        machine->set_register(15, 1);
    } else {
        machine->set_register(15, 0);
    }
    vx_bitset = vx_bitset >> 1;
    machine->set_register(vx, vx_bitset);
    machine->advance_pc();
}

/*
    Format: 8xy7
    ASM: SUBN Vx, Vy
    Desc: Vx = Vy - Vx and Vf = NOT borrow
*/
void Executor::exec_sub_regs_flipped(const std::bitset<16>& instr) {
    int vx = byte_to_int(instr, 2);
    int vy = byte_to_int(instr, 1);
    int vx_val = machine->read_register(vx).to_ulong();
    int vy_val = machine->read_register(vy).to_ulong();
    if (vy_val > vx_val) {
        machine->set_register(15, 1);
    } else {
        machine->set_register(15, 0);
    }
    machine->set_register(vx, vy_val - vx_val);
    machine->advance_pc();
}


/*
    Format: 8xyE
    ASM: SHL Vx (Vy not used)
    Desc: Vx = Vx SHL 1, VF = MSb
*/
void Executor::exec_shift_l(const std::bitset<16>& instr) {
    int vx = byte_to_int(instr, 2);
    auto vx_bitset = machine->read_register(vx);
    if (vx_bitset.test(7)) {
        machine->set_register(15, 1);
    } else {
        machine->set_register(15, 0);
    }
    vx_bitset = vx_bitset << 1;
    machine->set_register(vx, vx_bitset);
    machine->advance_pc();
}