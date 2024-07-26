#include "shader.hpp"

namespace core::gl
{
    void Shader::create()
    {
        _handle = glCreateProgram();
    }

    void Shader::destroy()
    {
        glDeleteProgram(_handle);
    }

    void Shader::attach(const Stage& stage) const
    {
        glAttachShader(_handle, stage.handle());
    }

    void Shader::bind() const
    {
        glUseProgram(_handle);
    }

    void Shader::link() const
    {
        glLinkProgram(_handle);
    }

    void Shader::push(const int32_t location, const float* data) const
    {
        glProgramUniformMatrix4fv(_handle, location, 1, 0, data);
    }

    void Shader::push(const int32_t location, const math::rgb& rgb) const
    {
        glProgramUniform3fv(_handle, location, 1, &rgb.r);
    }
}