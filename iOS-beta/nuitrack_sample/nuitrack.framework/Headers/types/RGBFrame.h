#ifndef NUITRACK_RGBFRAME_H_
#define NUITRACK_RGBFRAME_H_

#include "nuitrack/types/Color3.h"
#include "nuitrack/types/Frame.h"
#include "nuitrack/capi/ColorSensor_CAPI.h"

namespace tdv
{
namespace nuitrack
{
/**
* @brief Stores a frame color map.
* @ingroup ColorSensor_group
*/
class RGBFrame : public Frame<RGBFrame, Color3>
{
public:
	/** @warning For internal use only. */
	RGBFrame(ColorSensorData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddColorSensorDataRef(pimpl);
	}

	virtual ~RGBFrame()
	{
		nuitrack_DestroyColorSensorData(_pimpl);
	}

	/**
	 * @brief Returns the number of rows in the RGB frame.
	 */
	int getRows() const
	{
		return nuitrack_GetColorFrameRows(_pimpl);
	}

	/**
	 * @brief Returns the number of columns in the RGB frame.
	 */
	int getCols() const
	{
		return nuitrack_GetColorFrameCols(_pimpl);
	}

	/**
	 * @brief Returns the RGB frame ID.
	 */
	uint64_t getID() const
	{
		return nuitrack_GetColorFrameID(_pimpl);
	}

	/**
	 * @brief Returns the frame data.
	 */
	const DataType* getData() const
	{
		return nuitrack_GetColorFrameData(_pimpl);
	}

	/**
	 * @brief Returns timestamp corresponding to the last received RGB frame in microseconds.
	 * @note The exact meaning of this value depends on the RGB provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetColorFrameTimestamp(_pimpl);
	}

private:
	ColorSensorData* _pimpl;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_RGBFRAME_H_ */
