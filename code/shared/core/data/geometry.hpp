#pragma once

namespace core::data
{
    template <typename vertex_t> struct geometry
    {
        std::vector<vertex_t> vertices;
        std::vector<uint32_t> indices;
    };
}