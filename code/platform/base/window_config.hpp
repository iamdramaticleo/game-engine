#pragma once

#include "window_size.hpp"

namespace core::base
{
    struct window_config
    {
        std::string title;

        window_size size;
    };
}