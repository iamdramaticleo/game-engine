#pragma once

namespace gainput
{
    class InputDeviceMouseImpl
    {
    public:
        virtual ~InputDeviceMouseImpl() =default;
        virtual void Update(InputDeltaState* delta) = 0;
    };
}