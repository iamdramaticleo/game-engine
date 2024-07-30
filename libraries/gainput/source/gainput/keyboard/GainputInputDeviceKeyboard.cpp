#include <gainput/gainput.h>

#include "GainputInputDeviceKeyboardImpl.h"
#include <gainput/GainputInputDeltaState.h>
#include <gainput/GainputHelpers.h>

#include "GainputInputDeviceKeyboardWin.h"

namespace gainput
{
InputDeviceKeyboard::InputDeviceKeyboard(InputManager& manager, DeviceId device, unsigned index) :
	InputDevice(manager, device, index == InputDevice::AutoIndex ? manager.GetDeviceCountByType(DT_KEYBOARD): index),
	impl_(0)
{
	state_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), KeyCount_);
	GAINPUT_ASSERT(state_);
	previousState_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), KeyCount_);
	GAINPUT_ASSERT(previousState_);

	impl_ = manager.GetAllocator().New<InputDeviceKeyboardImplWin>(manager, *this, *state_, *previousState_);

	GAINPUT_ASSERT(impl_);
}

InputDeviceKeyboard::~InputDeviceKeyboard()
{
	manager_.GetAllocator().Delete(state_);
	manager_.GetAllocator().Delete(previousState_);
	manager_.GetAllocator().Delete(impl_);
}

void InputDeviceKeyboard::InternalUpdate(InputDeltaState* delta)
{
	impl_->Update(delta);
}

ButtonType InputDeviceKeyboard::GetButtonType(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	return BT_BOOL;
}

InputState* InputDeviceKeyboard::GetNextInputState()
{
	return impl_->GetNextInputState();
}

bool InputDeviceKeyboard::IsTextInputEnabled() const
{
	return impl_->IsTextInputEnabled();
}

void InputDeviceKeyboard::SetTextInputEnabled(bool enabled)
{
	impl_->SetTextInputEnabled(enabled);
}

char InputDeviceKeyboard::GetNextCharacter()
{
	return impl_->GetNextCharacter();
}
}