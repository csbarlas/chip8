#include <iostream>
#include <bitset>
#include <unistd.h>

#include "Machine.hpp"

Machine machine;

int main(int argc, char *argv[]) {
    if(argc == 1) {
        // ?
    } else if (argc == 2) {
        ROM test_rom(argv[1]);
        machine.load_rom(test_rom);
        machine.run();
    } else {
        throw std::runtime_error("Unsupported number of command line arguments given.");
    }
}
