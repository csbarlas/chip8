#include "gtest/gtest.h"
#include "ROM.hpp"
#include "Machine.hpp"
#include "bitset"

TEST(ROMTest, clear_only_load_test) {
    ROM *rom = new ROM("../test/roms/clearonly.rom");
    EXPECT_EQ(rom->to_string(), "00E0");
}

TEST(ROMTest, ibm_logo_load_test) {
    ROM *rom = new ROM("../test/roms/IBMlogo.ch8");
    const char *text = "00E0A22A600C6108D01F7009A239D01FA2487008D01F7004A257D01F7008A266D01F7008A275D01F1228FF00FF003C003C003C003C00FF00FFFF00FF0038003F003F003800FF00FF8000E000E00080008000E000E00080F800FC003E003F003B003900F800F8030007000F00BF00FB00F300E30043E000E0008000800080008000E000E0";
    EXPECT_EQ(rom->to_string(), text);
}