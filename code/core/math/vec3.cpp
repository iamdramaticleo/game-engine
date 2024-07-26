#include "vec3.hpp"

namespace core::math
{
    vec3 vec3::normalize() const
    {
        if (const float l = length(); l >= std::numeric_limits<float>::epsilon())
        {
            return *this * (1 / l);
        }

         return *this;
    }

    float vec3::dot(const vec3& a) const
    {
        return x * a.x + y * a.y + z * a.z;
    }

    float vec3::length() const
    {
        return std::sqrtf(dot(*this));
    }

    vec3 vec3::operator*(const float u) const
    {
        return { x * u, y * u, z * u };
    }
}
