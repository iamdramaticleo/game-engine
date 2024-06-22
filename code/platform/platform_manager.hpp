#pragma once

#include "platform_factory.hpp"

namespace core
{
    class PlatformManager
    {
    public:
        void init(const std::shared_ptr<base::PlatformFactory>& factory);

        void release() const;
        void update()  const;

        PlatformManager(const PlatformManager&)            = delete;
        PlatformManager& operator=(const PlatformManager&) = delete;

        static PlatformManager& instance() noexcept;

    private:
        std::unique_ptr<base::Platform> _platform;

        PlatformManager() = default;
    };
}