#pragma once

#include "base/platform_factory.hpp"

class WindowInstance
{
public:
    void create(const std::shared_ptr<base::PlatformFactory>& factory, const base::window_config& config);
    void destroy()    const;
    void update()     const;

    void close() const;

    [[nodiscard]] bool is_active() const;

    WindowInstance& operator=(const WindowInstance&) = delete;
    WindowInstance(const WindowInstance&)            = delete;

    static WindowInstance& instance();

private:
    std::unique_ptr<base::Window> _window;

    WindowInstance() = default;
};