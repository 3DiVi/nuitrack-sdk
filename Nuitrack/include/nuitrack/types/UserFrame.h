#ifndef NUITRACK_USERFRAME_H_
#define NUITRACK_USERFRAME_H_

#include <vector>

#include "nuitrack/types/Frame.h"
#include "nuitrack/types/User.h"
#include "nuitrack/capi/UserTracker_CAPI.h"

namespace tdv
{
namespace nuitrack
{

/**
 * @ingroup UserTracker_group
 * @brief Represents a user map with information about the floor.
 *
 * Each UserFrame element stores the ID of a user to which corresponding frame pixel belongs.
 *
 * Additional information about detected users can be accessed trough UserFrame::getUsers.
 *
 * The floor is represented in the form of a plane: as the point and the normal vector.
 * This properties can be accessed via UserFrame::getFloor and
 * UserFrame::getFloorNormal respectively.
 */
class UserFrame : public Frame<UserFrame, uint16_t>
{
public:
	/** @warning For internal use only. */
	UserFrame(UserTrackerData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddUserTrackerDataRef(pimpl);
	}

	virtual ~UserFrame()
	{
		nuitrack_DestroyUserTrackerData(_pimpl);
	}

	/**
	 * @brief Returns additional information about detected users.
	 *
	 * @return Detected user properties in the form of array of the User structures.
	 */
	const std::vector<User> getUsers() const
	{
		UserTrackerData* dataHolder = _pimpl;

		std::vector<User> usersVector;

		size_t numUsers = nuitrack_GetUserFrameNumUsers(dataHolder);

		for(size_t i = 0; i < numUsers; i++)
		{
			User user;
			nuitrack_GetUserFrameUser(dataHolder, i, &user);
			usersVector.push_back(user);
		}

		return usersVector;
	}

	/**
	 * @brief Returns the number of rows in the user frame.
	 */
	int getRows() const
	{
		return nuitrack_GetUserFrameRows(_pimpl);
	}

	/**
	 * @brief Returns the number of columns in the user frame.
	 */
	int getCols() const
	{
		return nuitrack_GetUserFrameCols(_pimpl);
	}

	/**
	 * @brief Returns the user frame ID.
	 */
	uint64_t getID() const
	{
		return nuitrack_GetUserFrameID(_pimpl);
	}

	/**
	 * @brief Returns the user frame data.
	 */
	const DataType* getData() const
	{
		return nuitrack_GetUserFrameData(_pimpl);
	}

	uint64_t getTimestamp() const
	{
		return nuitrack_GetUserFrameTimestamp(_pimpl);
	}

	/**
	 * @brief Get point of floor.
	 *
	 * @return floor point.
	 */
	const Vector3 getFloor() const
	{
		Vector3 floor;
		nuitrack_GetUserFrameFloor(_pimpl, &floor);
		return floor;
	}

	/**
	 * @brief Get normal of floor.
	 *
	 * @return floor normal.
	 */
	const Vector3 getFloorNormal() const
	{
		Vector3 floorNormal;
		nuitrack_GetUserFrameFloorNormal(_pimpl, &floorNormal);
		return floorNormal;
	}

private:
	UserTrackerData* _pimpl;

};


}
}

#endif /* NUITRACK_USERFRAME_H_ */
