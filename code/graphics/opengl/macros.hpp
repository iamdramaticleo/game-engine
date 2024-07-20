#pragma once

namespace gl
{
    constexpr uint32_t shader_binary_format = 0x9551;

    constexpr uint32_t uniform_buffer       = 0x8A11;
    constexpr uint32_t array_buffer         = 0x8892;
    constexpr uint32_t element_array_buffer = 0x8893;

    constexpr uint32_t color_buffer_bit = 0x00004000;
    constexpr uint32_t depth_buffer_bit = 0x00000100;

    constexpr uint32_t static_draw = 0x88E4;

    constexpr uint32_t depth_test  = 0x0B71;
    constexpr uint32_t multisample = 0x809D;

    constexpr uint32_t type_float  = 0x1406;
    constexpr uint32_t type_uint   = 0x1405;

    constexpr uint32_t triangles   = 0x0004;
}