#include "platform_factory.hpp"
#include "platform.hpp"
#include "window.hpp"

namespace glfw
{
    std::unique_ptr<base::Platform> PlatformFactory::create_platform() const
    {
        return std::make_unique<Platform>();
    }

    std::unique_ptr<base::Window> PlatformFactory::create_window() const
    {
        return std::make_unique<Window>();
    }
}
