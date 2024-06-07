#ifndef NUITRACK_GESTUREDATA_H_
#define NUITRACK_GESTUREDATA_H_

#include "nuitrack/types/ObjectData.h"
#include "nuitrack/types/Gesture.h"
#include "nuitrack/capi/GestureRecognizer_CAPI.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup GestureRecognizer_group
 * @brief Stores the results of gesture estimation.
 */
class GestureData: public ObjectData<GestureData>
{
public:
	/** @warning For internal use only. */
	GestureData(GestureRecognizerData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddGestureRecognizerDataRef(pimpl);
	}

	virtual ~GestureData()
	{
		nuitrack_DestroyGestureRecognizerData(_pimpl);
	}

	/**
	 * @brief Returns the data timestamp in microseconds.
	 *
	 * The timestamp characterizes the time point to which the gesture
	 * data corresponds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetUserGesturesTimestamp(_pimpl);
	}

	/**
	 * @brief Returns the number of gestures detected.
	 */
	int getNumGestures() const
	{
		return nuitrack_GetUserGesturesNumGestures(_pimpl);
	}

	/**
	 * @brief Returns descriptions of detected gestures.
	 *
	 * @return Gesture information in the form of array of the Gesture structures.
	 */
	const std::vector<Gesture> getGestures() const
	{
		std::vector<Gesture> gesturesVector;

		GestureRecognizerData* dataHolder  = _pimpl;


		size_t numUsers = nuitrack_GetUserGesturesNumGestures(dataHolder);

		for(size_t i = 0; i < numUsers; i++)
		{
			Gesture g;
			nuitrack_GetUserGesture(dataHolder, i, &g);
			gesturesVector.push_back(g);
		}

		return gesturesVector;
	}

private:
	GestureRecognizerData* _pimpl;
};


/**
 * @ingroup GestureRecognizer_group
 * @brief Stores the results of user state estimation.
 */
class UserStateData : public ObjectData<UserStateData>
{
public:
	/** @warning For internal use only. */
	UserStateData(UsersStateChanges* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddUsersStateChangesRef(pimpl);
	}

	virtual ~UserStateData()
	{
		nuitrack_DestroyUsersStateChanges(_pimpl);
	}

	/**
	 * @brief Returns the number of user states detected.
	 */
	int getNumUserStates() const
	{
		return nuitrack_GetNumUsersStateChanges(_pimpl);
	}

	/**
	 * @brief Returns the data timestamp in microseconds.
	 *
	 * The timestamp characterizes the time point to which the user state
	 * data corresponds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetUsersStateChangesTimestamp(_pimpl);
	}

	/**
	 * @brief Returns descriptions of detected states of users.
	 *
	 * @return User state information in the form of array of the UserState structures.
	 */
	const std::vector<UserState> getUserStates() const
	{
		std::vector<UserState> usersVector;

		UsersStateChanges* dataHolder = _pimpl;

		size_t numUsers = nuitrack_GetNumUsersStateChanges(dataHolder);

		for(size_t i = 0; i < numUsers; i++)
		{
			UserState g;
			nuitrack_GetUserStateChange(dataHolder, i, &g);
			usersVector.push_back(g);
		}

		return usersVector;
	}

private:
	UsersStateChanges* _pimpl;
};


/**
 * @ingroup GestureRecognizer_group
 * @brief Stores the results of estimation of the state of gestures
 * for every tracked user.
 */
class UserGesturesStateData: public ObjectData<UserGesturesStateData>
{
public:
	/** @warning For internal use only. */
	UserGesturesStateData(GestureRecognizerUserGesturesStateData* pimpl)
	{
		_pimpl = pimpl;
		nuitrack_AddUsersStateDataRef(pimpl);
	}

	virtual ~UserGesturesStateData()
	{
		nuitrack_DestroyUsersStateData(_pimpl);
	}

	/**
	 * @brief Returns the number of tracked users.
	 */
	int getNumUsers() const
	{
		return nuitrack_GetNumUsersGestures(_pimpl);
	}

	/**
	 * @brief Returns the data timestamp in microseconds.
	 *
	 * The timestamp characterizes the time point to which the gesture state
	 * data corresponds.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	uint64_t getTimestamp() const
	{
		return nuitrack_GetUsersGesturesStateTimestamp(_pimpl);
	}

	/**
	 * @brief Returns information about the gestures of the tracked users.
	 *
	 * @return User gesture information in the form of array of the UserGesturesState structures.
	 */
	const std::vector<UserGesturesState> getUserGesturesStates() const
	{
		std::vector<UserGesturesState> usersVector;

		GestureRecognizerUserGesturesStateData* dataHolder = _pimpl;


		int numUsers = nuitrack_GetNumUsersGestures(dataHolder);

		for(int i = 0; i < numUsers; i++)
		{
			UserGesturesState ugs;
			UserGesturesState ugsTemp;

			nuitrack_GetUserStateData(dataHolder, i, &ugsTemp);
			ugs.userId = ugsTemp.userId;
			ugs.state = ugsTemp.state;

			int numGestures = nuitrack_GetNumUserGestureState(dataHolder, i);
			for(int j = 0; j < numGestures; j++)
			{
				GestureState gs;
				nuitrack_GetUserGestureState(dataHolder, i, j, &gs);
				ugs.gestures.push_back(gs);
			}

			usersVector.push_back(ugs);
		}

		return usersVector;
	}

private:
	GestureRecognizerUserGesturesStateData* _pimpl;
};

} // namespace nuitrack
} // namespace tdv

#endif /* NUITRACK_GESTUREDATA_H_ */
