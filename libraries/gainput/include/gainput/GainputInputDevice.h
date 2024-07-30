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

	/// Returns the type of the given button.
	virtual ButtonType GetButtonType(DeviceButtonId deviceButton) const = 0;

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