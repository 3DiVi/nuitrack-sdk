#ifndef NUITRACK_MIDDLEWARE_ISSUES_DATA_H_
#define NUITRACK_MIDDLEWARE_ISSUES_DATA_H_

#include <map>
#include <memory>
#include <string.h>

#include "nuitrack/capi/IssueTracker_CAPI.h"
#include "nuitrack/types/ObjectData.h"
#include "nuitrack/types/Issue.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/types/FrameBorderIssue.h"
#include "nuitrack/types/OcclusionIssue.h"
#include "nuitrack/types/SensorIssue.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup CommonElements_group
 * @brief Stores results of issue detection.
 */
class IssuesData
{
public:
	/** @warning For internal use only. */
	IssuesData(IssueTrackerData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddIssueTrackerDataRef(pimpl);
	}

	virtual ~IssuesData()
	{
		nuitrack_DestroyIssueTrackerData(_pimpl);
	}

	/**
	 * @brief Smart pointer to access the IssuesData instance.
	 */
	typedef std::shared_ptr<IssuesData> Ptr;

	/**
	 * @brief Returns information about sensor related issue detected.
	 *
	 * @tparam T A data type that stores information about the requested issue.
	 */
	template<typename T> std::shared_ptr<T> NUITRACK_LOCAL getIssue() const
	{
		std::shared_ptr<T> result;
		if(strcmp(T::getType().c_str(), "SensorIssue") == 0)
		{
			Issue* issue = NULL;

			const int bufferSize = 300;
			std::string buffer;
			buffer.resize(bufferSize);
			if(nuitrack_GetSensorIssue(_pimpl, (char *)buffer.c_str(), bufferSize))
			{
				buffer.resize(strlen(buffer.c_str()));
				issue = new SensorIssue(SENSOR_ISSUE, buffer);
			}

			result = std::shared_ptr<T>(static_cast<T*>(issue));
		}
		return result;
	}

	/**
	 * @brief Returns information about user related issue detected.
	 *
	 * @tparam T A data type that stores information about the requested issue.
	 * @param userId ID of the user of interest.
	 */
	template<typename T> std::shared_ptr<T> NUITRACK_LOCAL getUserIssue(int userId) const
	{
		std::shared_ptr<T> result;

		if(strcmp(T::getType().c_str(), "OcclusionIssue") == 0)
		{
			bool occlusion = nuitrack_GetOcclusionIssue(_pimpl, userId);
			Issue* issue = NULL;
			if(occlusion)
			{
				issue = new OcclusionIssue();
			}
			result = std::shared_ptr<T>(static_cast<T*>(issue));
		}

		if(strcmp(T::getType().c_str(), "FrameBorderIssue") == 0)
		{
			bool left = false;
			bool right = false;
			bool top = false;
			nuitrack_GetFrameBorderIssue(_pimpl, userId, &left, &right, &top);
			Issue* issue = NULL;
			if(left || right || top)
			{
				issue = new FrameBorderIssue(left, right, top);
			}
			result = std::shared_ptr<T>(static_cast<T*>(issue));
		}
		return result;
	}

protected:
	/** @warning For internal use only. */
	IssueTrackerData* _pimpl;
};


} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_MIDDLEWARE_ISSUES_DATA_H_ */
