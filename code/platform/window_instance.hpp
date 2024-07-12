#pragma once

#include "base/window_size.hpp"
#include "base/window_state.hpp"

class WindowInstance
{
public:
    void create();
    void destroy() const;
    void update()  const;

private:
    window_state _state { };
    window_size  _size  { };
};