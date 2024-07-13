#pragma once

#include "base/window_state.hpp"
#include "base/platform_factory.hpp"

class WindowInstance
{
public:
    void create();
    void destroy() const;
    void update()  const;

private:
    std::unique_ptr<base::Window> _window;

    window_state _state  { };
    int32_t      _width  { };
    int32_t      _height { };
};