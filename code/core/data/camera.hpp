#pragma once

#include "math/vec3.hpp"

namespace core::data
{
    struct camera
    {
        glm::mat4  view;
        glm::mat4  proj;

        math::vec3 position;
    };
}