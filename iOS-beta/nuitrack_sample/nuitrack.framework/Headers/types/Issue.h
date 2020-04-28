#ifndef NUITRACK_ISSUE_H_
#define NUITRACK_ISSUE_H_

#include <memory>
#include <string>
#include<cstring>

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
		return std::string(_name);
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
		_id(NONE_ISSUE)
	{
		std::string name = "Issue";
		_name = new char[name.length() + 1];
		std::strcpy(_name, name.c_str());
	}

	/**
	 * @brief Constructs an issue object from its identifier and name.
	 */
	Issue(IssueId id, const std::string &name) :
		_id(id)
	{
		_name = new char[name.length() + 1];
		std::strcpy(_name, name.c_str());
	}

	virtual ~Issue()
	{
		deleteString();
	}

	/**
	 * Release the memory occupied by the string representation of the name.
	 */
	void deleteString()
	{
		if(_name)
		{
			delete[] _name;
			_name = NULL;
		}
	}

	/**
	 * @brief Copy constructor.
	 */
	Issue(const Issue& issue)
	{
		copyIssue(issue);
	}

	/**
	 * @brief Overloaded copy assignment operator.
	 */
	void operator=(const Issue& issue)
	{
		copyIssue(issue);
	}

protected:
	/** @warning For internal use only. */
	IssueId _id;
	/** @warning For internal use only. */
	char* _name;

private:
	void copyIssue(const Issue& issue)
	{
		_id = issue._id;

		uint32_t nameSize = 0;
		while(issue._name[nameSize] != '\0')
			nameSize++;

		_name = new char[nameSize + 1];
		for(uint32_t i = 0; i <= nameSize; i++)
			_name[i] = issue._name[i];
	}
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_ISSUE_H_ */
