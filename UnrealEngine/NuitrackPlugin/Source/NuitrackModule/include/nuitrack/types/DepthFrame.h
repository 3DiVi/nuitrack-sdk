#ifndef NUITRACK_DEPTHFRAME_H_
#define NUITRACK_DEPTHFRAME_H_

#include "nuitrack/types/Frame.h"
#include "nuitrack/capi/DepthSensor_CAPI.h"

namespace tdv
{
namespace nuitrack
{
/**
* @brief Stores a frame depth map.
* @ingroup DepthSensor_group
*/
class DepthFrame : public Frame<DepthFrame, uint16_t>
{
public:
	/** @warning For internal use only. */
	DepthFrame(DepthSensorData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddDepthSensorDataRef(pimpl);
	}

	virtual ~DepthFrame()
	{
		nuitrack_DestroyDepthSensorData(_pimpl);
	}

	/**
	 * @brief Returns the number of rows in the depth frame.
	 */
	int getRows() const
	{
		return nuitrack_GetDepthFrameRows(_pimpl);
	}

	/**
	 * @brief Returns the number of columns in the depth frame.
	 */
	int getCols() const
	{
		return nuitrack_GetDepthFrameCols(_pimpl);
	}

	/**
	 * @brief Returns the depth frame ID.
	 */
	uint64_t getID() const
	{
		return nuitrack_GetDepthFrameID(_pimpl);
	}

	/**
	 * @brief Returns the frame data.
	 */
	const DataType* getData() const
	{
		return nuitrack_GetDepthFrameData(_pimpl);
	}

	/**
	 * @brief Returns timestamp corresponding to the last received depth frame in microseconds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetDepthFrameTimestamp(_pimpl);
	}

private:
	DepthSensorData* _pimpl;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_DEPTHFRAME_H_ */
