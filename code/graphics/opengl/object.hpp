#pragma once

namespace gl
{
    class Object
    {
    public:
        virtual void create()  = 0;
        virtual void destroy() = 0;

    protected:
        virtual  ~Object() = default;

        uint32_t _handle { };
    };
}