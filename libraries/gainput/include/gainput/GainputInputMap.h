#pragma once

namespace gainput
{
class UserButton;
typedef float (*FilterFunc_T)(float const value, void* userData);

class GAINPUT_LIBEXPORT InputMap
{
public:
	InputMap(InputManager& manager, Allocator& allocator = GetDefaultAllocator());
	/// Unitializes the map.
	~InputMap();

	/// Clears all mapped inputs.
	void Clear();

	/// Returns the input manager this input map uses.
	const InputManager& GetManager() const { return manager_; }

	unsigned GetId() const { return id_; }

	bool MapBool(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton);

	bool MapFloat(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton, float min = 0.0f, float max = 1.0f,
			FilterFunc_T filterFunc = 0, void* filterUserData = 0);
	/// Removes all mappings for the given user button.
	void Unmap(UserButtonId userButton);
	/// Returns if the given user button has any mappings.
	bool IsMapped(UserButtonId userButton) const;

	size_t GetMappings(UserButtonId userButton, DeviceButtonSpec* outButtons, size_t maxButtonCount) const;

	enum UserButtonPolicy
	{
		UBP_FIRST_DOWN,		///< The first device buttons that is down (or not 0.0f) determines the result.
		UBP_MAX,		///< The maximum of all device button states is the result.
		UBP_MIN,		///< The minimum of all device button states is the result.
		UBP_AVERAGE		///< The average of all device button states is the result.
	};

	bool SetUserButtonPolicy(UserButtonId userButton, UserButtonPolicy policy);

	bool SetDeadZone(UserButtonId userButton, float deadZone);

	bool GetBool(UserButtonId userButton) const;
	bool GetBoolIsNew(UserButtonId userButton) const;
	bool GetBoolPrevious(UserButtonId userButton) const;
	bool GetBoolWasDown(UserButtonId userButton) const;

	float GetFloat(UserButtonId userButton) const;
	float GetFloatPrevious(UserButtonId userButton) const;
	float GetFloatDelta(UserButtonId userButton) const;

	UserButtonId GetUserButtonId(DeviceId device, DeviceButtonId deviceButton) const;

private:
	InputManager& manager_;
	unsigned id_;
	Allocator& allocator_;

	typedef HashMap<UserButtonId, UserButton*> UserButtonMap;
	UserButtonMap userButtons_;
	UserButtonId nextUserButtonId_;

	float GetFloatState(UserButtonId userButton, bool previous) const;

	UserButton* GetUserButton(UserButtonId userButton);
	const UserButton* GetUserButton(UserButtonId userButton) const;

	// Do not copy.
	InputMap(const InputMap &);
	InputMap& operator=(const InputMap &);
};
}