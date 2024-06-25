#pragma once

namespace gl
{
    class Commands
    {
    public:
        static void clear(float r, float g, float b);
        static void clear(uint32_t flags);

    private:
        Commands() = delete;
    };
}