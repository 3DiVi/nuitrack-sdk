// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <memory>
#include <string>

#include "nuitrack/cpp/Export.h"

namespace tdv { namespace nuitrack {

/**
 * @ingroup CommonElements_group
 * @brief Describes an issue identifier.
 */
enum class IssueId
{
	NONE_ISSUE         = 0,
	FRAME_BORDER_ISSUE = 1,
	OCCLUSION_ISSUE    = 2,
	SENSOR_ISSUE       = 3
};

/**
 * @ingroup CommonElements_group
 * @brief Stores general information about a issue.
 *
 * Parent class of all issue classes.
 */
class Issue
{
public:
	static std::string getType() { return "Issue"; }

	virtual std::string getName() const { return _name; }
	IssueId             getId() { return _id; }

	Issue() : _id(IssueId::NONE_ISSUE), _name("Issue") {}
	Issue(IssueId id, const std::string& name) : _id(id), _name(name) {}

	virtual ~Issue() = default;
	using Ptr = std::shared_ptr<Issue>;

protected:
	/** @warning For internal use only. */
	IssueId     _id;
	std::string _name;
};

class OcclusionIssue : public Issue
{
public:
	using Ptr = std::shared_ptr<OcclusionIssue>;
	static std::string getType() { return "OcclusionIssue"; }
	OcclusionIssue() : Issue(IssueId::OCCLUSION_ISSUE, "OcclusionIssue") {}
};


class FrameBorderIssue : public Issue
{
public:
	explicit FrameBorderIssue(bool left = false, bool right = false, bool top = false) :
		Issue(IssueId::FRAME_BORDER_ISSUE, "FrameBorderIssue"), _top(top), _left(left), _right(right) {}

	static std::string getType() { return "FrameBorderIssue"; }

	bool _top = false, _left = false, _right = false;

	using Ptr = std::shared_ptr<FrameBorderIssue>;
	~FrameBorderIssue() override = default;
};


constexpr int SENSOR_ISSUES_STREAM = 9;

class SensorIssue : public Issue
{
public:
	explicit SensorIssue(IssueId issueId = IssueId::SENSOR_ISSUE, const std::string& issueName = "SensorIssue") :
		Issue(issueId, issueName) {}

	static std::string getType() { return "SensorIssue"; }
};


namespace cpp {
class MIDDLEWARE_API IssuesData // TODO: architectural refinement, namespace review
{
public:
	using Ptr = std::shared_ptr<IssuesData>;

	// delete "virtual" keyword if build on Windows fails
	virtual ~IssuesData() = default;

	template<typename T> std::shared_ptr<T> getIssue() const;
	template<typename T> std::shared_ptr<T> getUserIssue(int userId) const;
};
}

}}
