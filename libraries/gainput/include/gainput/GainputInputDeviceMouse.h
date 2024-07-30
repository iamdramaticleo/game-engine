#pragma once

namespace gainput
{
/// All valid device buttons for InputDeviceMouse.
enum MouseButton
{
	MouseButton0 = 0,
	MouseButtonLeft = MouseButton0,
	MouseButton1,
	MouseButtonMiddle = MouseButton1,
	MouseButton2,
	MouseButtonRight = MouseButton2,
	MouseButton3,
	MouseButtonWheelUp = MouseButton3,
	MouseButton4,
	MouseButtonWheelDown = MouseButton4,
	MouseButton5,
	MouseButton6,
	MouseButton7,
	MouseButton8,
	MouseButton9,
	MouseButton10,
	MouseButton11,
	MouseButton12,
	MouseButton13,
	MouseButton14,
	MouseButton15,
	MouseButton16,
	MouseButton17,
	MouseButton18,
	MouseButton19,
	MouseButton20,
	MouseButtonMax = MouseButton20,
	MouseButtonCount,
	MouseAxisX = MouseButtonCount,
	MouseAxisY,
	MouseButtonCount_,
	MouseAxisCount = MouseButtonCount_ - MouseAxisX
};

class InputDeviceMouseImpl;

class GAINPUT_LIBEXPORT InputDeviceMouse : public InputDevice
{
public:
	/// Initializes the device.
	/**
	 * Instantiate the device using InputManager::CreateDevice().
	 *
	 * \param manager The input manager this device is managed by.
	 * \param device The ID of this device.
	 */
	InputDeviceMouse(InputManager& manager, DeviceId device, unsigned index);
	/// Shuts down the device.
	~InputDeviceMouse();

	/// Returns DT_MOUSE.
	DeviceType GetType() const { return DT_MOUSE; }

	bool IsValidButtonId(DeviceButtonId deviceButton) const { return deviceButton < MouseButtonCount_; }

	ButtonType GetButtonType(DeviceButtonId deviceButton) const;

	/// Returns the platform-specific implementation of this device (internal use only).
	InputDeviceMouseImpl* GetPimpl() { return impl_; }

protected:
	void InternalUpdate(InputDeltaState* delta);

private:
	InputDeviceMouseImpl* impl_;
};
}