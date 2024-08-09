#pragma once

#include "math/rgb.hpp"

#include "stage.hpp"

namespace core::gl
{
    class Shader final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attach(const Stage& stage) const;

        void bind() const;
        void link() const;

        [[maybe_unused]] void push(int32_t location, const     float* data) const;
        [[maybe_unused]] void push(int32_t location, const math::rgb&  rgb) const;
    };
}