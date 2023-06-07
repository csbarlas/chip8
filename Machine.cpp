#include "Machine.hpp"
#include <iostream>
#include <cstddef>
#include <bitset>

Machine::Machine() {}

void Machine::print_state() {
    std::cout << "sp: " << std::bitset<8>(std::to_integer<int>(sp)) << std::endl;
}