#pragma once

#include "window_state.hpp"

class WindowInstance
{
public:
    void create();
    void destroy() const;
    void update()  const;

private:
    window_state _state  { };
    int32_t      _width  { };
    int32_t      _height { };
};