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
        void exec_jump(const std::bitset<16>& instr);
        void exec_call(const std::bitset<16>& instr);
        void exec_skip_equal_byte(const std::bitset<16>& instr);
        void exec_skip_not_equal_byte(const std::bitset<16>& instr);
        void exec_skip_equal_reg(const std::bitset<16>& instr);
        void exec_load_imm(const std::bitset<16>& instr);
        void exec_add_imm(const std::bitset<16>& instr);
        void exec_opcode_eight(const std::bitset<16>& instr);
        void exec_load_regs(const std::bitset<16>& instr);
        void exec_bitwise_or(const std::bitset<16>& instr);
        void exec_bitwise_and(const std::bitset<16>& instr);
        void exec_bitwise_xor(const std::bitset<16>& instr);
        void exec_add_regs(const std::bitset<16>& instr);
        void exec_sub_regs(const std::bitset<16>& instr);
        void exec_shift_r(const std::bitset<16>& instr);
        void exec_sub_regs_flipped(const std::bitset<16>& instr);
        void exec_shift_l(const std::bitset<16>& instr);
        void exec_skip_next_instr(const std::bitset<16>& instr);
        void exec_load_addr(const std::bitset<16>& instr);
        void exec_jump_reg_offset(const std::bitset<16>& instr);
        void exec_random(const std::bitset<16>& instr);
        void exec_draw(const std::bitset<16>& instr);
        void exec_e_opcodes(const std::bitset<16>& instr);
        void exec_skip_key_pressed(const std::bitset<16>& instr);
        void exec_skip_key_not_pressed(const std::bitset<16>& instr);
        void exec_f_opcodes(const std::bitset<16>& instr);
        void exec_load_dt_reg(const std::bitset<16>& instr);
        void exec_wait_key_press(const std::bitset<16>& instr);
        void exec_set_dt(const std::bitset<16>& instr);
        void exec_set_st(const std::bitset<16>& instr);
        void exec_add_vi(const std::bitset<16>& instr);

        int bytes_to_int(const std::bitset<16>& instr, int from, int to);
        int byte_to_int(const std::bitset<16>& instr, int byte);
        std::string bytes_to_str(const std::bitset<16>& instr, int from, int to) const; 
};