#ifndef NUITRACK_SKELETONDATA_H_
#define NUITRACK_SKELETONDATA_H_

#include <memory>

#include "nuitrack/types/Skeleton.h"
#include "nuitrack/types/ObjectData.h"
#include "nuitrack/capi/SkeletonTracker_CAPI.h"

namespace tdv
{
namespace nuitrack
{

	/**
	* @ingroup SkeletonTracker_group
	* @brief Stores the data of all available skeletons at a certain point in time.
	*/
class SkeletonData: public ObjectData<SkeletonData>
{
public:
	SkeletonData(SkeletonTrackerData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddSkeletonTrackerDataRef(pimpl);
	}

	virtual ~SkeletonData()
	{
		nuitrack_DestroySkeletonTrackerData(_pimpl);
	}

	/**
	 * @brief Get current number of skeletons.
	 *
	 * @return Number of skeletons.
	 */
	int getNumSkeletons() const
	{
		return nuitrack_GetNumUsers(_pimpl);
	}

	/**
	 * @brief Get current user skeletons.
	 *
	 * @return Skeletons.
	 */
	const std::vector<Skeleton> getSkeletons() const
	{

		SkeletonTrackerData* dataHolder = _pimpl;

		std::vector<Skeleton> usersVector;

		size_t numUsers = nuitrack_GetNumUsers(dataHolder);
		size_t maxJoints = 25;

		for (size_t i = 0; i < numUsers; i++)
		{
			Skeleton skeleton;
			int id = nuitrack_GetSkeletonID(dataHolder, i);
			skeleton.id = id;

			for (size_t j = 0; j < maxJoints; j++)
			{
				Joint joint;
				nuitrack_GetSkeletonJoint(dataHolder, i, (JointType)j, &joint);
				skeleton.joints.push_back(joint);
			}

			usersVector.push_back(skeleton);
		}

		return usersVector;
	}

	/**
	 * @brief Returns the data timestamp in microseconds.
	 *
	 * The timestamp characterizes the time point to which the skeleton
	 * data corresponds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetSkeletonTrackerTimestamp(_pimpl);
	}

private:
	SkeletonTrackerData* _pimpl;
};

}
}

#endif /* NUITRACK_SKELETONDATA_H_ */
