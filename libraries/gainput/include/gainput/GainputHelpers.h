#pragma once

namespace gainput
{
	inline void HandleButton(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, bool value)
	{
		if (delta)
		{
			const bool oldValue = state.GetBool(buttonId);
			if (value != oldValue)
			{
				delta->AddChange(device.GetDeviceId(), buttonId, oldValue, value);
			}
		}

		state.Set(buttonId, value);
	}

	inline void HandleAxis(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, float value)
	{
		const float deadZone = device.GetDeadZone(buttonId);
		if (deadZone > 0.0f)
		{
			const float absValue = Abs(value);
			const float sign = value < 0.0f ? -1.0f : 1.0f;
			if (absValue < deadZone)
			{
				value = 0.0f;
			}
			else
			{
				value -= sign*deadZone;
				value *= 1.0f / (1.0f - deadZone);
			}
		}

		if (delta)
		{
			const float oldValue = state.GetFloat(buttonId);
			if (value != oldValue)
			{
				delta->AddChange(device.GetDeviceId(), buttonId, oldValue, value);
			}
		}

		state.Set(buttonId, value);
	}

}