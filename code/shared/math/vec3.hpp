#pragma once

namespace core
{
    struct vec3
    {
        vec3 operator*(float u) const;
        vec3 normalize()        const;

        float dot(const vec3& a) const;
        float length()           const;

        float x;
        float y;
        float z;
    };
}
