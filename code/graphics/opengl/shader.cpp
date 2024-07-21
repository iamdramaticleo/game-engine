#include "shader.hpp"

namespace gl
{
    void Shader::create()
    {
        _handle = glCreateProgram();
    }

    void Shader::destroy()
    {
        glDeleteProgram(_handle);
    }

    void Shader::attach(const ShaderStage& stage) const
    {
        glAttachShader(_handle, stage._handle);
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

    void Shader::push(const int32_t location, const core::rgb& rgb) const
    {
        glProgramUniform3fv(_handle, location, 1, &rgb.r);
    }
}