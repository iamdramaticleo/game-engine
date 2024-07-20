#pragma once

#include "base/platform_factory.hpp"

class PlatformModule
{
public:
    static std::shared_ptr<base::PlatformFactory> create_factory();
};