// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/types/BoundingBox.h"
#include "nuitrack/types/Vector3.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup UserTracker_group
 * @brief Stores information about a detected user.
 */
struct User
{
	/**
	 * @brief %User identifier.
	 */
	int id;

	/**
	 * @brief Center of mass in projective coordinates.
	 */
	Vector3 proj;

	/**
	 * @brief Center of mass in real coordinates.
	 */
	Vector3 real;

	/**
	 * @brief Bounding box
	 * 
	 * Face positions are given in normalized floating-point coordinates in range [0;1].
	 */
	BoundingBox box;

	/**
	 * @brief Occlusion rate in range [0;1]
	 */
	float occlusion;
};

} /* namespace nuitrack */
} /* namespace tdv */
