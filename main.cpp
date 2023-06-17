#include <iostream>

#include "Machine.hpp"
#include "ROM.hpp"

Machine machine;

int main(int, char**) {
    //machine.print_state();
    ROM test_rom("roms/pong.rom");
    test_rom.print_rom();
}
