#include "window.hpp"

namespace win32
{
    void Window::create(const window_config& config)
    {
        _handle = glfwCreateWindow(config.size.width, config.size.height, config.title.c_str(), nullptr);

        if (_handle == nullptr)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwSetCloseCallback(_handle, []
        {
        });

        glfwMakeContextCurrent(_handle);
    }

    void Window::destroy()
    {
        glfwDestroyWindow(_handle);
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
