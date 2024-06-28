#include "commands.hpp"

namespace gl
{
    void Commands::clear(const float r, const float g, const float b)
    {
        glClearColor(r, g, b, 1.0f);
    }

    void Commands::clear(const uint32_t flags)
    {
        glClear(flags);
    }

    void Commands::draw_arrays(const uint32_t primitive, const int32_t count)
    {
        glDrawArrays(primitive, 0, count);
    }
}