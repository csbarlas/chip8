#include <iostream>
#include <fstream>
#include <boost/dynamic_bitset.hpp>
#include "ROM.hpp"
#include <bitset>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <stdexcept>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

ROM::ROM(std::string path) {
    //Member init
    seekPosition = 0;

    rom_path = path;
    open_and_size_rom();
    rom_disk_to_mem();
    close_file();
}

void ROM::open_and_size_rom() {
    streampos start, end;

    cout << "Reading ROM " << rom_path << " ..." << endl;
    file.open(rom_path, ios::in | ios::binary);

    if(file.fail()) {
        cout << "Failed to open ROM " << rom_path << endl;
        throw std::runtime_error("Could not open file.");
    }
    else if (file.good()) file_did_open = true;

    start = file.tellg();
    file.seekg(0, ios::end);
    end = file.tellg();

    rom_size = end - start;
    cout << "ROM size is: " << std::dec << rom_size << " bytes." << endl;
    calculate_rom_addr_max_size();
    file.seekg(0, ios::beg);
}

void ROM::rom_disk_to_mem() {
    char temp_store[rom_size];

    //rom_binary.resize(rom_size * 8);
    data.resize(rom_size);

    file.read(temp_store, rom_size);

    //0th bit of 0th btyte in char arr = N-1 bit in bitset
    int bitpos = (rom_size * 8) - 1;

    //i = which byte
    for(int i = 0; i < rom_size; i++)
    {
        bitset<8> b(temp_store[i]);
        // j = bit in byte
        for(int j = 0; j < 8; j++) {
            if(b.test(8 - j - 1)) data.at(i).set(8 - j - 1);
            bitpos -= 1;
        }
    }
}

void ROM::close_file() {
    if(file_did_open) { 
        file.close();
        cout << "ROM reading complete." << endl;
    }
}

std::bitset<8> ROM::get_byte(int byte) {
    return data.at(byte);
}

int ROM::size() {
    return rom_size;
}

void ROM::print_rom() {
    calculate_print_rows();

    cout << "ROM contents: " << endl;
    for(int row = 0; row < print_rows; row++) {
        for(int col = 0; col < PRINT_COLS - 1; col++) {
            print_data_table_entry(row, col);
            cout << " | ";
        }
        print_data_table_entry(row, PRINT_COLS - 1);
        cout << endl;
    }
}

void ROM::print_data_table_entry(int row, int col) {
    int entry = row + (col * print_rows);
    if(entry < rom_size) {
        std::cout << std::setfill('0') << std::setw(rom_addr_max_size) << uppercase << std::hex << entry << ": " << setfill('0') << setw(2) << uppercase << hex << data[entry].to_ulong();
    } else {
        std::cout << std::setfill('0') << std::setw(rom_addr_max_size) << uppercase << std::hex << entry << ": XX";
    }
}

void ROM::calculate_rom_addr_max_size() {
    rom_addr_max_size = (int) ceil(log(rom_size) / log(16));
}

void ROM::calculate_print_rows() {
    print_rows = ceil((double)rom_size / PRINT_COLS);
}

std::string ROM::to_string() {
    std::string str;

    for (auto byte : data) {
        str.append(long_to_hex(byte.to_ulong()));
    }

    cout << str << endl;
    return str;
}

// Source: https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
std::string ROM::long_to_hex(ulong value) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << value;
    return stream.str();
}