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