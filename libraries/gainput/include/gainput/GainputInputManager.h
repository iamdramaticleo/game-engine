#pragma once

namespace gainput
{
class GAINPUT_LIBEXPORT InputManager
{
public:
	InputManager(Allocator& allocator = GetDefaultAllocator());

	~InputManager();

	void SetDisplaySize(int width, int height) { displayWidth_ = width; displayHeight_ = height; }

	void HandleMessage(const MSG& msg);

	void Update();

	/// Returns the allocator to be used for memory allocations.
	Allocator& GetAllocator() const { return allocator_; }

	/// Creates an input device and registers it with the manager.
	/**
	 * \tparam T The input device class, muste be derived from InputDevice.
	 * \param variant Requests the specified device variant. Note that this is only
	 * a request. Another implementation variant of the device may silently be instantiated
	 * instead. To determine what variant was instantiated, call InputDevice::GetVariant().
	 * \return The ID of the newly created input device.
	 */
	template<class T> DeviceId CreateDevice(unsigned index = InputDevice::AutoIndex);

	/// Returns the input device with the given ID.
	/**
	 * \return The input device or 0 if it doesn't exist.
	 */
	InputDevice* GetDevice(DeviceId deviceId);
	/// Returns the input device with the given ID.
	/**
	 * \return The input device or 0 if it doesn't exist.
	 */
	const InputDevice* GetDevice(DeviceId deviceId) const;
	/// Returns the ID of the device with the given type and index.
	/**
	 * \param type The device type. Should come from InputDevice::GetType().
	 * \param index The index of the device. Should come from InputDevice::GetIndex().
	 * \return The device's ID or InvalidDeviceId if no matching device exists.
	 */
	DeviceId FindDeviceId(InputDevice::DeviceType type, unsigned index) const;

	typedef HashMap<DeviceId, InputDevice*> DeviceMap;
	/// Iterator over all registered devices.
	typedef DeviceMap::iterator iterator;
	/// Const iterator over all registered devices.
	typedef DeviceMap::const_iterator const_iterator;

	/// Returns the begin iterator over all registered devices.
	iterator begin() { return devices_.begin(); }
	/// Returns the end iterator over all registered devices.
	iterator end() { return devices_.end(); }
	/// Returns the begin iterator over all registered devices.
	const_iterator begin() const { return devices_.begin(); }
	/// Returns the end iterator over all registered devices.
	const_iterator end() const { return devices_.end(); }

	/// Returns the number of devices with the given type.
	unsigned GetDeviceCountByType(InputDevice::DeviceType type) const;
	/// Returns the graphical display's width in pixels.
	int GetDisplayWidth() const { return displayWidth_; }
	/// Returns the graphical display's height in pixels.
	int GetDisplayHeight() const { return displayHeight_; }

	/// Registers a modifier that will be called after devices have been updated.
	ModifierId AddDeviceStateModifier(DeviceStateModifier* modifier);
	/// De-registers the given modifier.
	void RemoveDeviceStateModifier(ModifierId modifierId);

    void EnqueueConcurrentChange(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, bool value);
    void EnqueueConcurrentChange(InputDevice& device, InputState& state, InputDeltaState* delta, DeviceButtonId buttonId, float value);

private:
	Allocator& allocator_;

	DeviceMap devices_;
	unsigned nextDeviceId_;

	HashMap<ModifierId, DeviceStateModifier*> modifiers_;
	unsigned nextModifierId_;

	InputDeltaState* deltaState_;

    struct Change
    {
        InputDevice* device;
        InputState* state;
        InputDeltaState* delta;
        DeviceButtonId buttonId;
		ButtonType type;
		union
		{
			bool b;
			float f;
		};
    };

    GAINPUT_CONC_QUEUE(Change) concurrentInputs_;

	int displayWidth_;
	int displayHeight_;

	// Do not copy.
	InputManager(const InputManager &);
	InputManager& operator=(const InputManager &);
};

template<class T> DeviceId
InputManager::CreateDevice(unsigned index)
{
	T* device = allocator_.New<T>(*this, nextDeviceId_, index);
	devices_[nextDeviceId_] = device;
	return nextDeviceId_++;
}

inline InputDevice* InputManager::GetDevice(DeviceId deviceId)
{
	const auto it = devices_.find(deviceId);
	if (it == devices_.end())
	{
		return 0;
	}
	return it->second;
}

inline const InputDevice* InputManager::GetDevice(DeviceId deviceId) const
{
	const auto it = devices_.find(deviceId);
	if (it == devices_.end())
	{
		return 0;
	}
	return it->second;
}

/// Interface for modifiers that change device input states after they have been updated.
class DeviceStateModifier
{
public:
	/// Called after non-dependent devices have been updated.
	/**
	 * This function is called by InputManager::Update() after InputDevice::Update() has been
	 * called on all registered devices that have InputDevice::IsLateUpdate() return \c false.
	 *
	 * \param delta All device state changes should be registered with this delta state, may be 0.
	 */
	virtual void Update(InputDeltaState* delta) = 0;
};
}