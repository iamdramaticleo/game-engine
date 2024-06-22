#include "window.hpp"

namespace glfw
{
    void Window::create(const base::window_config& config)
    {
            _handle = glfwCreateWindow(config.size.width, config.size.height, config.title.c_str(), nullptr);
        if (_handle)
        {
            std::exit(EXIT_FAILURE);
        }
    }

    void Window::destroy()
    {
        glfwDestroyWindow(_handle);
    }

    void Window::activate() const
    {
        glfwMakeContextCurrent(_handle);
    }

    void Window::update() const
    {
        glfwSwapBuffers(_handle);
    }

    std::any Window::handle() const
    {
        return glfwGetWin32Window(_handle);
    }
}
