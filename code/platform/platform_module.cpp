#include "platform_module.hpp"

#ifdef WIN32
#include "windows/platform_factory.hpp"

namespace core
{
    std::shared_ptr<base::PlatformFactory> PlatformModule::create_factory()
    {
        return std::make_shared<win32::PlatformFactory>();
    }
}
#endif