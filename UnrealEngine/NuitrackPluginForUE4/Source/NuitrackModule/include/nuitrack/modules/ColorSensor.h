#ifndef NUITRACK_COLORSENSOR_H_
#define NUITRACK_COLORSENSOR_H_

#include <vector>

#include "nuitrack/modules/HeaderOnlyAPI_Module.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/utils/ExceptionTranslator.h"
#include "nuitrack/types/RGBFrame.h"
#include "nuitrack/types/Vector3.h"
#include "nuitrack/types/OutputMode.h"
#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/capi/ColorSensor_CAPI.h"
#include "nuitrack/utils/CallbackStruct.h"

#include <iostream>

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup ColorSensor_group
 * @brief Represents the interface to the capabilities of the
 * @ref ColorSensor_group "Nuitrack Color Sensor" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor ColorSensor::create.
 * This instance is called %ColorSensor module object.
 * To receive the new color frames, add an ColorSensor::OnNewFrame callback
 * to the module object with ColorSensor::connectOnNewFrame method.
 */
class ColorSensor : public tdv::nuitrack::HeaderOnlyAPI_Module
{
public:

	/**
	* @brief Smart pointer to access the ColorSensor instance.
	* @see create
	*/
	typedef std::shared_ptr<ColorSensor> Ptr;

	/**
	 * @brief The callback type of the new color frame request.
	 *
	 * @see tdv::nuitrack::RGBFrame
	 * @see connectOnNewFrame
	 */
	typedef std::function<void (RGBFrame::Ptr)> OnNewFrame;

	/**
	 * @brief Create the ColorSensor module object.
	 *
	 * @return Smart pointer to a new ColorSensor instance.
	 * @note Do not call this method twice. Instead, use the previously
	 * received ColorSensor::Ptr.
	 */
	static ColorSensor::Ptr create()
	{
		NuitrackModule* pimpl = NULL;
		ExceptionType exception_code = nuitrack_CreateColorSensor(&pimpl);
		ExceptionTranslator::generateExceptionByErrorCode(exception_code);
		return std::shared_ptr<ColorSensor>(new ColorSensor(pimpl));
	}

	/** @warning For internal use only. */
	ColorSensor(NuitrackModule* pimpl)
	{
		_pimpl = pimpl;

		_callbackStruct = new CallbackStruct<RGBFrame::Ptr>();
		_callbackWrapper.setColorSensor(this);
		_callbackWrapper.setFunctionAddress(&onNewFrameCallback);
		nuitrack_registerColorSensorCallback(_pimpl, &_callbackWrapper);
	}

	virtual ~ColorSensor()
	{
		nuitrack_DestroyColorSensor(_pimpl);
		if(_callbackStruct)
			delete _callbackStruct;
	}

	/**
	 * @brief Returns output mode of color sensor.
	 */
	const OutputMode getOutputMode() const
	{
		OutputMode mode;
		nuitrack_GetColorSensorOutputMode(_pimpl, &mode);
		return mode;
	}

	/**
	 * @brief Add a callback for the new color frame request.
	 *
	 * @param[in] callback Callback to be invoked at the new color frame request.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnNewFrame
	 */
	uint64_t connectOnNewFrame(const OnNewFrame& callback)
	{
		return _callbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the new color frame request.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnNewFrame
	 */
	void disconnectOnNewFrame(uint64_t handler)
	{
		_callbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Returns smart pointer to the last available RGBFrame.
	 */
	RGBFrame::Ptr getColorFrame()
	{
		ColorSensorDataPtr data = nuitrack_GetColorSensorData(_pimpl);
		RGBFrame::Ptr newFrame(new RGBFrame(data));
		return newFrame;
	}

	bool canUpdate() const
	{
		return nuitrack_GetNuitrackModuleCanUpdate(_pimpl);
	}

	/**
	 * @brief Returns the last processed data timestamp in microseconds.
	 *
	 * Returns timestamp corresponding to the last available color frame.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp()
	{
		return nuitrack_GetNuitrackModuleTimestamp(_pimpl);
	}

private:

	static void onNewFrameCallback(ColorSensorData* colorFrameImpl, ColorSensor* sensor)
	{
		RGBFrame::Ptr newFrame(new RGBFrame(colorFrameImpl));
		sensor->_callbackStruct->executeAllCallbacks(newFrame);
	}

	NuitrackModule* _pimpl;

	ColorSensorCallbackWrapper _callbackWrapper;

	CallbackStruct<RGBFrame::Ptr>* _callbackStruct;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_COLORSENSOR_H_ */
