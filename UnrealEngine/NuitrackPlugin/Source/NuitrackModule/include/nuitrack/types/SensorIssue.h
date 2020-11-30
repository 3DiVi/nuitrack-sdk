#ifndef NUITRACK_SENSORISSUE_H_
#define NUITRACK_SENSORISSUE_H_

#include "Issue.h"


namespace tdv
{
namespace nuitrack
{

const int SENSOR_ISSUES_STREAM = 9;

/**
 * @ingroup CommonElements_group
 * @brief Represents the sensor issue.
 */
class SensorIssue : public Issue
{
public:
	/**
	 * @brief Smart pointer to access the SensorIssue instance.
	 */
	typedef std::shared_ptr<SensorIssue> Ptr;
	
	/**
	 * @brief Returns the issue type as a string.
	 */
	static std::string getType()
	{
		static std::string _type = "SensorIssue";
		return _type;
	}
	
	/**
	 * @brief Constructs a sensor issue object from its ID and name
	 */
	SensorIssue(IssueId issueId = SENSOR_ISSUE,
	            std::string issueName = "SensorIssue")
	    : Issue(issueId, issueName)
	{
	}
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_SENSORISSUE_H_ */
