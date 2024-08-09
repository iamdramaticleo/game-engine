#pragma once

namespace core::gl
{
    class Commands
    {
    public:
        static void clear(float r, float g, float b);
        static void clear(uint32_t flags);

        static void draw_arrays(uint32_t   primitive, int32_t count);
        static void draw_elements(uint32_t primitive, int32_t count);

    private:
        Commands() = delete;
    };
}