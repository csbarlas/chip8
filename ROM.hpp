#pragma once
#include <string>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>

class ROM {
    public:
        ROM(std::string path);

    private:
        boost::dynamic_bitset<> rom_binary;
        std::string rom_path;
        int rom_size;
        std::ifstream file;
        bool file_did_open;

        void open_and_size_rom();
        void rom_disk_to_mem();
        void close_file();
};