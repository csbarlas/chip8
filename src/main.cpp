#include <iostream>
#include <bitset>

#include "Machine.hpp"
#include "ROM.hpp"
#include "Executor.hpp"

Machine machine;

int main(int argc, char *argv[]) {
    if(argc == 1) {
        // ROM test_rom("../roms/pong.rom");
        // machine.load_rom(test_rom);
        machine.pc_to_next_instruction();
    } else if (argc == 2) {
        ROM test_rom(argv[1]);
        machine.load_rom(test_rom);
    } else {
        throw std::runtime_error("Unsupported number of command line arguments given.");
    }

    machine.run();
}
