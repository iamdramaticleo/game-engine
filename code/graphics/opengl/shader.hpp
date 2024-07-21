#pragma once

#include "shader_stage.hpp"

#include "rgb.hpp"

namespace gl
{
    class Shader final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attach(const ShaderStage& stage) const;

        void bind() const;
        void link() const;

        void push(int32_t location, const float* data)    const;
        void push(int32_t location, const core::rgb& rgb) const;
    };
}