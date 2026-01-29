#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <filesystem>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "[error]: wrong argument count" << std::endl;
        return 1;
    }

    std::string const binary_filename = std::string(argv[1]);
    if (binary_filename.empty()) {
        std::cout << "[error]: binary file input is invalid" << std::endl;
        return 1;
    }

    std::filesystem::path current_working_dir = std::filesystem::current_path();
    std::filesystem::path binary_path = current_working_dir / binary_filename;
    
    bool const binary_exists = std::filesystem::exists(binary_path);
    if (!binary_exists) {
        std::cout << "[error]: binary file does not exist" << std::endl;
        return 1;
    }

    uintmax_t const binary_file_size = std::filesystem::file_size(binary_path);
    if (!binary_file_size) {
        std::cout << "[error]: binary file size is 0" << std::endl;
        return 1;
    }

    std::ifstream binary_file(binary_path, std::ios::binary);
    
    bool const binary_file_open = binary_file.is_open();
    if (!binary_file_open) {
        std::cout << "[error]: binary file failed to open" << std::endl;
        return 1;
    }
    
    std::vector<std::uint8_t> binary_data(binary_file_size);
    std::for_each(std::istreambuf_iterator<char>(binary_file),
                  std::istreambuf_iterator<char>(),
                  [&binary_data](char const c){
                    binary_data.push_back(c);
                  });
    
    for (std::size_t i = 0; i < binary_data.size(); ++i) {
        // read only data of the binary
        // here all the parsing will be done however this has to be done
        // with indexed for loop to access further positions for proper
        // instruction parsing
        // Parsing sybnta
    }

    return 0;
};
