#include <iostream>
#include <bitset>

#include "Machine.hpp"
#include "ROM.hpp"
#include "Executor.hpp"

Machine machine;

int main(int, char**) {
    // machine.print_state();
    ROM test_rom("../roms/pong.rom");
    // test_rom.print_rom();
    machine.load_rom(test_rom);
    // machine.print_state();
 
    std::bitset<16> b("0000000011101110");
    Executor e(machine);
    e.execute(b);
}
