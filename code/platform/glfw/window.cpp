#include "window.hpp"
#include "window_callbacks.hpp"

namespace glfw
{
    void Window::create(const base::window_config& config)
    {
            _handle =  glfwCreateWindow(config.size.width, config.size.height, config.title.c_str(), nullptr);
        if (_handle == nullptr)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwSetCloseCallback(_handle, core::WindowCallbacks::on_close);
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
