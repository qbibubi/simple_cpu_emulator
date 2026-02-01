#include "../include/compiler.hh"

#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <iostream>

namespace {
    /**
     * @brief Tokenizes an assembly file line
     *
     * It seems like this could be improved a lot. I have not measured std::regex yet but I have heard that it is not the fastest solution. This is a proof of concept for now though.
     */
    [[nodiscard]] 
    std::vector<std::string>
    tokenize_assembly_line(std::string const& line) {
        auto const regex = std::regex{ R"([\s|,]+)" };

        std::sregex_token_iterator it { 
            line.begin(), 
            line.end(), 
            regex, 
            -1
        };

        std::vector<std::string> tokenized_line { it, {} };

        tokenized_line.erase(
            std::remove_if(
                tokenized_line.begin(),
                tokenized_line.end(),
                [](std::string const& remaining) {
                    return remaining.size() == 0;
                }
            ),
            tokenized_line.end()
        );

        return tokenized_line;
    }

    [[nodiscard]] cpu::opcode_t parse_opcode(std::string const& token){
        if (!token.compare("mov")) { return cpu::opcode_t::mov; } 
        if (!token.compare("add")) { return cpu::opcode_t::add; }
        if (!token.compare("sub")) { return cpu::opcode_t::sub; }
        if (!token.compare("mul")) { return cpu::opcode_t::mul; }
        if (!token.compare("div")) { return cpu::opcode_t::div; } 
    }

    [[nodiscard]] std::variant<cpu::register_t, std::uint16_t> parse_operand(std::string const& token){
        if (!token.compare("ax")) { return cpu::register_t::ax; } else 
        if (!token.compare("bx")) { return cpu::register_t::bx; } else
        if (!token.compare("cx")) { return cpu::register_t::cx; } else
        if (!token.compare("dx")) { return cpu::register_t::dx; } 
        else { 
            return static_cast<std::uint16_t>(std::stoi(token));
        }
    }

} // namespace

namespace compiler {
    [[nodiscard]] 
    std::vector<cpu::instruction_t> 
    parse_input(std::filesystem::path const& input_path) {
        bool const input_exists = std::filesystem::exists(input_path);
        if (!input_exists) {
            return {};
        }

        std::ifstream input_file(input_path);
        
        bool const input_file_open = input_file.is_open();
        if (!input_file_open) {
            return {};
        }

        std::vector<cpu::instruction_t> instructions;
        std::string line;

        while(std::getline(input_file, line)) {
            auto const tokens = tokenize_assembly_line(line);

            cpu::instruction_t instruction;

            for (std::size_t operand_position = 0; operand_position < tokens.size(); ++operand_position) {
                auto const& token = tokens[operand_position];

                switch (operand_position) {
                    case 0: instruction.opcode = parse_opcode(token); break;
                    case 1: instruction.first_operand = parse_operand(token); break;
                    case 2: instruction.second_operand = parse_operand(token); break;
                }
            }

            instructions.push_back(instruction);
        }

        return instructions; 
    }

    void test(std::filesystem::path const& input_path){
        uintmax_t const input_file_size = std::filesystem::file_size(input_path);
        if (!input_file_size) {
            // std::cout << "[error]: binary file size is 0" << std::endl;
            // return 1;
        }

        std::ifstream input_file(input_path, std::ios::binary);
        
        bool const input_file_open = input_file.is_open();
        if (!input_file_open) {
            // std::cout << "[error]: binary file failed to open" << std::endl;
            // return 1;
        }
        
        std::vector<std::uint8_t> input_data(input_file_size);
        std::for_each(std::istreambuf_iterator<char>(input_file),
                      std::istreambuf_iterator<char>(),
                      [&input_data](char const c){
                        input_data.push_back(c);
                      });

        std::vector<cpu::instruction_t> instructions;
    }
} // namespace compiler

