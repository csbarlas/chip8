#pragma once
#include <string>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>
#include <vector>

class ROM {
    public:
        ROM(std::string path);

    private:
        std::vector<std::bitset<8>> data;
        std::string rom_path;
        int rom_size;
        std::ifstream file;
        bool file_did_open;

        void open_and_size_rom();
        void rom_disk_to_mem();
        void close_file();
};