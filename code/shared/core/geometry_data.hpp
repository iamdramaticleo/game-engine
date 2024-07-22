#pragma once

namespace core
{
    template <typename vertex_t> struct geometry_data
    {
        std::vector<vertex_t> vertices;
        std::vector<uint32_t> indices;
    };
}