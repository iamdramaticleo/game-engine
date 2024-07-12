#pragma once

#include "base/window.hpp"

namespace win32
{
    class Window final : public base::Window
    {
    public:
        void create(const window_config& config) override;
        void destroy()                           override;
        void update()                      const override;

        [[nodiscard]] std::any handle()    const override;

    private:
        GLFWwindow*  _handle { };
    };
}