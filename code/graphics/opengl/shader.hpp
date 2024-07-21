#pragma once

#include "shader_stage.hpp"

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

        void uniform_mat4(int32_t location, const float* data) const;
        void uniform_vec3(int32_t location, const float* data) const;
    };
}