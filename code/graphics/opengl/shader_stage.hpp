#pragma once

#include "object.hpp"

namespace gl
{
    class ShaderStage final : public Object
    {
    public:
        friend class Shader;

    explicit ShaderStage(uint32_t type);
        void create()    override;
        void destroy()   override;

        void source(const std::vector<char>& source) const;

    private:
        uint32_t _type;
    };
}