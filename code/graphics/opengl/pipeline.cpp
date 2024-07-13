#include "pipeline.hpp"

namespace gl
{
    void Pipeline::enable(const uint32_t flag)
    {
        glEnable(flag);
    }
}
