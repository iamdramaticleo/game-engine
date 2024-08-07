#pragma once

#include "base/factory.hpp"
#include "base/window_config.hpp"

namespace core
{
    class WindowInstance
    {
    public:
        void create(const std::shared_ptr<base::PlatformFactory>& factory, const base::window_config& config);
        void destroy()    const;
        void update()     const;
        void close()      const;

        [[nodiscard]] std::any handle() const;

        [[nodiscard]] int32_t width()   const;
        [[nodiscard]] int32_t height()  const;

        [[nodiscard]] bool is_active()  const;

        WindowInstance& operator=(const WindowInstance&) = delete;
        WindowInstance(const WindowInstance&)            = delete;

        static WindowInstance& instance();

    private:
        std::unique_ptr<base::Window> _window;

        WindowInstance() = default;
    };
}