#ifndef NUITRACK_HANDTRACKERDATA_H_
#define NUITRACK_HANDTRACKERDATA_H_

#include "nuitrack/types/ObjectData.h"
#include "nuitrack/types/Hand.h"
#include "nuitrack/capi/HandTracker_CAPI.h"
#include <vector>

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup HandTracker_group
 * @brief Stores hand tracking results related to a specific point in time.
 */
class HandTrackerData : public ObjectData<HandTrackerData>
{
public:
	/** @warning For internal use only. */
	HandTrackerData(HandTrackerDataInner* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddHandTrackerDataRef(_pimpl);
	}

	virtual ~HandTrackerData()
	{
		nuitrack_DestroyHandTrackerData(_pimpl);
	}

	/**
	 * @brief Returns the data timestamp in microseconds.
	 *
	 * The timestamp characterizes the time point to which the hand
	 * tracking data corresponds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetHandTrackerDataTimestamp(_pimpl);
	}

    /**
     * @brief Returns the number of users handled by the hand tracker.
     */
    int getNumUsers() const
    {
    	return nuitrack_HandTrackerGetNumUsers(_pimpl);
    }

    /**
     * @brief Returns information about the hands of the tracked users.
     *
     * @return User hand information in the form of array of the UserHands structures.
     */
    const std::vector<UserHands> getUsersHands() const
	{
    	HandTrackerDataInner* dataHolder = _pimpl;

    	size_t numUsers = nuitrack_HandTrackerGetNumUsers(dataHolder);

    	std::vector<UserHands> userHands;

    	int userId = 0;
    	tdv::nuitrack::Hand leftHand;
    	tdv::nuitrack::Hand rightHand;
    	for(size_t i = 0; i < numUsers; i++)
    	{
    		nuitrack_HandTrackerGetUserHands(dataHolder, i, &userId, &leftHand, &rightHand);
    		UserHands newHand;
    		newHand.userId = userId;
    		newHand.leftHand = Hand::Ptr(new tdv::nuitrack::Hand(leftHand));
    		newHand.rightHand = Hand::Ptr(new tdv::nuitrack::Hand(rightHand));
    		userHands.push_back(newHand);
    	}

    	return userHands;
	}

private:
    HandTrackerDataInner* _pimpl;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_HANDTRACKERDATA_H_ */
