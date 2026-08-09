// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/cpp/Types.h"
#include "nuitrack/cpp/ObjectData.h"

namespace tdv { namespace nuitrack {

	/**
	* @brief Contents all available skeletons with timestamp.
	* @ingroup SkeletonTracker_group
	*/
class SkeletonData: public ObjectData<SkeletonData>
{
public:
	~SkeletonData() override = default;

	/**
	 * @brief Get current number of skeletons.
	 * @return Number of skeletons.
	 */
	virtual int getNumSkeletons() const = 0;

	/**
	 * @brief Get current user skeletons.
	 * @return Skeletons.
	 */
	virtual std::vector<Skeleton> getSkeletons() const = 0;
};

}}
