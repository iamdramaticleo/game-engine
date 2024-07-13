#include "functions.hpp"

namespace gl
{
    void Functions::load()
    {
        if (gladLoadGL() == 0)
        {
            std::exit(EXIT_FAILURE);
        }
    }
}
