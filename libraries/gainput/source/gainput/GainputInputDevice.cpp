#include <gainput/gainput.h>

namespace gainput
{
InputDevice::InputDevice(InputManager& manager, DeviceId device, unsigned index) :
	manager_(manager),
	deviceId_(device),
	index_(index),
	deadZones_(0)
{
}

InputDevice::~InputDevice()
{
	manager_.GetAllocator().Deallocate(deadZones_);
}

void InputDevice::Update(InputDeltaState* delta)
{
	*previousState_ = *state_;
	InternalUpdate(delta);
}

float InputDevice::GetDeadZone(DeviceButtonId buttonId) const
{
	if (!deadZones_ || !IsValidButtonId(buttonId))
	{
		return 0.0f;
	}
	GAINPUT_ASSERT(buttonId < state_->GetButtonCount());
	return deadZones_[buttonId];
}

void InputDevice::SetDeadZone(DeviceButtonId buttonId, float value)
{
	if (!deadZones_)
	{
		const size_t size = sizeof(float) * state_->GetButtonCount();
		deadZones_ = reinterpret_cast<float*>(manager_.GetAllocator().Allocate(size));
		memset(deadZones_, 0, size);
	}
	GAINPUT_ASSERT(buttonId < state_->GetButtonCount());
	deadZones_[buttonId] = value;
}
}