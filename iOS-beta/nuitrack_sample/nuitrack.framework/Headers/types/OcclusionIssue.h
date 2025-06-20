// Copyright 3DiVi 2024, Inc. All Rights Reserved.

#pragma once

#include "Issue.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Represents the occlusion issue.
 */
class OcclusionIssue : public Issue
{
public:
	/**
	 * @brief Smart pointer to access the OcclusionIssue instance.
	 */
	typedef std::shared_ptr<OcclusionIssue> Ptr;

	/**
	 * @brief Returns the issue type as a string.
	 */
	static std::string getType()
	{
		static std::string _type = "OcclusionIssue";
		return _type;
	}

	/**
	 * @brief Constructs a default occlusion issue object.
	 */
	OcclusionIssue() :
		Issue(OCCLUSION_ISSUE, "OcclusionIssue")
	{
	}
};

} /* namespace nuitrack */
} /* namespace tdv */
