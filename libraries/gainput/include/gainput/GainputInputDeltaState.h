#pragma once

namespace gainput
{
class InputDeltaState
{
public:
	InputDeltaState(Allocator& allocator);

	void AddChange(DeviceId device, DeviceButtonId deviceButton, bool oldValue, bool newValue);
	void AddChange(DeviceId device, DeviceButtonId deviceButton, float oldValue, float newValue);

	/// Clear list of state changes.
	void Clear();

private:
	struct Change
	{
		DeviceId device;
		DeviceButtonId deviceButton;
		ButtonType type;
		union
		{
			bool b;
			float f;
		} oldValue, newValue;
	};

	Array<Change> changes_;
};
}