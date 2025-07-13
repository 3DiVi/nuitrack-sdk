// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/types/BoundingBox.h"
#include "nuitrack/types/Vector3.h"

#include <memory>

namespace tdv { namespace nuitrack {
/**
 * @ingroup UserTracker_group
 * @brief Stores information about a detected user.
 */
struct User
{
	using Ptr = std::shared_ptr<User>;

	int id; /** @brief %User identifier. */

	Vector3 proj; /** @brief Center of mass in projective coordinates. */
	Vector3 real; /** @brief Center of mass in real coordinates. */

	BoundingBox box; /** @brief Bounding box. Face positions are given in normalized floating-point coordinates in range [0;1]. */

	float occlusion; /** @brief Occlusion rate in range [0;1] */
};

}}
