#pragma once
#include <cstdint>

namespace cpu {
    enum class opcode_t : std::uint8_t {
        add,
        sub,
        mul,
        div,
        mov
    };

    enum class register_t : std::uint16_t {
        ax,
        bx,
        cx,
        dx
    };

    void handle_instruction(opcode_t const opcode);
} // namespace cpu
