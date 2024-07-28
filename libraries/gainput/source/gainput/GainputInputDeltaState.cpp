#include <gainput/gainput.h>
#include <gainput/GainputInputDeltaState.h>

namespace gainput
{
InputDeltaState::InputDeltaState(Allocator& allocator) :
	changes_(allocator)
{
}

void InputDeltaState::AddChange(DeviceId device, DeviceButtonId deviceButton, bool oldValue, bool newValue)
{
	Change change;
	change.device = device;
	change.deviceButton = deviceButton;
	change.type = BT_BOOL;
	change.oldValue.b = oldValue;
	change.newValue.b = newValue;
	changes_.push_back(change);
}

void InputDeltaState::AddChange(DeviceId device, DeviceButtonId deviceButton, float oldValue, float newValue)
{
	Change change;
	change.device = device;
	change.deviceButton = deviceButton;
	change.type = BT_FLOAT;
	change.oldValue.f = oldValue;
	change.newValue.f = newValue;
	changes_.push_back(change);
}

void InputDeltaState::Clear()
{
	changes_.clear();
}
}