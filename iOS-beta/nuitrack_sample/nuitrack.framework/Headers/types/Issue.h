#ifndef NUITRACK_ISSUE_H_
#define NUITRACK_ISSUE_H_

#include <memory>
#include <string>
#include <cstring>

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Describes an issue identifier.
 */
enum IssueId
{
	NONE_ISSUE = 0,
	FRAME_BORDER_ISSUE = 1,
	OCCLUSION_ISSUE = 2,
	SENSOR_ISSUE = 3
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
	/**
	 * @brief Smart pointer to access the Issue instance.
	 */
	typedef std::shared_ptr<Issue> Ptr;

	/**
	 * @brief Returns the issue type as a string.
	 */
	static std::string getType()
	{
		static std::string _type = "Issue";
		return _type;
	}

	/**
	 * @brief Returns the issue name.
	 */
	virtual std::string getName() const
	{
		return _name;
	}

	/**
	 * @brief Returns the issue identifier.
	 */
	IssueId getId()
	{
		return _id;
	}

	/**
	 * @brief Constructs a default issue.
	 */
	Issue() :
		_id(NONE_ISSUE),
		_name("Issue")
	{
	}

	/**
	 * @brief Constructs an issue object from its identifier and name.
	 */
	Issue(IssueId id, const std::string &name) :
		_id(id),
		_name(name)
	{
	}

	virtual ~Issue()
	{
	}

protected:
	/** @warning For internal use only. */
	IssueId _id;
	/** @warning For internal use only. */
	std::string _name;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_ISSUE_H_ */
