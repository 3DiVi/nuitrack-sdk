// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "Issue.h"
#include "nuitrack/types/Export.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Represents the frame border issue.
 */
class FrameBorderIssue : public Issue
{
public:
	/**
	 * @brief Smart pointer to access the FrameBorderIssue instance.
	 */
	typedef std::shared_ptr<FrameBorderIssue> Ptr;

	/**
	 * @brief Returns the issue type as a string.
	 */
	static std::string getType()
	{
		static std::string _type = "FrameBorderIssue";
		return _type;
	}

	bool isTop() const { return _top; }
	bool isLeft() const { return _left; }
	bool isRight() const { return _right; }
	void setTop(bool isTop) { this->_top = isTop; }
	void setLeft(bool isLeft) { this->_left = isLeft; }
	void setRight(bool isRight) { this->_right = isRight; }

	~FrameBorderIssue() override = default;

	/**
	 * @brief Constructs a frame border issue object from its properties.
	 */
	FrameBorderIssue(bool left = false, bool right = false, bool top = false) : Issue(FRAME_BORDER_ISSUE, "FrameBorderIssue"),
		_top(top), _left(left), _right(right) {}

private:
	bool _top = false;
	bool _left = false;
	bool _right = false;
};

}
}
