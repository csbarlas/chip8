#include <iostream>
#include <bitset>

#include "Machine.hpp"
#include "ROM.hpp"
#include "Executor.hpp"
#include "Display.hpp"

Machine machine;

int main(int argc, char *argv[]) {
    if(argc == 1) {
        // ROM test_rom("../roms/pong.rom");
        // machine.load_rom(test_rom);
    } else if (argc == 2) {
        ROM test_rom(argv[1]);
        machine.load_rom(test_rom);
        machine.run();
    } else {
        throw std::runtime_error("Unsupported number of command line arguments given.");
    }
    //machine.print_registers();
}
