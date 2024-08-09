#pragma once

#include "math/vec3.hpp"
#include "math/rgb.hpp"

namespace core::data
{
    struct light
    {
        math::vec3 position;
        float      ambient;
        math::rgb  color;
    };
}