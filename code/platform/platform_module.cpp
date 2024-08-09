#include "platform_module.hpp"

#ifdef WIN32
#include "windows/factory.hpp"
#endif

namespace core
{
    #ifdef WIN32
    std::shared_ptr<base::PlatformFactory> PlatformModule::create_factory()
    {
        return std::make_shared<win32::PlatformFactory>();
    }
    #endif
}