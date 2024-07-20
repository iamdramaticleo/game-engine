#pragma once

#include "window_config.hpp"

namespace base
{
    class Window
    {
    public:
        enum class state
        {
            active,
            closed
        };

        virtual void create(const window_config& config) = 0;
        virtual void destroy()                           = 0;
        virtual void update()                      const = 0;

        virtual std::any handle()                  const = 0;
        virtual         ~Window() = default;

        void switch_state(const state state)
        {
            _state = state;
        }
        bool    has_state(const state state) const
        {
            return _state == state;
        }

    private:
        int32_t _width  { };
        int32_t _height { };

        state   _state  { };
    };
}