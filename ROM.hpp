#pragma once
#include <string>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>

#define PRINT_COLS 8


class ROM {
    public:
        ROM(std::string path);
        std::bitset<8> get_byte(int byte);
        int size();
        void print_rom();

    private:
        std::vector<std::bitset<8>> data;
        std::string rom_path;
        int rom_size;
        std::ifstream file;
        bool file_did_open;
        int seekPosition;
        int rom_addr_max_size;
        int print_rows;

        void open_and_size_rom();
        void rom_disk_to_mem();
        void close_file();
        void print_data_table_entry(int row, int col);
        void calculate_rom_addr_max_size();
        void calculate_print_rows();
};