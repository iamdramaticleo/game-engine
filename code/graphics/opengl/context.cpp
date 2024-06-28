#include "context.hpp"
#include "macros.hpp"

namespace gl
{
    void Context::load()
    {
        if (gladLoadGL() == FALSE)
        {
            std::exit(-1);
        }
    }
}
