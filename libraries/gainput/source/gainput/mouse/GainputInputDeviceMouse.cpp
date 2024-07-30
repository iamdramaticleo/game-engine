#include <gainput/gainput.h>

#include "GainputInputDeviceMouseImpl.h"
#include <gainput/GainputInputDeltaState.h>
#include <gainput/GainputHelpers.h>

#include "GainputInputDeviceMouseWin.h"

namespace gainput
{
ButtonType deviceButtonInfos[] =
{
	BT_BOOL,//"mouse_left" },
	BT_BOOL,//"mouse_middle" },
	BT_BOOL,//"mouse_right" },
	BT_BOOL,//"mouse_3" },
	BT_BOOL,//"mouse_4" },
	BT_BOOL,//"mouse_5" },
	BT_BOOL,//"mouse_6" },
	BT_BOOL,//"mouse_7" },
	BT_BOOL,//"mouse_8" },
	BT_BOOL,//"mouse_9" },
	BT_BOOL,//"mouse_10" },
	BT_BOOL,//"mouse_11" },
	BT_BOOL,//"mouse_12" },
	BT_BOOL,//"mouse_13" },
	BT_BOOL,//"mouse_14" },
	BT_BOOL,//"mouse_15" },
	BT_BOOL,//"mouse_16" },
	BT_BOOL,//"mouse_17" },
	BT_BOOL,//"mouse_18" },
	BT_BOOL,//"mouse_19" },
	BT_BOOL,//"mouse_20" },
	BT_FLOAT,// "mouse_x" },
	BT_FLOAT,//"mouse_y" }
};

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

ButtonType InputDeviceMouse::GetButtonType(DeviceButtonId deviceButton) const
{
	GAINPUT_ASSERT(IsValidButtonId(deviceButton));
	return deviceButtonInfos[deviceButton];
}
}