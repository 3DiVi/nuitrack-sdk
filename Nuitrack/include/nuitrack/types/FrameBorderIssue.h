#ifndef NUITRACK_FRAMEBORDERISSUE_H_
#define NUITRACK_FRAMEBORDERISSUE_H_

#include "Issue.h"
#ifdef __aarch64__
#include "nuitrack/types/Export.h"
#endif
namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Represents the frame bodrer issue.
 */
#if defined(ANDROID) && defined(__aarch64__)
class MIDDLEWARE_API FrameBorderIssue : public Issue
#else
class FrameBorderIssue : public Issue
#endif

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

	bool isTop() const
	{
		return _top;
	}
	bool isLeft() const
	{
		return _left;
	}
	bool isRight() const
	{
		return right;
	}
	void setTop(bool isTop)
	{
		this->_top = isTop;
	}
	void setLeft(bool isLeft)
	{
		this->_left = isLeft;
	}
	void setRight(bool isRight)
	{
		this->right = isRight;
	}

#if defined(ANDROID) && defined(__aarch64__)
	virtual ~FrameBorderIssue();
#endif
	/**
	 * @brief Constructs a default frame border issue object.
	 */
	FrameBorderIssue() :
		Issue(FRAME_BORDER_ISSUE, "FrameBorderIssue"),
		_top(false),
		_left(false),
		right(false)
	{}

	/**
	 * @brief Constructs a frame border issue object from its properties.
	 */
	FrameBorderIssue(bool left, bool right, bool top) :
		Issue(FRAME_BORDER_ISSUE, "FrameBorderIssue"),
		_top(top),
		_left(left),
		right(right)
	{}

private:
	bool _top;
	bool _left;
	bool right;
};

}
}

#endif /* NUITRACK_FRAMEBORDERISSUE_H_ */
