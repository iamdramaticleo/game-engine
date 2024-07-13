#pragma once

#include "base/platform_factory.hpp"

namespace core
{
    class PlatformModule
    {
    public:
        static std::shared_ptr<base::PlatformFactory> create_factory();
    };
}