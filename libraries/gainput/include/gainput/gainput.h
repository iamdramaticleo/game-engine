#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER)
	#define GAINPUT_PLATFORM_WIN
	#if defined(GAINPUT_LIB_DYNAMIC)
		#define GAINPUT_LIBEXPORT		__declspec(dllexport)
	#elif defined(GAINPUT_LIB_DYNAMIC_USE)
		#define GAINPUT_LIBEXPORT		__declspec(dllimport)
	#else
		#define GAINPUT_LIBEXPORT
	#endif
#endif

//#define GAINPUT_DEBUG
//#define GAINPUT_DEV
#define GAINPUT_ENABLE_ALL_GESTURES
#define GAINPUT_ENABLE_RECORDER
#define GAINPUT_TEXT_INPUT_QUEUE_LENGTH 32

#ifdef GAINPUT_ENABLE_CONCURRENCY
#define MOODYCAMEL_EXCEPTIONS_DISABLED
#include "concurrentqueue.h"
#define GAINPUT_CONC_QUEUE(TYPE)            moodycamel::ConcurrentQueue<TYPE>
#define GAINPUT_CONC_CONSTRUCT(queue)       queue()
#define GAINPUT_CONC_ENQUEUE(queue, obj)    queue.enqueue(obj)
#define GAINPUT_CONC_DEQUEUE(queue, obj)    queue.try_dequeue(obj)
#else
#define GAINPUT_CONC_QUEUE(TYPE)            gainput::Array<TYPE>
#define GAINPUT_CONC_CONSTRUCT(queue)       queue(allocator)
#define GAINPUT_CONC_ENQUEUE(queue, obj)    queue.push_back(obj)
#define GAINPUT_CONC_DEQUEUE(queue, obj)    (!queue.empty() ? (obj = queue[queue.size()-1], queue.pop_back(), true) : false)
#endif

#include <cassert>
#include <cstring>
#include <new>

#define GAINPUT_ASSERT assert
#define GAINPUT_UNUSED(x) (void)(x)

#include <cstdlib>

typedef struct tagMSG MSG;

namespace gainput
{
	typedef unsigned __int8 uint8_t;
	typedef __int8 int8_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint64_t;
}

/// Contains all Gainput related classes, types, and functions.
namespace gainput
{
/// ID of an input device.
typedef unsigned int DeviceId;
/// ID of a specific button unique to an input device.
typedef unsigned int DeviceButtonId;

/// Describes a device button on a specific device.
struct DeviceButtonSpec
{
	/// ID of the input device.
	DeviceId deviceId;
	/// ID of the button on the given input device.
	DeviceButtonId buttonId;
};

/// ID of a user-defined, mapped button.
typedef unsigned int UserButtonId;
/// ID of an input listener.
typedef unsigned int ListenerId;
/// ID of a device state modifier.
typedef unsigned int ModifierId;

/// An invalid device ID.
static const DeviceId InvalidDeviceId = -1;
/// An invalid device button ID.
static const DeviceButtonId InvalidDeviceButtonId = -1;
/// An invalid user button ID.
static const UserButtonId InvalidUserButtonId = -1;

class InputDeltaState;
class InputListener;
class InputManager;
class DebugRenderer;
class DeviceStateModifier;

template <class T> T Abs(T a) { return a < T() ? -a : a; }
}

#include <gainput/GainputAllocator.h>
#include <gainput/GainputContainers.h>
#include <gainput/GainputInputState.h>
#include <gainput/GainputInputDevice.h>
#include <gainput/GainputInputListener.h>
#include <gainput/GainputInputManager.h>
#include <gainput/GainputInputMap.h>

#include <gainput/GainputInputDeviceMouse.h>
#include <gainput/GainputInputDeviceKeyboard.h>