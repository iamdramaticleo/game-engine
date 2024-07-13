#include "platform_factory.hpp"
#include "window.hpp"

namespace win32
{
    std::unique_ptr<base::Window> PlatformFactory::create_window() const
    {
        return std::make_unique<Window>();
    }
}
