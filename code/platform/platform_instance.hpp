#pragma once

#include "platform_factory.hpp"

namespace core
{
    class PlatformInstance
    {
    public:
        void init(const std::shared_ptr<base::PlatformFactory>& factory);
        void release()  const;
        void update()   const;

        PlatformInstance(const PlatformInstance&)            = delete;
        PlatformInstance& operator=(const PlatformInstance&) = delete;

        static PlatformInstance& instance();

    private:
        std::unique_ptr<base::Platform> _platform;

        PlatformInstance() = default;
    };
}