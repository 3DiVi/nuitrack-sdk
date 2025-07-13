// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

namespace tdv { namespace nuitrack {

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

	Intrinsics(float fx = -1.0f, float fy = -1.0f, float cx = -1.0, float cy = -1.0f):
		fx(fx), fy(fy), cx(cx), cy(cy) {}
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

	OutputMode(int fps = -1, int xres = -1, int yres = -1, float hfov = -1.0f, Intrinsics intr = Intrinsics()):
		fps(fps), xres(xres), yres(yres), hfov(hfov), intrinsics(intr) {}
};

}}
