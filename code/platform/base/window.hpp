#pragma once

#include "window_state.hpp"
#include "window_size.hpp"

namespace core::base
{
    class Window
    {
    public:
        virtual void create(const std::string& title) = 0;
        virtual void destroy()                        = 0;
        virtual void update()                   const = 0;

        virtual std::any handle()               const = 0;
        virtual         ~Window() = default;

        void state(const window_state state)
        {
            _state = state;
        }
        void size(const  window_size& size)
        {
            _size = size;
        }

        const window_size& size()  const
        {
            return _size;
        }
              window_state state() const
        {
            return _state;
        }

    protected:
        window_state _state { };
        window_size  _size  { };
    };
}