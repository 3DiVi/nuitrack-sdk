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
	float fx; /** @brief Focal length in X direction */
	float fy; /** @brief Focal length in Y direction */

	float cx; /** @brief Optical center abscissa */
	float cy; /** @brief Optical center ordinate */
};

/**
* @ingroup DepthSensor_group
* @brief Stores sensor data properties.
*/
struct OutputMode
{
	int fps; /** @brief Count of frames transferred per second. */

	int xres; /** @brief X resolution (frame width). */
	int yres; /** @brief Y resolution (frame height). */

	float hfov; /** @brief Horizontal field of view in radians. */

	Intrinsics intrinsics; /** @brief Sensor intrinsics for current xres, yres. */
};

} /* namespace nuitrack */
} /* namespace tdv */
