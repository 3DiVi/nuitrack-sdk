// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Stores the spatial orientation as a 3x3 rotation matrix.
 */
struct Orientation
{
	/**
	 * @brief Constructs an orientation with the zero matrix
	 */
	Orientation()
	{
		matrix[0] = 0;
		matrix[1] = 0;
		matrix[2] = 0;
		matrix[3] = 0;
		matrix[4] = 0;
		matrix[5] = 0;
		matrix[6] = 0;
		matrix[7] = 0;
		matrix[8] = 0;
	}

	float matrix[9]; /** @brief Flattened 3x3 rotation matrix. */
};

}
}
