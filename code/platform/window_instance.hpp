#pragma once

#include "platform_factory.hpp"

namespace core
{
    class WindowInstance
    {
    public:
        void init(const std::shared_ptr<base::PlatformFactory>& factory);
        void create(const base::window_config& config); // TODO maybe use the factory in the constructor????

        void release() const;
        void update()  const;

        WindowInstance(const WindowInstance&)            = delete;
        WindowInstance& operator=(const WindowInstance&) = delete;

    private:
        std::unique_ptr<base::Window> _window;
    };
}