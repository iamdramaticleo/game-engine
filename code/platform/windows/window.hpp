#pragma once

#include "base/window.hpp"

namespace win32
{
    class Window final : public base::Window
    {
    public:
        void create(const base::window_config& config) override;
        void destroy()                                 override;
        void update()                            const override;

    private:
        [[nodiscard]] std::any handle() const override;

        GLFWwindow*  _handle { };
    };
}