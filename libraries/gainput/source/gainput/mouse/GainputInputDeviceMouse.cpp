#include <gainput/gainput.h>

#include "GainputInputDeviceMouseImpl.h"
#include "GainputMouseInfo.h"
#include <gainput/GainputInputDeltaState.h>
#include <gainput/GainputHelpers.h>

#include "GainputInputDeviceMouseWin.h"

namespace gainput
{
InputDeviceMouse::InputDeviceMouse(InputManager& manager, const DeviceId device, const unsigned index) :
	InputDevice(manager, device, index == AutoIndex ? manager.GetDeviceCountByType(DT_MOUSE) : index),
	impl_(nullptr)
{
	state_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), MouseButtonCount + MouseAxisCount);
	GAINPUT_ASSERT(state_);
	previousState_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), MouseButtonCount + MouseAxisCount);
	GAINPUT_ASSERT(previousState_);

	impl_ = manager.GetAllocator().New<InputDeviceMouseImplWin>(manager, *this, *state_, *previousState_);

	GAINPUT_ASSERT(impl_);
}

InputDeviceMouse::~InputDeviceMouse()
{
	manager_.GetAllocator().Delete(state_);
	manager_.GetAllocator().Delete(previousState_);
	manager_.GetAllocator().Delete(impl_);
}

void InputDeviceMouse::InternalUpdate(InputDeltaState* delta)
{
	impl_->Update(delta);
}

size_t InputDeviceMouse::GetAnyButtonDown(DeviceButtonSpec* outButtons, size_t maxButtonCount) const
{
	GAINPUT_ASSERT(outButtons);
	GAINPUT_ASSERT(maxButtonCount > 0);
	return CheckAllButtonsDown(outButtons, maxButtonCount, MouseButton0, MouseButtonCount_);
}

size_t InputDeviceMouse::GetButtonName(DeviceButtonId deviceButton, char* buffer, size_t bufferLength) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	GAINPUT_ASSERT(buffer);
	GAINPUT_ASSERT(bufferLength > 0);
	strncpy(buffer, deviceButtonInfos[deviceButton].name, bufferLength);
	buffer[bufferLength-1] = 0;
	const size_t nameLen = strlen(deviceButtonInfos[deviceButton].name);
	return nameLen >= bufferLength ? bufferLength : nameLen+1;
}

ButtonType InputDeviceMouse::GetButtonType(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	return deviceButtonInfos[deviceButton].type;
}

DeviceButtonId InputDeviceMouse::GetButtonByName(const char* name) const
{
	GAINPUT_ASSERT(name);
	for (unsigned i = 0; i < MouseButtonCount + MouseAxisCount; ++i)
	{
		if (strcmp(name, deviceButtonInfos[i].name) == 0)
		{
			return DeviceButtonId(i);
		}
	}
	return InvalidDeviceButtonId;
}
}