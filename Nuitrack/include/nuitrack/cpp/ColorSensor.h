#pragma once

#include <functional>

#include "nuitrack/cpp/Module.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/Types.h"

namespace tdv { namespace nuitrack { namespace cpp {

/**
 * @brief Represent access to sensor device.
 * @ingroup ColorSensor_group
 */
class ColorSensor: public Module
{
public:
	using Ptr = std::shared_ptr<ColorSensor>;

	/**
	 * ColorSensor new frame event.
	 * Event function receive smart pointer to RGBFrame, which contain color map.
	 */
	using OnNewFrame = std::function<void (RGBFrame::Ptr)>;

	/**
	 * @brief Create ColorSensor.
	 * @return New ColorSensor instance.
	 */
	NUITRACK_API static ColorSensor::Ptr create();

	/**
	 * @brief Get output mode for ColorSensor.
	 * Returns resolution, fps, fov and other sensor information.
	 * @return Output mode.
	 */
	virtual CameraModel getOutputMode() const = 0;

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
	 * @brief Get smart pointer to last available RGBFrame.
	 * @return Smart pointer to last available RGBFrame.
	 */
	virtual RGBFrame::Ptr getColorFrame() = 0;

};

}}}
