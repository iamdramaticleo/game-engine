#pragma once

#include "base/window.hpp"

namespace core::win32
{
    class Window final : public base::Window
    {
    public:
        void create(const std::string& title) override;
        void destroy()                        override;
        void update()                   const override;

        [[nodiscard]] std::any handle() const override;

    private:
        GLFWwindow*  _handle { };
    };
}