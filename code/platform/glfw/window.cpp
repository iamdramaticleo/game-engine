#include "window.hpp"
#include "window_callbacks.hpp"

namespace glfw
{
    void Window::create(const base::window_config& config)
    {
        _size   = config.size;
        _handle = glfwCreateWindow(_size.width, _size.height, config.title.c_str(), nullptr);

        if (_handle == nullptr)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwSetCloseCallback(_handle, core::WindowCallbacks::on_close);
        glfwSetSizeCallback(_handle,  core::WindowCallbacks::on_size);
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
