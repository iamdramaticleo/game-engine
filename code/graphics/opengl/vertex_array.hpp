#pragma once

#include "vertex_attribute.hpp"

#include "object.hpp"

namespace gl
{
    class VertexArray final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attribute(const base::vertex_attribute& attribute, int32_t stride) const;
        void bind()    const;
    };
}
