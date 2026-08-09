// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <functional>

#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/Types.h"

namespace tdv { namespace nuitrack { namespace cpp {

/**
 * @brief Represent access to sensor device.
 * @ingroup DepthSensor_group
 */
class DepthSensor: public Module
{
public:
	using Ptr = std::shared_ptr<DepthSensor>;

	/**
	 * DepthSensor new frame event.
	 * Event function receive smart pointer to DepthFrame, which is contain depth map.
	 */
	using OnNewFrame = std::function<void (DepthFrame::Ptr)>;

	/**
	 * @brief Create DepthSensor.
	 * @return New DepthSensor instance.
	 */
	NUITRACK_API static Ptr create();

	/**
	 * @brief Get output mode for DepthSensor.
	 * Returns resolution, fps, fov and other sensor information.
	 * @return Output mode.
	 */
	virtual CameraModel getOutputMode() const = 0;

	/**
	 * @brief Get mirror mode of DepthSensor.
	 * @return Mirror mode of DepthSensor.
	 */
	virtual bool isMirror() const = 0;

	/**
	 * @brief Set mirror mode for DepthSensor.
	 * @param[in] mirror Mirror mode for DepthSensor.
	 */
	virtual void setMirror(bool mirror) = 0;

	/**
	 * @brief Register OnNewFrame event callback.
	 * @param[in] callback OnNewFrame event callback.
	 * @return Callback handler.
	 */
	virtual uint64_t connectOnNewFrame(const OnNewFrame& callback) = 0;

	/**
	 * @brief Unregister OnNewFrame event callback.
	 * @param[in] callback Callback handler.
	 */
	virtual void disconnectOnNewFrame(uint64_t handler) = 0;

	/**
	 * @brief Get smart pointer to last available DepthFrame.
	 * @return Smart pointer to last available DepthFrame.
	 */
	virtual DepthFrame::Ptr getDepthFrame() = 0;

	virtual Vector3 convertProjToRealCoords(const Vector3& p) const = 0;
	virtual Vector3 convertProjToRealCoords(int x, int y, DepthFrame::DataType depth) const = 0;

	virtual Vector3 convertRealToProjCoords(const Vector3& p) const = 0;
	virtual Vector3 convertRealToProjCoords(float x, float y, float z) const = 0;
};

}}}
