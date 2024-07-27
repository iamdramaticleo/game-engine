#pragma once

namespace gainput
{
/// Type of an input device button.
enum ButtonType
{
	BT_BOOL,	///< A boolean value button, either down (true) or up (false).
	BT_FLOAT,	///< A floating-point value button, between -1.0f and 1.0f or 0.0f and 1.0f.
	BT_COUNT	///< The number of different button types.
};

/// Interface for anything that provides device inputs.
/**
 * An InputDevice can be anything from a physical device, like a mouse or keyboard, to the more abstract
 * concept of gestures that in turn themselves depend on other InputDevices. What they have in common is
 * that they provide a number of device buttons (identified by a DeviceButtonId) which can be queried for
 * their state.
 *
 * Note that you may not instantiate an InputDevice (or any derived implementation) directly. Instead you
 * have to call InputManager::CreateDevice() or InputManager::CreateAndGetDevice() with the device you want
 * to instantiate as the template parameter. That way the device will be properly registered with the
 * InputManager and continuously updated.
 *
 * Normally, you won't interact with an InputDevice directly, but instead use its device ID and its device
 * buttons' IDs to map the device buttons to user buttons (see InputMap).
 */
class GAINPUT_LIBEXPORT InputDevice
{
public:
	/// Type of an input device.
	enum DeviceType
	{
		DT_MOUSE,
		DT_KEYBOARD,
		DT_COUNT
	};

	static const unsigned AutoIndex = unsigned(-1);

	/// Initializes the input device.
	/**
	 * Do not instantiate any input device directly. Call InputManager::CreateDevice() instead.
	 */
	InputDevice(InputManager& manager, DeviceId device, unsigned index);

	/// Empty virtual destructor.
	virtual ~InputDevice();

	/// Update this device, internally called by InputManager.
	/**
	 * \param delta The delta state to add changes to. May be 0.
	 */
	void Update(InputDeltaState* delta);

	/// Returns this device's ID.
	DeviceId GetDeviceId() const { return deviceId_; }
	/// Returns the device's index among devices of the same type.
	unsigned GetIndex() const { return index_; }

	/// Returns the device type.
	virtual DeviceType GetType() const = 0;
	/// Returns if this device should be updated after other devices.
	virtual bool IsLateUpdate() const { return false; }

	/// Returns if the given button is valid for this device.
	virtual bool IsValidButtonId(DeviceButtonId deviceButton) const = 0;

	/// Returns the current state of the given button.
	bool GetBool(DeviceButtonId deviceButton) const;
	/// Returns the previous state of the given button.
	bool GetBoolPrevious(DeviceButtonId deviceButton) const;
	/// Returns the current state of the given button.
	float GetFloat(DeviceButtonId deviceButton) const;
	/// Returns the previous state of the given button.
	float GetFloatPrevious(DeviceButtonId deviceButton) const;

	/// Checks if any button on this device is down.
	/**
	 * \param[out] outButtons An array with maxButtonCount fields to receive the device buttons that are down.
	 * \param maxButtonCount The number of fields in outButtons.
	 * \return The number of device buttons written to outButtons.
	 */
	virtual size_t GetAnyButtonDown(DeviceButtonSpec* outButtons, size_t maxButtonCount) const { GAINPUT_UNUSED(outButtons); GAINPUT_UNUSED(maxButtonCount); return 0; }

	/// Gets the name of the given button.
	/**
	 * \param deviceButton ID of the button.
	 * \param buffer A char-buffer to receive the button name.
	 * \param bufferLength Length of the buffer receiving the button name in bytes.
	 * \return The number of bytes written to buffer (includes the trailing \0).
	 */
	virtual size_t GetButtonName(DeviceButtonId deviceButton, char* buffer, size_t bufferLength) const { GAINPUT_UNUSED(deviceButton); GAINPUT_UNUSED(buffer); GAINPUT_UNUSED(bufferLength); return 0; }
	/// Returns the type of the given button.
	virtual ButtonType GetButtonType(DeviceButtonId deviceButton) const = 0;

	/// Returns the button's ID if the name is of this device's buttons.
	/**
	 * \param name Name of the device button to look for.
	 * \return The device button ID.
	 */
	virtual DeviceButtonId GetButtonByName(const char* name) const { GAINPUT_UNUSED(name); return InvalidDeviceButtonId; }

	/// Returns the device's state, probably best if only used internally.
	InputState* GetInputState() { return state_; }
	/// Returns the device's state, probably best if only used internally.
	const InputState* GetInputState() const { return state_; }
	/// Returns the device's previous state, probably best if only used internally.
	InputState* GetPreviousInputState() { return previousState_; }
	/// Returns the device's state that is currently being determined, may be 0 if not available.
	virtual InputState* GetNextInputState() { return 0; }

	/// Returns the previously set dead zone for the given button or 0.0f if none was set yet.
	float GetDeadZone(DeviceButtonId buttonId) const;
	/// Sets the dead zone for the given button.
	void SetDeadZone(DeviceButtonId buttonId, float value);

protected:
	/// The manager this device belongs to.
	InputManager& manager_;

	/// The ID of this device.
	DeviceId deviceId_;

	/// Index of this device among devices of the same type.
	unsigned index_;

	/// The current state of this device.
	InputState* state_;
	/// The previous state of this device.
	InputState* previousState_;

	float* deadZones_;

	/// Implementation of the device's Update function.
	/**
	 * \param delta The delta state to add changes to. May be 0.
	 */
	virtual void InternalUpdate(InputDeltaState* delta) = 0;

	/// Checks which buttons are down.
	/**
	 * This function is normally used by GetAnyButtonDown implementations internally.
	 * \param outButtons An array to write buttons that are down to.
	 * \param maxButtonCount The size of outButtons.
	 * \param start The lowest device button ID to check.
	 * \param end The biggest device button ID to check.
	 * \return The number of buttons written to outButtons.
	 */
	size_t CheckAllButtonsDown(DeviceButtonSpec* outButtons, size_t maxButtonCount, unsigned start, unsigned end) const;
};

inline
bool
InputDevice::GetBool(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(state_);
	return state_->GetBool(deviceButton);
}

inline
bool
InputDevice::GetBoolPrevious(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(previousState_);
	return previousState_->GetBool(deviceButton);
}

inline
float
InputDevice::GetFloat(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(state_);
	return state_->GetFloat(deviceButton);
}

inline
float
InputDevice::GetFloatPrevious(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(previousState_);
	return previousState_->GetFloat(deviceButton);
}
}