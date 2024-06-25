#pragma once

#include "platform_factory.hpp"

namespace core
{
    class WindowInstance
    {
    public:
        void create(const std::shared_ptr<base::PlatformFactory>& factory, const base::window_config& config);
        void destroy()    const;
        void update()     const;

        void resize(const base::window_size& size) const;
        void close()                               const;

        [[nodiscard]] base::window_size& size() const;
        [[nodiscard]] std::any handle()  const;
        [[nodiscard]] bool  is_active()  const;

        WindowInstance(const WindowInstance&)            = delete;
        WindowInstance& operator=(const WindowInstance&) = delete;

        static WindowInstance& instance();

    private:
        std::unique_ptr<base::Window> _window;

        WindowInstance() = default;
    };
}