// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <vector>
#include <string>
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/Types.h"


namespace tdv { namespace nuitrack { namespace device { namespace cpp {

class MIDDLEWARE_API NuitrackDevice // legacy
{
public:
	using Ptr = std::shared_ptr<NuitrackDevice>;

	virtual ~NuitrackDevice() = default;

	/**
	 * @brief Provides device info by type.
	 * @param [in] info_type Type of device info.
	 * @return Info about a device.
	 */
	virtual std::string getInfo(DeviceInfoType info_type) const = 0;

	/**
	 * @brief Provides all available video modes for a current StreamType.
	 * @param [in] stream_type Stream type of VideoMode.
	 * @return Vector of available video modes.
	 */
	virtual std::vector<VideoMode> getAvailableVideoModes(StreamType stream_type) const = 0;

	/**
	 * @brief Provides selected video mode for a current StreamType.
	 * @param [in] stream_type Stream type of VideoMode.
	 * @return Selected VideoMode.
	 */
	virtual VideoMode getSelectedVideoMode(StreamType stream_type) const = 0;

	/**
	 * @brief Sets video mode for a current StreamType.
	 * @param [in] stream_type Stream type of VideoMode.
	 * @param [in] video_mode Video mode.
	 */
	virtual void setVideoMode(StreamType stream_type, VideoMode video_mode) = 0;

	/**
	 * @brief Get license activation status.
	 * @return License activation status.
	 */
	virtual ActivationStatus getActivationStatus() const = 0;

	/**
	 * @brief Activate the current device.
	 * @param [in] activation_key License key for Nuitrack.
	 * @throw tdv::nuitrack::Exception
	 */
	virtual void activate(std::string activation_key) = 0;

	/**
	 * @brief For internal use only.
	 *
	 * FIXME: This does not match the reference design.
	 * The public interface should not be the construction entry point.
	 * The implementation object should be constructed first and then exposed through the interface class.
	 */

	static Ptr create(const std::vector<std::string>&			  deviceInfo,
					  const std::vector<std::vector<VideoMode> >& modes);

	static Ptr create(const std::vector<std::string>&             deviceInfo,
					  const std::vector<std::string>&             specialData,
					  const std::vector<std::vector<VideoMode> >& modes);
};

}}}}
