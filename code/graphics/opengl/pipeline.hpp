#pragma once

namespace gl
{
    class Pipeline
    {
    public:
        static void enable(uint32_t flag);

    private:
        Pipeline() = delete;
    };
}