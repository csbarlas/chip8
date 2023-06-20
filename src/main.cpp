#include <iostream>

#include "Machine.hpp"
#include "ROM.hpp"

Machine machine;

int main(int, char**) {
    machine.print_state();
    ROM test_rom("roms/pong.rom");
    test_rom.print_rom();
    machine.load_rom(test_rom);
    machine.print_state();
}
