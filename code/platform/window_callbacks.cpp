#include "window_callbacks.hpp"
#include "window_instance.hpp"

namespace core
{
    void WindowCallbacks::on_size(const int32_t width, const int32_t height)
    {
        WindowInstance::instance().resize({ width, height });
    }

    void WindowCallbacks::on_close()
    {
        WindowInstance::instance().close();
    }
}
