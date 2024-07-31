#pragma once

namespace gainput
{
class UserButton;
/// Type for filter functions that can be used to filter mapped float inputs.
typedef float (*FilterFunc_T)(float const value, void* userData);

class GAINPUT_LIBEXPORT InputMap
{
public:
	/// Initializes the map.
	/**
	 * \param manager The input manager used to get device inputs.
	 * \param name The name for the input map (optional). If a name is provided, it is copied to an internal buffer.
	 * \param allocator The allocator to be used for all memory allocations.
	 */
	InputMap(InputManager& manager, Allocator& allocator = GetDefaultAllocator());
	/// Unitializes the map.
	~InputMap();

	/// Clears all mapped inputs.
	void Clear();

	/// Returns the input manager this input map uses.
	const InputManager& GetManager() const { return manager_; }
	/// Returns the map's auto-generated ID (that should not be used outside of the library).
	unsigned GetId() const { return id_; }

	/// Maps a bool-type button.
	/**
	 * \param userButton The user ID for this mapping.
	 * \param device The device's ID of the device button to be mapped.
	 * \param deviceButton The ID of the device button to be mapped.
	 * \return true if the mapping was created.
	 */
	bool MapBool(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton);
	/// Maps a float-type button, possibly to a custom range.
	/**
	 * \param userButton The user ID for this mapping.
	 * \param device The device's ID of the device button to be mapped.
	 * \param deviceButton The ID of the device button to be mapped.
	 * \param min Optional minimum value of the mapped button.
	 * \param max Optional maximum value of the mapped button.
	 * \param filterFunc Optional filter functions that modifies the device button value.
	 * \param filterUserData Optional user data pointer that is passed to filterFunc.
	 * \return true if the mapping was created.
	 */
	bool MapFloat(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton, float min = 0.0f, float max = 1.0f,
			FilterFunc_T filterFunc = 0, void* filterUserData = 0);
	/// Removes all mappings for the given user button.
	void Unmap(UserButtonId userButton);
	/// Returns if the given user button has any mappings.
	bool IsMapped(UserButtonId userButton) const;
	
	/// Gets all device buttons mapped to the given user button.
	/**
	 * \param userButton The user button ID of the button to return all mappings for.
	 * \param[out] outButtons An array with maxButtonCount fields to receive the device buttons that are mapped.
	 * \param maxButtonCount The number of fields in outButtons.
	 * \return The number of device buttons written to outButtons.
	 */
	size_t GetMappings(UserButtonId userButton, DeviceButtonSpec* outButtons, size_t maxButtonCount) const;
	
	/// Policy for how multiple device buttons are summarized in one user button.
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