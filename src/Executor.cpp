#include <string>
#include <sstream>
#include <iomanip>

#include "Executor.hpp"
#include "Machine.hpp"

Executor::Executor(const Machine& m) : machine(m) {
}

void Executor::execute(const std::bitset<16>& instr) {
    int opcode = (int) (instr >> 12).to_ulong();
    switch (opcode) {
        case 0:
            exec_opcode_zero(instr);
            break;
        default:
            //error
            break;
    }
}

void Executor::exec_opcode_zero(const std::bitset<16>& instr) {
    std::string three_lsb = bytes_to_str(instr, 0, 2);
    if (three_lsb == "0E0") exec_clear_screen(instr);
    else if (three_lsb == "0EE") exec_ret_from_subroutine(instr);
    else exec_subroutine(instr);
}

void Executor::exec_subroutine(const std::bitset<16>& instr) {
    std::cout << "hello from exec subroutine!" << std::endl;
}

void Executor::exec_clear_screen(const std::bitset<16>& instr) {
    std::cout << "hello from clear screen!" << std::endl;
}

std::string Executor::bytes_to_str(const std::bitset<16>& instr, int from, int to) const {
    std::stringstream stream;

    int start_pos = (3 - to) * 4;
    int ending_pos = 15 - (4 * from);
    std::string temp = instr.to_string();
    temp = temp.substr(start_pos, ending_pos + 1);
    stream << std::setfill('0') << std::setw((to - from) + 1) << std::uppercase << std::hex << stoi(temp, nullptr, 2);
    return stream.str();
}