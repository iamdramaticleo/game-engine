#pragma once

#include "object.hpp"

#include "base/buffer_data.hpp"
#include "base/buffer_location.hpp"

namespace gl
{
    class Buffer final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void bind(uint32_t target)                const;
        void bind(base::buffer_location location) const;

        void     data(const base::buffer_data& buffer, uint32_t usage)      const;
        void sub_data(const base::buffer_data& buffer, int32_t  offset = 0) const;
    };
}