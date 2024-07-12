#pragma once

namespace base
{
    class Platform
    {
    public:
        virtual void init()         = 0;
        virtual void release()      = 0;
        virtual void update() const = 0;

        virtual ~Platform() = default;
    };
}