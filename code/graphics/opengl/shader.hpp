#pragma once

#include "shader_stage.hpp"

#include "rgb.hpp"

namespace core::gl
{
    class Shader final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attach(const ShaderStage& stage) const;

        void bind() const;
        void link() const;

        [[maybe_unused]] void push(int32_t location, const float* data) const;
        [[maybe_unused]] void push(int32_t location, const   rgb&  rgb) const;
    };
}