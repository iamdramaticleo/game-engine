#pragma once

#include "vertex_attribute.hpp"

#include "object.hpp"

namespace core::gl
{
    class VertexArray final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attribute(const vertex_attribute& attribute, int32_t stride) const;
        void bind()    const;
    };
}
