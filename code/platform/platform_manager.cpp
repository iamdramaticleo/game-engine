#include "platform_manager.hpp"

namespace core
{
    void PlatformManager::init(const std::shared_ptr<base::PlatformFactory>& factory)
    {
        _platform = factory->create_platform();
        _platform->init();
    }

    void PlatformManager::release() const
    {
        _platform->release();
    }

    void PlatformManager::update() const
    {
        _platform->update();
    }

    PlatformManager& PlatformManager::instance() noexcept
    {
        static PlatformManager instance;
        return instance;
    }
}
