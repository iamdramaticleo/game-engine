#include "window.hpp"
#include "window_instance.hpp"

namespace win32
{
    void Window::create(const window_config& config)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::exit(EXIT_FAILURE);
        }
            _handle =  glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr);
        if (_handle == nullptr)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwSetCloseCallback(_handle, []
        {
            WindowInstance::instance().close();
        });

        glfwMakeContextCurrent(_handle);
    }

    void Window::destroy()
    {
        glfwDestroyWindow(_handle);
        glfwTerminate();
    }

    void Window::update() const
    {
        glfwSwapBuffers(_handle);
        glfwPollEvents();
    }

    std::any Window::handle() const
    {
        return glfwGetWin32Window(_handle);
    }
}
