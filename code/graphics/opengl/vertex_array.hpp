#pragma once

#include "vertex/attribute.hpp"

#include "object.hpp"

namespace core::gl
{
    class VertexArray final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attribute(const vertex::attribute& attribute, int32_t stride) const;
        void bind()    const;
    };
}
