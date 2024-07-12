#pragma once

#include "window_size.hpp"
#include "window_state.hpp"

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