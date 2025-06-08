// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <ostream>
namespace tdv { namespace nuitrack { namespace device
{

/**
 * @ingroup CommonElements_group
 * @brief Contains activation types.
 */
struct ActivationInfo
{
	enum class Status // please also refer to NuitrackDeviceCommon.cs
	{
		NONE = 0,	///< no valid license
		TRIAL,		///< time-limited license
		PRO,		///< Pro license types
		AI,			///< AI license types 
		AI_ONLINE,  ///< AI subscription license types
		PRO_ONLINE  ///< Pro subscription license types
	};
};

inline std::ostream& operator<< (std::ostream& s, const ActivationInfo::Status status)
{
	switch (status)
	{
		case ActivationInfo::Status::NONE: s << "None"; break;
		case ActivationInfo::Status::TRIAL: s << "Trial"; break;
		case ActivationInfo::Status::AI: s << "AI"; break;
		case ActivationInfo::Status::AI_ONLINE: s << "AI_Online"; break;
		case ActivationInfo::Status::PRO: s << "Pro"; break;
		case ActivationInfo::Status::PRO_ONLINE: s << "Pro_Online"; break;
	}
	return s;
}

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

} } }
