#include <gainput/gainput.h>

#include "GainputInputDeviceMouseImpl.h"
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
}