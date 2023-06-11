#include <iostream>
#include <fstream>
#include <boost/dynamic_bitset.hpp>
#include "ROM.hpp"

using namespace std;

ROM::ROM(std::string path) {
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
        return;
    }
    else if (file.good()) file_did_open = true;

    start = file.tellg();
    file.seekg(0, ios::end);
    end = file.tellg();

    rom_size = end - start;
    cout << "ROM size is: " << rom_size << " bytes." << endl;
    file.seekg(0, ios::beg);
}

void ROM::rom_disk_to_mem() {
    char temp_store[rom_size];

    rom_binary.resize(rom_size * 8);

    file.read(temp_store, rom_size);

    //0th bit of 0th btyte in char arr = N-1 bit in bitset
    int bitpos = (rom_size * 8) - 1;

    //i = which byte
    for(int i = 0; i < rom_size; i++)
    {
        bitset<8> b(temp_store[i]);
        // j = bit in byte
        for(int j = 0; j < 8; j++) {
            if(b.test(8 - j - 1)) rom_binary.set(bitpos);
            bitpos -= 1;
        }
    }

    cout << "ROM Binary:" << endl;
    cout << rom_binary << endl;
}

void ROM::close_file() {
    if(file_did_open) file.close();
}