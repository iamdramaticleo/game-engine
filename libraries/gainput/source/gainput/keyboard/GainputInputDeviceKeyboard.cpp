#include <gainput/gainput.h>

#include "GainputInputDeviceKeyboardImpl.h"
#include "GainputKeyboardKeyNames.h"
#include <gainput/GainputInputDeltaState.h>
#include <gainput/GainputHelpers.h>

#include "GainputInputDeviceKeyboardWin.h"

namespace gainput
{

InputDeviceKeyboard::InputDeviceKeyboard(InputManager& manager, DeviceId device, unsigned index) :
	InputDevice(manager, device, index == InputDevice::AutoIndex ? manager.GetDeviceCountByType(DT_KEYBOARD): index),
	impl_(0),
	keyNames_(manager_.GetAllocator())
{
	state_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), KeyCount_);
	GAINPUT_ASSERT(state_);
	previousState_ = manager.GetAllocator().New<InputState>(manager.GetAllocator(), KeyCount_);
	GAINPUT_ASSERT(previousState_);

	impl_ = manager.GetAllocator().New<InputDeviceKeyboardImplWin>(manager, *this, *state_, *previousState_);

	GAINPUT_ASSERT(impl_);

	GetKeyboardKeyNames(keyNames_);
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

size_t InputDeviceKeyboard::GetAnyButtonDown(DeviceButtonSpec* outButtons, size_t maxButtonCount) const
{
	GAINPUT_ASSERT(outButtons);
	GAINPUT_ASSERT(maxButtonCount > 0);
	return CheckAllButtonsDown(outButtons, maxButtonCount, 0, KeyCount_);
}

size_t InputDeviceKeyboard::GetButtonName(DeviceButtonId deviceButton, char* buffer, size_t bufferLength) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	GAINPUT_ASSERT(buffer);
	GAINPUT_ASSERT(bufferLength > 0);
	const auto it = keyNames_.find(Key(deviceButton));
	if (it == keyNames_.end())
	{
		return 0;
	}
	strncpy(buffer, it->second, bufferLength);
	buffer[bufferLength-1] = 0;
	const size_t nameLen = strlen(it->second);
	return nameLen >= bufferLength ? bufferLength : nameLen+1;
}

ButtonType InputDeviceKeyboard::GetButtonType(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	return BT_BOOL;
}

DeviceButtonId InputDeviceKeyboard::GetButtonByName(const char* name) const
{
	GAINPUT_ASSERT(name);
	for (auto it = keyNames_.begin(); it != keyNames_.end(); ++it)
	{
		if (strcmp(name, it->second) == 0)
		{
			return it->first;
		}
	}
	return InvalidDeviceButtonId;
}

InputState* InputDeviceKeyboard::GetNextInputState()
{
	return impl_->GetNextInputState();
}

bool
InputDeviceKeyboard::IsTextInputEnabled() const
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