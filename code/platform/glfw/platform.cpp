#include "platform.hpp"

namespace glfw
{
    void Platform::init()
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_SAMPLES,    4);
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
