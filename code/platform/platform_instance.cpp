#include "platform_instance.hpp"

namespace core
{
    void PlatformInstance::init(const std::shared_ptr<base::PlatformFactory>& factory)
    {
        _platform = factory->create_platform();
        _platform->init();
    }

    void PlatformInstance::release() const
    {
        _platform->release();
    }

    void PlatformInstance::update() const
    {
        _platform->update();
    }
}
