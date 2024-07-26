#pragma once

namespace core::math
{
    struct vec3
    {
        vec3 operator*(const float u) const
        {
            return { x * u, y * u, z * u };
        }
        vec3 normalize()              const
        {
            if (const float l = length(); l >= std::numeric_limits<float>::epsilon())
            {
                return *this * (1 / l);
            }

            return *this;
        }

        float dot(const vec3& a) const
        {
            return x * a.x + y * a.y + z * a.z;
        }
        float length()           const
        {
            return std::sqrtf(dot(*this));
        }

        float x;
        float y;
        float z;
    };
}
