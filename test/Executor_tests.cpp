#include "gtest/gtest.h"
#include "Executor.hpp"
#include "Machine.hpp"
#include "ROM.hpp"

TEST(ExecutorTest, jump_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/jump_test_simple.rom");
    m->load_rom(rom);
    m->run();
    EXPECT_EQ("001F", m->pc_to_string());
}

TEST(ExecutorTest, call_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/call_test_simple.rom");
    m->load_rom(rom);
    m->run();
    EXPECT_EQ("0300", m->pc_to_string());
    EXPECT_EQ(1, m->get_sp());
    auto stack = m->get_stack();
    EXPECT_EQ(std::stoi("0200", nullptr, 16), stack[0].to_ulong());
}

TEST(ExecutorTest, skip_equal_false_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_equal_test_simple.rom");
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, skip_equal_true_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_equal_test_simple.rom");
    m->set_register(4, 16);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x204, m->get_pc().to_ulong());
}

TEST(ExecutorTest, skip_not_equal_true_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_not_equal_test_simple.rom");
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x204, m->get_pc().to_ulong());
}

TEST(ExecutorTest, skip_not_equal_false_test_simple) {
    Machine *m = new Machine();
    m->set_register(4, 16);
    ROM rom("../test/roms/skip_not_equal_test_simple.rom");
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, skip_equal_reg_true_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_equal_test_reg_simple.rom");
    m->set_register(7, 7);
    m->set_register(8, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x204, m->get_pc().to_ulong());
}

TEST(ExecutorTest, skip_equal_reg_false_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_equal_test_reg_simple.rom");
    m->set_register(7, 1);
    m->set_register(8, 2);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, load_imm_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/load_imm_test_simple.rom");
    m->set_register(5, 20);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(16, m->read_register(5).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, add_imm_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/add_imm_test_simple.rom");
    m->set_register(10, 5);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(6, m->read_register(10).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, load_regs_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/load_regs_test_simple.rom");
    m->set_register(1, 7);
    m->set_register(15, 9);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(7, m->read_register(15).to_ulong());
    EXPECT_EQ(7, m->read_register(1).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, bitwise_or_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/bitwise_or_test_simple.rom");
    m->set_register(15, 15); //0x0F
    m->set_register(1, 240); //0xF0
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(255, m->read_register(15).to_ulong());
    EXPECT_EQ(240, m->read_register(1).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, bitwise_and_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/bitwise_and_test_simple.rom");
    m->set_register(15, 15); //0x0F
    m->set_register(1, 240); //0xF0
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0, m->read_register(15).to_ulong());
    EXPECT_EQ(240, m->read_register(1).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, bitwise_xor_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/bitwise_xor_test_simple.rom");
    m->set_register(15, 15); //0x0F
    m->set_register(1, 240); //0xF0
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(255, m->read_register(15).to_ulong());
    EXPECT_EQ(240, m->read_register(1).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, add_regs_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/add_regs_test_simple.rom");
    m->set_register(1, 1);
    m->set_register(14, 2);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(3, m->read_register(14).to_ulong());
    EXPECT_EQ(1, m->read_register(1).to_ulong());
    EXPECT_EQ(0, m->read_register(15).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, subtract_regs_test_simple){
    Machine *m = new Machine();
    ROM rom("../test/roms/subtract_regs_test_simple.rom");
    m->set_register(15, 10);
    m->set_register(14, 14);
    m->set_register(1, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(7, m->read_register(14).to_ulong());
    EXPECT_EQ(7, m->read_register(1).to_ulong());
    EXPECT_EQ(1, m->read_register(15).to_ulong());
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
}

TEST(ExecutorTest, shift_r_test_simple_bit_out) {
    Machine *m = new Machine();
    ROM rom("../test/roms/shift_r_test_simple.rom");
    m->set_register(1, 7);
    m->set_register(15, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(3, m->read_register(1).to_ulong());
    EXPECT_EQ(1, m->read_register(15).to_ulong());
}

TEST(ExecutorTest, shift_r_test_simple_no_bit_out) {
    Machine *m = new Machine();
    ROM rom("../test/roms/shift_r_test_simple.rom");
    m->set_register(1, 6);
    m->set_register(15, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(3, m->read_register(1).to_ulong());
    EXPECT_EQ(0, m->read_register(15).to_ulong());
}

TEST(ExecutorTest, subn_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/subn_test_simple.rom");
    m->set_register(1, 6);
    m->set_register(7, 7);
    m->set_register(15, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(1, m->read_register(1).to_ulong());
    EXPECT_EQ(1, m->read_register(15).to_ulong());
}

TEST(ExecutorTest, shl_test_msb_set) {
    Machine *m = new Machine();
    ROM rom("../test/roms/shl_test_simple.rom");
    m->set_register(1, 128);
    m->set_register(15, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(0, m->read_register(1).to_ulong());
    EXPECT_EQ(1, m->read_register(15).to_ulong());
}

TEST(ExecutorTest, shl_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/shl_test_simple.rom");
    m->set_register(1, 4);
    m->set_register(15, 7);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(8, m->read_register(1).to_ulong());
    EXPECT_EQ(0, m->read_register(15).to_ulong());
}

TEST(ExecutorTest, skip_not_eq_test_true) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_not_eq_test_simple.rom");
    m->set_register(4, 1);
    m->set_register(5, 0);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x204, m->get_pc().to_ulong());
    EXPECT_EQ(1, m->read_register(4).to_ulong());
    EXPECT_EQ(0, m->read_register(5).to_ulong());
}

TEST(ExecutorTest, skip_not_eq_test_false) {
    Machine *m = new Machine();
    ROM rom("../test/roms/skip_not_eq_test_simple.rom");
    m->set_register(4, 1);
    m->set_register(5, 1);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(1, m->read_register(4).to_ulong());
    EXPECT_EQ(1, m->read_register(5).to_ulong());
}

TEST(ExecutorTest, load_addr_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/load_addr_test_simple.rom");
    m->load_rom(rom);
    EXPECT_EQ(0, m->get_vi().to_ulong());
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(0xFF, m->get_vi().to_ulong());
}

TEST(ExecutorTest, jump_reg_offset_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/jump_reg_offset_test_simple.rom");
    m->set_register(0, 255);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(255 + 10, m->get_pc().to_ulong());
    EXPECT_EQ(255, m->read_register(0).to_ulong());
}

/*
    Hang on... we can't possibly know what the random number is going to be
    Maybe come back and provide a seed?
*/
// TEST(ExecutorTest, random_test_simple) {
//     Machine *m = new Machine();
//     ROM rom("../test/roms/random_test_simple.rom");
//     m->set_register(13, 85);
//     m->load_rom(rom);
//     m->run();
//     EXPECT_EQ(0x202, m->get_pc().to_ulong());
//     EXPECT_EQ(255, m->read_register(0).to_ulong());
// }

TEST(ExecutorTest, load_dt_to_vx_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/load_dt_to_vx_test_simple.rom");
    m->set_dt(60);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(60, m->get_dt().to_ulong());
    EXPECT_EQ(60, m->read_register(10).to_ulong());
}

TEST(ExecutorTest, load_vx_to_dt_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/set_dt_reg_test_simple.rom");
    m->set_dt(60);
    m->set_register(3, 30);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(30, m->get_dt().to_ulong());
    EXPECT_EQ(30, m->read_register(3).to_ulong());
}

TEST(ExecutorTest, load_vx_to_st_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/set_st_reg_test_simple.rom");
    m->set_st(60);
    m->set_register(11, 30);
    m->load_rom(rom);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(30, m->get_st().to_ulong());
    EXPECT_EQ(30, m->read_register(11).to_ulong());
}

TEST(ExecutorTest, add_vi_test_simple) {
    Machine *m = new Machine();
    ROM rom("../test/roms/add_vi_test_simple.rom");
    m->load_rom(rom);
    m->set_vi(768);
    m->set_register(9, 16);
    m->run();
    EXPECT_EQ(0x202, m->get_pc().to_ulong());
    EXPECT_EQ(0x310, m->get_vi().to_ulong());
    EXPECT_EQ(16, m->read_register(9).to_ulong());
}