#pragma once

#include "platform.hpp"
#include "window.hpp"

namespace base
{
    class PlatformFactory
    {
    public:
        virtual std::unique_ptr<Platform> create_platform() const = 0;
        virtual std::unique_ptr<Window>   create_window()   const = 0;

        virtual ~PlatformFactory() = default;
    };
}