#ifndef NUITRACK_OUTPUTMODE_H_
#define NUITRACK_OUTPUTMODE_H_

namespace tdv
{
namespace nuitrack
{

/**
* @ingroup DepthSensor_group
* @brief Stores sensor data properties.
*/
struct OutputMode
{
	/**
	 * @brief Count of frames transferred per second.
	 */
	int fps;

	/**
	 * @brief X resolution (frame width).
	 */
	int xres;

	/**
	 * @brief Y resolution (frame height).
	 */
	int yres;

	/**
	 * @brief Horizontal field of view in radians.
	 */
	float hfov;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_OUTPUTMODE_H_ */
