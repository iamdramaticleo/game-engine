#include <gainput/gainput.h>

#include <stdlib.h>

namespace
{
	template<class T> T Min(const T&a, const T& b) { return a < b ? a : b; }
	template<class T> T Max(const T&a, const T& b) { return a < b ? b : a; }
}

namespace gainput
{
class MappedInput
{
public:
	DeviceId device;
	DeviceButtonId deviceButton;

	float rangeMin;
	float rangeMax;

	FilterFunc_T filterFunc;
	void* filterUserData;
};

typedef Array<MappedInput> MappedInputList;

class UserButton
{
public:
	UserButtonId userButton;
	MappedInputList inputs;
	InputMap::UserButtonPolicy policy;
	float deadZone;

	UserButton(Allocator& allocator) :
		inputs(allocator),
		deadZone(0.0f)
	{ }
};

InputMap::InputMap(InputManager& manager, Allocator& allocator) :
	manager_(manager),
	allocator_(allocator),
	userButtons_(allocator_),
	nextUserButtonId_(0)
{
	static unsigned nextId = 0;
	id_ = nextId++;
}

InputMap::~InputMap()
{
	Clear();
}

void InputMap::Clear()
{
	for (auto it = userButtons_.begin(); it != userButtons_.end(); ++it)
	{
		allocator_.Delete(it->second);
	}
	userButtons_.clear();
	nextUserButtonId_ = 0;
}

bool InputMap::MapBool(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton)
{
	UserButton* ub = GetUserButton(userButton);

	if (!ub)
	{
		ub = allocator_.New<UserButton>(allocator_);
		GAINPUT_ASSERT(ub);
		ub->userButton = nextUserButtonId_++;
		ub->policy = UBP_FIRST_DOWN;
		userButtons_[userButton] = ub;
	}

	MappedInput mi;
	mi.device = device;
	mi.deviceButton = deviceButton;
	ub->inputs.push_back(mi);

	return true;
}

bool InputMap::MapFloat(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton, float min, float max, FilterFunc_T filterFunc, void* filterUserData)
{
	UserButton* ub = GetUserButton(userButton);

	if (!ub)
	{
		ub = allocator_.New<UserButton>(allocator_);
		GAINPUT_ASSERT(ub);
		ub->userButton = nextUserButtonId_++;
		ub->policy = UBP_FIRST_DOWN;
		userButtons_[userButton] = ub;
	}

	MappedInput mi;
	mi.device = device;
	mi.deviceButton = deviceButton;
	mi.rangeMin = min;
	mi.rangeMax = max;
	mi.filterFunc = filterFunc;
	mi.filterUserData = filterUserData;
	ub->inputs.push_back(mi);

	return true;
}

void InputMap::Unmap(UserButtonId userButton)
{
	UserButton* ub = GetUserButton(userButton);
	if (ub)
	{
		allocator_.Delete(ub);
		userButtons_.erase(userButton);
	}
}

bool InputMap::IsMapped(UserButtonId userButton) const
{
	return GetUserButton(userButton) != 0;
}

size_t InputMap::GetMappings(UserButtonId userButton, DeviceButtonSpec* outButtons, size_t maxButtonCount) const
{
	size_t buttonCount = 0;
	const UserButton* ub = GetUserButton(userButton);
	if (!ub)
	{
		return 0;
	}
	for (MappedInputList::const_iterator it = ub->inputs.begin();
			it != ub->inputs.end() && buttonCount < maxButtonCount;
			++it, ++buttonCount)
	{
		const MappedInput& mi = *it;
		outButtons[buttonCount].deviceId = mi.device;
		outButtons[buttonCount].buttonId = mi.deviceButton;
	}
	return buttonCount;
}

bool InputMap::SetUserButtonPolicy(UserButtonId userButton, UserButtonPolicy policy)
{
	UserButton* ub = GetUserButton(userButton);
	if (!ub)
	{
		return false;
	}
	ub->policy = policy;
	return true;
}

bool InputMap::SetDeadZone(UserButtonId userButton, float deadZone)
{
	UserButton* ub = GetUserButton(userButton);
	if (!ub)
	{
		return false;
	}
	ub->deadZone = deadZone;
	return true;
}

bool InputMap::GetBool(UserButtonId userButton) const
{
	const UserButton* ub = GetUserButton(userButton);
	GAINPUT_ASSERT(ub);
	for (MappedInputList::const_iterator it = ub->inputs.begin();
			it != ub->inputs.end();
			++it)
	{
		const MappedInput& mi = *it;
		const InputDevice* device = manager_.GetDevice(mi.device);
		GAINPUT_ASSERT(device);
		if (device->GetBool(mi.deviceButton))
		{
			return true;
		}
	}
	return false;
}

bool InputMap::GetBoolIsNew(UserButtonId userButton) const
{
	const UserButton* ub = GetUserButton(userButton);
	GAINPUT_ASSERT(ub);
	for (MappedInputList::const_iterator it = ub->inputs.begin();
			it != ub->inputs.end();
			++it)
	{
		const MappedInput& mi= *it;
		const InputDevice* device = manager_.GetDevice(mi.device);
		GAINPUT_ASSERT(device);
		if (device->GetBool(mi.deviceButton)
				&& !device->GetBoolPrevious(mi.deviceButton))
		{
			return true;
		}
	}
	return false;
}

bool InputMap::GetBoolPrevious(UserButtonId userButton) const
{
	const UserButton* ub = GetUserButton(userButton);
	GAINPUT_ASSERT(ub);
	for (auto it = ub->inputs.begin(); it != ub->inputs.end(); ++it)
	{
		const MappedInput& mi= *it;
		const InputDevice* device = manager_.GetDevice(mi.device);
		GAINPUT_ASSERT(device);
		if (device->GetBoolPrevious(mi.deviceButton))
		{
			return true;
		}
	}
	return false;
}

bool InputMap::GetBoolWasDown(UserButtonId userButton) const
{
	const UserButton* ub = GetUserButton(userButton);
	GAINPUT_ASSERT(ub);
	for (auto it = ub->inputs.begin(); it != ub->inputs.end(); ++it)
	{
		const MappedInput& mi= *it;
		const InputDevice* device = manager_.GetDevice(mi.device);
		GAINPUT_ASSERT(device);
		if (!device->GetBool(mi.deviceButton)
				&& device->GetBoolPrevious(mi.deviceButton))
		{
			return true;
		}
	}
	return false;
}

float InputMap::GetFloat(UserButtonId userButton) const
{
	return GetFloatState(userButton, false);
}

float InputMap::GetFloatPrevious(UserButtonId userButton) const
{
	return GetFloatState(userButton, true);
}

float InputMap::GetFloatDelta(UserButtonId userButton) const
{
	return GetFloat(userButton) - GetFloatPrevious(userButton);
}

float InputMap::GetFloatState(UserButtonId userButton, bool previous) const
{
	float value = 0.0f;
	int downCount = 0;
	const UserButton* ub = GetUserButton(userButton);
	GAINPUT_ASSERT(ub);
	for (auto it = ub->inputs.begin();it != ub->inputs.end();++it)
	{
		const MappedInput& mi= *it;
		const InputDevice* device = manager_.GetDevice(mi.device);
		GAINPUT_ASSERT(device);

		bool down = false;
		float deviceValue = 0.0f;
		if (device->GetButtonType(mi.deviceButton) == BT_BOOL)
		{
			down = previous ? device->GetBoolPrevious(mi.deviceButton) : device->GetBool(mi.deviceButton);
			deviceValue = down ? mi.rangeMax : mi.rangeMin;
		}
		else
		{
			const float tmpValue = previous ? device->GetFloatPrevious(mi.deviceButton) : device->GetFloat(mi.deviceButton);
			if (tmpValue != 0.0f)
			{
				GAINPUT_ASSERT(device->GetButtonType(mi.deviceButton) == BT_FLOAT);
				deviceValue = mi.rangeMin + tmpValue*mi.rangeMax;
				down = true;
			}
		}

		if (mi.filterFunc)
		{
			deviceValue = mi.filterFunc(deviceValue, mi.filterUserData);
		}

		if (down)
		{
			++downCount;
			if (ub->policy == UBP_FIRST_DOWN)
			{
				value = deviceValue;
				break;
			}
			if (ub->policy == UBP_MAX)
			{
				if (Abs(deviceValue) > Abs(value))
				{
					value = deviceValue;
				}
			}
			else if (ub->policy == UBP_MIN)
			{
				if (downCount == 1)
				{
					value = deviceValue;
				}
				else
				{
					if (Abs(deviceValue) < Abs(value))
					{
						value = deviceValue;
					}
				}
			}
			else if (ub->policy == UBP_AVERAGE)
			{
				value += deviceValue;
			}
		}
	}

	if (ub->policy == UBP_AVERAGE && downCount)
	{
		value /= static_cast<float>(downCount);
	}

	if (Abs(value) <= ub->deadZone)
	{
		value = 0.0f;
	}

	return value;
}

UserButtonId InputMap::GetUserButtonId(DeviceId device, DeviceButtonId deviceButton) const
{
	for (auto it = userButtons_.begin();it != userButtons_.end();++it)
	{
		const UserButton* ub = it->second;
		for (auto it2 = ub->inputs.begin();it2 != ub->inputs.end();++it2)
		{
			const MappedInput& mi = *it2;
			if (mi.device == device && mi.deviceButton == deviceButton)
			{
				return it->first;
			}
		}
	}
	return InvalidUserButtonId;
}

UserButton* InputMap::GetUserButton(UserButtonId userButton)
{
	auto it = userButtons_.find(userButton);
	if (it == userButtons_.end())
	{
		return nullptr;
	}
	return it->second;
}

const UserButton* InputMap::GetUserButton(UserButtonId userButton) const
{
	auto it = userButtons_.find(userButton);
	if (it == userButtons_.end())
	{
		return nullptr;
	}
	return it->second;
}
}