#include "gtest/gtest.h"
#include "Machine.hpp"

TEST(MachineTest, set_register_test) {
    Machine *m = new Machine();
    m->set_register(7, 128);
    EXPECT_EQ(128, m->read_register(7).to_ulong());
}