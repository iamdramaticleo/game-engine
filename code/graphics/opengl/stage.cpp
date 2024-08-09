#include "stage.hpp"
#include "macros.hpp"

namespace core::gl
{
    Stage::Stage(const uint32_t type)
        : _type { type }
    {
    }

    void Stage::create()
    {
        _handle = glCreateShader(_type);
    }

    void Stage::destroy()
    {
        glDeleteShader(_handle);
    }

    void Stage::source(const std::vector<char>& source) const
    {
        glShaderBinary(1, &_handle, shader_binary_format, source.data(), static_cast<int32_t>(source.size()));
        glSpecializeShader(_handle, "main", 0, nullptr, nullptr);
    }
}