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