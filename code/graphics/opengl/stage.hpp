#pragma once

#include "object.hpp"

namespace core::gl
{
    class Stage final : public Object
    {
    public:
    explicit Stage(uint32_t type);

        void create()    override;
        void destroy()   override;

        void source(const std::vector<char>& source) const;

    private:
        uint32_t _type;
    };
}