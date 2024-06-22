#include      "platform_factory.hpp"
#include "glfw/platform_factory.hpp"

namespace core
{
    std::shared_ptr<base::PlatformFactory> PlatformFactory::create_factory()
    {
        return std::make_shared<glfw::PlatformFactory>();
    }
}
