#pragma once

#include "base/factory.hpp"

namespace core::win32
{
    class PlatformFactory final : public base::PlatformFactory
    {
    public:
        [[nodiscard]] std::unique_ptr<base::Window> create_window() const override;
    };
}