// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

namespace tdv
{
namespace nuitrack
{
namespace device
{

/**
 * @ingroup CommonElements_group
 * @brief Contains activation types.
 */
struct ActivationInfo
{
	enum Status
	{
		NONE = 0,	///< no valid license
		TRIAL,		///< time-limited license
		PRO,		///< unlimited license types
		AI,		    ///< AI license types
		AI_ONLINE,
		PRO_ONLINE
	};
};
typedef ActivationInfo::Status ActivationStatus;

/**
 * @ingroup CommonElements_group
 * @brief Contains information types for NuitrackDevice.
 */
struct DeviceInfo
{
	enum Type
	{
		PROVIDER_NAME = 0,	///< device provider
		DEVICE_NAME,		///< device name from a driver
		SERIAL_NUMBER,		///< device serial number from a driver
		Count
	};
};
typedef DeviceInfo::Type DeviceInfoType;

/**
 * @ingroup CommonElements_group
 * @brief Contains stream data types.
 */
struct Stream
{
	enum Type
	{
		DEPTH = 0,	///< depth stream
		COLOR,		///< color stream
		Count
	};
};
typedef Stream::Type StreamType;

/**
 * @ingroup CommonElements_group
 * @brief Contains parameters for a stream.
 */
struct VideoMode
{
	int width;	///< frame width in pixels
	int height;	///< frame height in pixels
	int fps;	///< frame rate in FPS
};

}
}
}
