#pragma once

#include "vec3.hpp"
#include "rgb.hpp"

namespace core::data
{
    struct light
    {
        vec3  position;
        float ambient;
        rgb   color;
    };
}