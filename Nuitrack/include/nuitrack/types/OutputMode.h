// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

namespace tdv
{
namespace nuitrack
{

/**
* @ingroup DepthSensor_group
* @brief Stores sensor intrinsic values.
*/
struct Intrinsics
{
	/**
	 * @brief Focal length in X direction
	 */
	float fx;

	/**
	 * @brief Focal length in Y direction
	 */
	float fy;

	/**
	 * @brief Optical center abscissa
	 */
	float cx;

	/**
	 * @brief Optical center ordinate
	 */
	float cy;
};

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

	/**
	 * @brief Sensor intrinsics for current xres, yres.
	 */
	Intrinsics intrinsics;
};

} /* namespace nuitrack */
} /* namespace tdv */
