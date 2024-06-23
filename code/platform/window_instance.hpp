#pragma once

#include "platform_factory.hpp"

namespace core
{
    class WindowInstance
    {
    public:
        WindowInstance(const WindowInstance&)            = delete;
        WindowInstance& operator=(const WindowInstance&) = delete;

    private:
        std::unique_ptr<base::Window> _window;
    };
}