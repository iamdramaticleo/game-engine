#pragma once

namespace gainput
{
/// Stores a list of input state changes.
class GAINPUT_LIBEXPORT InputDeltaState
{
public:
	InputDeltaState(Allocator& allocator);

	/// Add a state change for a bool-type button.
	/**
	 * \param device The input device the change occurred on.
	 * \param deviceButton The input button that was changed.
	 * \param oldValue The old button state.
	 * \param newValue The new button state.
	 */
	void AddChange(DeviceId device, DeviceButtonId deviceButton, bool oldValue, bool newValue);
	/// Add a state change for a float-type button.
	/**
	 * \param device The input device the change occurred on.
	 * \param deviceButton The input button that was changed.
	 * \param oldValue The old button state.
	 * \param newValue The new button state.
	 */
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