#include <gainput/gainput.h>
#include <gainput/GainputInputDeltaState.h>

#include "keyboard/GainputInputDeviceKeyboardWin.h"
#include "mouse/GainputInputDeviceMouseWin.h"

#include <stdlib.h>

#include <gainput/GainputHelpers.h>

namespace gainput
{
InputManager::InputManager(bool useSystemTime, Allocator& allocator) :
		allocator_(allocator),
		devices_(allocator_),
		nextDeviceId_(0),
		modifiers_(allocator_),
		nextModifierId_(0),
		deltaState_(allocator_.New<InputDeltaState>(allocator_)),
		currentTime_(0),
        GAINPUT_CONC_CONSTRUCT(concurrentInputs_),
		displayWidth_(-1),
		displayHeight_(-1),
		useSystemTime_(useSystemTime)
{
}

InputManager::~InputManager()
{
	allocator_.Delete(deltaState_);

	for (auto it = devices_.begin(); it != devices_.end(); ++it)
	{
		allocator_.Delete(it->second);
	}
}

void InputManager::Update()
{
    Change change;
    while (GAINPUT_CONC_DEQUEUE(concurrentInputs_, change))
    {
        if (change.type == BT_BOOL)
        {
            HandleButton(*change.device, *change.state, change.delta, change.buttonId, change.b);
        }
        else if (change.type == BT_FLOAT)
        {
            HandleAxis(*change.device, *change.state, change.delta, change.buttonId, change.f);
        }
    }

	InputDeltaState* ds = deltaState_;

	for (auto it = devices_.begin(); it != devices_.end(); ++it)
	{
		if (!it->second->IsLateUpdate())
		{
			it->second->Update(ds);
		}
	}

	for (auto it = modifiers_.begin(); it != modifiers_.end();++it)
	{
		it->second->Update(ds);
	}

	for (auto it = devices_.begin(); it != devices_.end(); ++it)
	{
		if (it->second->IsLateUpdate())
		{
			it->second->Update(ds);
		}
	}

	if (ds)
	{
		ds->Clear();
	}
}

void
InputManager::Update(uint64_t deltaTime)
{
	GAINPUT_ASSERT(useSystemTime_ == false);
	currentTime_ += deltaTime;
	Update();
}

uint64_t
InputManager::GetTime() const
{
	if (useSystemTime_)
	{
	static LARGE_INTEGER perfFreq = { 0 };
	if (perfFreq.QuadPart == 0)
	{
		QueryPerformanceFrequency(&perfFreq);
		GAINPUT_ASSERT(perfFreq.QuadPart != 0);
	}
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	double t = 1000.0 * double(count.QuadPart) / double(perfFreq.QuadPart);
	return static_cast<uint64_t>(t);
}
	else
	{
		return currentTime_;
	}
}

DeviceId
InputManager::FindDeviceId(InputDevice::DeviceType type, unsigned index) const
{
	for (DeviceMap::const_iterator it = devices_.begin();
			it != devices_.end();
			++it)
	{
		if (it->second->GetType() == type
			&& it->second->GetIndex() == index)
		{
			return it->first;
		}
	}
	return InvalidDeviceId;
}

ModifierId InputManager::AddDeviceStateModifier(DeviceStateModifier* modifier)
{
	modifiers_[nextModifierId_] = modifier;
	return nextModifierId_++;
}

void InputManager::RemoveDeviceStateModifier(ModifierId modifierId)
{
	modifiers_.erase(modifierId);
}

size_t InputManager::GetAnyButtonDown(DeviceButtonSpec* outButtons, size_t maxButtonCount) const
{
	size_t buttonsFound = 0;
	for (auto it = devices_.begin(); it != devices_.end() && maxButtonCount > buttonsFound; ++it)
	{
		buttonsFound += it->second->GetAnyButtonDown(outButtons+buttonsFound, maxButtonCount-buttonsFound);
	}
	return buttonsFound;
}

unsigned InputManager::GetDeviceCountByType(const InputDevice::DeviceType type) const
{
	unsigned count = 0;
	for (auto it = devices_.begin(); it != devices_.end(); ++it)
	{
		if (it->second->GetType() == type)
		{
			++count;
		}
	}
	return count;
}

void InputManager::DeviceCreated(InputDevice* device)
{
	GAINPUT_UNUSED(device);
}

void
InputManager::HandleMessage(const MSG& msg)
{
	for (DeviceMap::const_iterator it = devices_.begin(); it != devices_.end(); ++it)
	{
		if (it->second->GetType() == InputDevice::DT_KEYBOARD)
		{
			InputDeviceKeyboard* keyboard = static_cast<InputDeviceKeyboard*>(it->second);
			InputDeviceKeyboardImplWin* keyboardImpl = static_cast<InputDeviceKeyboardImplWin*>(keyboard->GetPimpl());
			GAINPUT_ASSERT(keyboardImpl);
			keyboardImpl->HandleMessage(msg);
		}
		else if (it->second->GetType() == InputDevice::DT_MOUSE)
		{
			InputDeviceMouse* mouse = static_cast<InputDeviceMouse*>(it->second);
			InputDeviceMouseImplWin* mouseImpl = static_cast<InputDeviceMouseImplWin*>(mouse->GetPimpl());
			GAINPUT_ASSERT(mouseImpl);
			mouseImpl->HandleMessage(msg);
		}
	}
}

void InputManager::EnqueueConcurrentChange(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, bool value)
{
    Change change;
    change.device = &device;
    change.state = &state;
    change.delta = delta;
    change.buttonId = buttonId;
    change.type = BT_BOOL;
    change.b = value;
    GAINPUT_CONC_ENQUEUE(concurrentInputs_, change);
}

void InputManager::EnqueueConcurrentChange(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, float value)
{
    Change change;
    change.device = &device;
    change.state = &state;
    change.delta = delta;
    change.buttonId = buttonId;
    change.type = BT_FLOAT;
    change.f = value;
    GAINPUT_CONC_ENQUEUE(concurrentInputs_, change);
}
}