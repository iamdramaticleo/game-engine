#include "platform.hpp"

namespace win32
{
    void Platform::init()
    {
        if (!glfwInit())
        {
            std::exit(EXIT_FAILURE);
        }
    }

    void Platform::release()
    {
        glfwTerminate();
    }

    void Platform::update() const
    {
        glfwPollEvents();
    }
}
