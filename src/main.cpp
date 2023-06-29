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
    machine.print_registers();

    std::cout << "Next instruction is: " << std::hex << machine.next_instruction().to_ulong() << std::endl;
    std::cout << "Next instruction is: " << std::hex << machine.next_instruction().to_ulong() << std::endl;
    std::cout << "Next instruction is: " << std::hex << machine.next_instruction().to_ulong() << std::endl;
}
