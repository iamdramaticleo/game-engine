#include "pipeline.hpp"

namespace core::gl
{
    void Pipeline::enable(const uint32_t flag)
    {
        glEnable(flag);
    }
}
