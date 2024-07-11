#pragma once

#include "base/platform.hpp"

namespace win32
{
    class Platform final : public base::Platform
    {
    public:
        void init()    override;
        void release() override;

        void update()  const override;
    };
}