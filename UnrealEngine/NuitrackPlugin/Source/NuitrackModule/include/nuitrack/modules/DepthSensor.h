#ifndef NUITRACK_DEPTHSENSOR_H_
#define NUITRACK_DEPTHSENSOR_H_

#include <vector>

#include "nuitrack/modules/HeaderOnlyAPI_Module.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/utils/ExceptionTranslator.h"
#include "nuitrack/types/DepthFrame.h"
#include "nuitrack/types/Vector3.h"
#include "nuitrack/types/OutputMode.h"
#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/capi/DepthSensor_CAPI.h"
#include "nuitrack/utils/CallbackStruct.h"

#include <iostream>

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup DepthSensor_group
 * @brief Represents the interface to the capabilities of the
 * @ref DepthSensor_group "Nuitrack Depth Sensor" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor DepthSensor::create.
 * This instance is called %DepthSensor module object.
 * To receive the new depth frames, add an DepthSensor::OnNewFrame callback
 * to the module object with DepthSensor::connectOnNewFrame method.
 * Use DepthSensor::convertProjToRealCoords
 * to convert coordinates from the projective system to the world and
 * DepthSensor::convertProjToRealCoords for reverse conversion.
 */
class DepthSensor : public tdv::nuitrack::HeaderOnlyAPI_Module
{
public:

	/**
	* @brief Smart pointer to access the DepthSensor instance.
	* @see create
	*/
	typedef std::shared_ptr<DepthSensor> Ptr;

	/**
	 * @brief The callback type of the new depth frame request.
	 *
	 * @see tdv::nuitrack::DepthFrame
	 * @see connectOnNewFrame
	 */
	typedef std::function<void (DepthFrame::Ptr)> OnNewFrame;

	/**
	 * @brief Create the DepthSensor module object.
	 *
	 * @return Smart pointer to a new DepthSensor instance.
	 * @note Do not call this method twice. Instead, use the previously
	 * received DepthSensor::Ptr.
	 */
	static DepthSensor::Ptr create()
	{
		NuitrackModule* pimpl = NULL;
		ExceptionType exception_code = nuitrack_CreateDepthSensor(&pimpl);
		char exception_message[1024];
		nuitrack_GetExceptionMessage(pimpl, exception_message, 1024);
		ExceptionTranslator::generateExceptionByErrorCode(exception_code, exception_message);
		return std::shared_ptr<DepthSensor>(new DepthSensor(pimpl));
	}

	/** @warning For internal use only. */
	DepthSensor(NuitrackModule* pimpl)
	{
		_pimpl = pimpl;

		_callbackStruct = new CallbackStruct<DepthFrame::Ptr>();
		_callbackWrapper.setDepthSensor(this);
		_callbackWrapper.setFunctionAddress(&onNewFrameCallback);
		nuitrack_registerDepthSensorCallback(_pimpl, &_callbackWrapper);
	}

	virtual ~DepthSensor()
	{
		nuitrack_DestroyDepthSensor(_pimpl);
		if(_callbackStruct)
			delete _callbackStruct;
	}

	/**
	 * @brief Returns output mode of depth sensor.
	 */
	const OutputMode getOutputMode() const
	{
		OutputMode mode;
		nuitrack_GetDepthSensorOutputMode(_pimpl, &mode);
		return mode;
	}

	/**
	 * @brief Returns true if mirror mode is enabled, false otherwise.
	 * @see setMirror
	 */
	bool isMirror() const
	{
		return nuitrack_IsDepthSensorMirror(_pimpl);
	}

	/**
	 * @brief Set mirror mode state.
	 *
	 * Call setMirror(true) to enable mirror mode.
	 * Call setMirror(false) to disable mirror mode.
	 *
	 * If the mirror mode is on, the depth map from the sensor will be
	 * reflected horizontally before consequent processing.
	 *
	 * @param[in] mirror Mirror mode state to be set.
	 * @see isMirror
	 */
	void setMirror(bool mirror)
	{
		nuitrack_SetDepthSensorMirror(_pimpl, mirror);
	}

	/**
	 * @brief Add a callback for the new depth frame request.
	 *
	 * @param[in] callback Callback to be invoked at the new depth frame request.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnNewFrame
	 */
	uint64_t connectOnNewFrame(const OnNewFrame& callback)
	{
		return _callbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the new depth frame request.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnNewFrame
	 */
	void disconnectOnNewFrame(uint64_t handler)
	{
		_callbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Returns smart pointer to the last available DepthFrame.
	 */

	DepthFrame::Ptr getDepthFrame()
	{
		DepthSensorDataPtr data = nuitrack_GetDepthSensorData(_pimpl);
		DepthFrame::Ptr newFrame(new DepthFrame(data));
		return newFrame;
	}

	/**
	 * @brief Convert projective coordinates to real world coordinates from Vector3 point.
	 * @param[in] p Projective point coordinates.
	 * @return Converted real world point.
	 */
	Vector3 convertProjToRealCoords(const Vector3& p) const
	{
		CVector3 c_vec { p.x, p.y, p.z };
		return Vector3(nuitrack_ctypes_ConvertProjToRealCoordsVector3(_pimpl, c_vec));
	}

	/**
	* @brief Convert projective coordinates to real world coordinates from x, y and depth map.
	* @param[in] x,y Projective point coordinates.
	* @param[in] depth Depth map.
	* @return Converted real world point.
	*/
	virtual Vector3 convertProjToRealCoords(size_t x, size_t y, DepthFrame::DataType depth) const
	{
		return Vector3(nuitrack_ctypes_ConvertProjToRealCoordsXYZ(_pimpl, x, y, depth));
	}

	/**
	 * @brief Convert real world coordinates to projective coordinates from Vector3 point.
	 * @param[in] p Real world point coordinates.
	 * @return Converted projective point.
	 */
	virtual Vector3 convertRealToProjCoords(const Vector3& p) const
	{
		CVector3 c_vec { p.x, p.y, p.z };
		return Vector3(nuitrack_ctypes_ConvertRealToProjCoordsVector3(_pimpl, c_vec));
	}

	/**
	* @brief Convert real world coordinates to projective coordinates from x, y, z.
	* @param[in] x,y,z Real world point coordinates.
	* @return Converted projective point.
	*/
	virtual Vector3 convertRealToProjCoords(float x, float y, float z) const
	{
		return Vector3(nuitrack_ctypes_ConvertRealToProjCoordsXYZ(_pimpl, x, y, z));
	}

	bool canUpdate() const
	{
		return nuitrack_GetNuitrackModuleCanUpdate(_pimpl);
	}

	/**
	 * @brief Returns the last processed data timestamp in microseconds.
	 *
	 * Returns timestamp corresponding to the last available depth frame.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp()
	{
		return nuitrack_GetNuitrackModuleTimestamp(_pimpl);
	}

private:

	static void onNewFrameCallback(DepthSensorData* depthFrameImpl, DepthSensor* sensor)
	{
		DepthFrame::Ptr newFrame(new DepthFrame(depthFrameImpl));
		sensor->_callbackStruct->executeAllCallbacks(newFrame);
	}

	NuitrackModule* _pimpl;

	DepthSensorCallbackWrapper _callbackWrapper;

	CallbackStruct<DepthFrame::Ptr>* _callbackStruct;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_DEPTHSENSOR_H_ */
