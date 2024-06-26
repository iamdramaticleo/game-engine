#pragma once

#include "object.hpp"

#include "base/buffer_data.hpp"

namespace gl
{
    class Buffer final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void bind(uint32_t target) const;

        void data(const base::buffer_data& buffer, uint32_t usage) const;
    };
}