#pragma once
#include <bitset>
#include <functional>
#include <array>

#define NUM_EXECUTE_FUNCS 10
#define NUM_ZERO_OPCODES 3

class Machine;

class Executor {
    public:
        Executor(Machine *m);
        void execute(const std::bitset<16>& instr);
    private:
        Machine *machine;
        void exec_opcode_zero(const std::bitset<16>& instr);
        void exec_subroutine(const std::bitset<16>& instr);
        void exec_clear_screen(const std::bitset<16>& instr);
        void exec_ret_from_subroutine(const std::bitset<16>& instr);
        void exec_exit(const std::bitset<16>& instr);
        std::string bytes_to_str(const std::bitset<16>& instr, int from, int to) const; 
};