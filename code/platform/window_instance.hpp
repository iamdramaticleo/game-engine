#pragma once

#include "base/window_state.hpp"
#include "base/platform_factory.hpp"

class WindowInstance
{
public:
    void create(const std::shared_ptr<base::PlatformFactory>& factory, const window_config& config);
    void destroy()    const;
    void update()     const;

    void close();

    [[nodiscard]] bool is_active() const;

    WindowInstance& operator=(const WindowInstance&) = delete;
    WindowInstance(const WindowInstance&)            = delete;

    static WindowInstance& instance();

private:
    WindowInstance() = default;

    std::unique_ptr<base::Window> _window;

    window_state _state  { };
    int32_t      _width  { };
    int32_t      _height { };
};