#include "window_callbacks.hpp"
#include "window_instance.hpp"

namespace core
{
    void WindowCallbacks::on_close()
    {
        WindowInstance::instance().close();
    }
}
