#pragma once

#include "platform_factory.hpp"

namespace core
{
    class WindowManager
    {
    public:
        WindowManager(const WindowManager&)            = delete;
        WindowManager& operator=(const WindowManager&) = delete;

        static WindowManager& instance() noexcept;

    private:
        std::unique_ptr<base::Window> _window;

        WindowManager() = default;
    };
}