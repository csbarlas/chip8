#include "gtest/gtest.h"
#include "Machine.hpp"

TEST(MachineTest, set_register) {
    Machine *m = new Machine();
    m->set_register(0, 0x200);
    EXPECT_EQ(0x200, m->read_register(0).to_ulong());
}