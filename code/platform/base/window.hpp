#pragma once
#pragma region Declaration
         class WindowInstance;
#pragma endregion

#include "window_state.hpp"
#include "window_config.hpp"

namespace base
{
    class Window
    {
    public:
        friend class WindowInstance;

        virtual void create(const window_config& config) = 0;
        virtual void destroy()                           = 0;
        virtual void update()                      const = 0;

        virtual     ~Window() = default;

    private:
        [[nodiscard]] virtual std::any handle() const = 0;

    protected:
        window_state _state { };
        window_size  _size  { };
    };
}