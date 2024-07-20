#pragma once

#include "window_config.hpp"

namespace base
{
    class Window
    {
        enum class state
        {
            active,
            closed
        };

    public:
        friend class WindowInstance;

        virtual void create(const window_config& config) = 0;
        virtual void destroy()                           = 0;
        virtual void update()                      const = 0;

        virtual std::any handle()                  const = 0;
        virtual         ~Window() = default;

    private:
        state _state { };
    };
}