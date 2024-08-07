#pragma once

#include "window.hpp"

namespace core::base
{
    class PlatformFactory
    {
    public:
        virtual  std::unique_ptr<Window> create_window() const = 0;

        virtual ~PlatformFactory() = default;
    };
}