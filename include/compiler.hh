#pragma once
#include <filesystem>
#include <vector>

#include "../include/cpu.hh"

/**
 * 1) We will have two types of parsing:
 *      - Compiling from assembly source code to binary -> binary gets fed into the virtual machine
 *      - Parsing pure binary
 *
 * 2) Each line of source code file in non-binary form has to be read as text and all
 *    lines should only contain singular instruction. Otherwise we will be throwing errors.
 *    This way we are not caring about line endings such as semicolons.
 *
 * 3) Singular pass-through will generate a std::vector<std::uint8_t> as opcode representation of the
 *    source code which will then get fed into the virtual machine that will only process raw bytes
 *    basing on a predefined instruction set.
 */
namespace compiler {
    [[nodiscard]] std::vector<cpu::instruction_t> parse_input(std::filesystem::path const& input_path);
} // namespace compiler
