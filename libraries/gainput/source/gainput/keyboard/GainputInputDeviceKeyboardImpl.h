#pragma once

namespace gainput
{
    class InputDeviceKeyboardImpl
    {
    public:
        virtual ~InputDeviceKeyboardImpl() { }

        virtual void Update(InputDeltaState* delta) = 0;
        virtual InputState* GetNextInputState() { return 0; }

        virtual bool IsTextInputEnabled() const = 0;
        virtual void SetTextInputEnabled(bool enabled) = 0;
        virtual char GetNextCharacter() = 0;
    };
}