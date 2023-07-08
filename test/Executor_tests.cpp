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