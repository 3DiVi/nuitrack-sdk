#ifndef NUITRACK_SKELETONTRACKER_H_
#define NUITRACK_SKELETONTRACKER_H_

#include <functional>

#include "nuitrack/modules/HeaderOnlyAPI_Module.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/types/SkeletonData.h"
#include "nuitrack/capi/SkeletonTracker_CAPI.h"
#include "nuitrack/utils/ExceptionTranslator.h"
#include "nuitrack/utils/CallbackStruct.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup SkeletonTracker_group
 * @brief Represents the interface to the capabilities of the
 * @ref SkeletonTracker_group "Nuitrack Skeleton Tracker" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor SkeletonTracker::create.
 * This instance is called %SkeletonTracker module object.
 * To receive the skeleton tracking data, add an SkeletonTracker::OnUpdate callback
 * to the module object with SkeletonTracker::connectOnUpdate method.
 * To handle events of appearance and disappearance of an active user,
 * add SkeletonTracker::OnNewUser and SkeletonTracker::OnLostUser callbacks
 * with SkeletonTracker::connectOnNewUser and SkeletonTracker::connectOnLostUser
 * methods respectively.
 */
class SkeletonTracker : public tdv::nuitrack::HeaderOnlyAPI_Module
{
public:
	/**
	 * @brief Smart pointer to access the SkeletonTracker instance.
	 * @see create
	 */
	typedef std::shared_ptr<SkeletonTracker> Ptr;

	/**
	 * @brief The callback type of the skeleton data update request.
	 *
	 * This callback receive a smart pointer to SkeletonData, which contains @ref Skeleton array.
	 * @see tdv::nuitrack::SkeletonData
	 * @see tdv::nuitrack::Skeleton
	 * @see connectOnUpdate
	 */
	typedef std::function<void (SkeletonData::Ptr)> OnUpdate;
	typedef void (*OnUpdateRawFunctionPtr)(SkeletonData*, SkeletonTracker*);

	/**
	 * @brief The callback type of the new active user apearance event.
	 *
	 * This callback will be called if a new active user appears.
	 * This callback receive the ID of the new active user.
	 * @see connectOnNewUser
	 */
	typedef std::function<void (SkeletonTracker::Ptr, int)> OnNewUser;
	typedef void (*OnNewUserRawFunctionPtr)(SkeletonTracker*, int);

	/**
	 * @brief The callback type of the active user disapearance event.
	 *
	 * This callback will be called if an active user disapears.
	 * This callback receive the ID of the lost active user.
	 * @see connectOnLostUser
	 */
	typedef std::function<void (SkeletonTracker::Ptr, int)> OnLostUser;
	typedef void (*OnLostUserRawFunctionPtr)(SkeletonTracker*, int);

	/**
	 * @brief Create the SkeletonTracker module object.
	 *
	 * @return Smart pointer to a new SkeletonTracker instance.
	 * @note Do not call this method twice. Instead, use the previously
	 * received SkeletonTracker::Ptr.
	 */
	static SkeletonTracker::Ptr create()
	{
		NuitrackModule* pimpl = NULL;
		ExceptionType errorCode = nuitrack_CreateSkeletonTracker(&pimpl);
		ExceptionTranslator::generateExceptionByErrorCode(errorCode);
		return std::shared_ptr<SkeletonTracker>(new SkeletonTracker(pimpl));
	}

	/** @warning For internal use only. */
	SkeletonTracker(NuitrackModule* pimpl)
	{
		_pimpl = pimpl;
		_isCopy = 0;

		_onUpdateCallbackStruct = new CallbackStruct<SkeletonData::Ptr>();
		_onNewUserCallbackStruct = new CallbackStruct2p<SkeletonTracker::Ptr, int>();
		_onLostUserCallbackStruct = new CallbackStruct2p<SkeletonTracker::Ptr, int>();

		_callbackWrapper.setSkeletonTracker(this);
		_callbackWrapper.setOnUpdateAddress(&onUpdateCallback);
		_callbackWrapper.setOnNewUserAddress(&onNewUserCallback);
		_callbackWrapper.setOnLostUserAddress(&onLostUserCallback);
		nuitrack_registerSkeletonTrackerCallback(_pimpl, &_callbackWrapper);
	}

	/** @warning For internal use only. */
	SkeletonTracker(NuitrackModule* pimpl, 	CallbackStruct<SkeletonData::Ptr>* onUpdateCallbackStruct,
									CallbackStruct2p<SkeletonTracker::Ptr, int>* onNewUserCallbackStruct,
									CallbackStruct2p<SkeletonTracker::Ptr, int>* onLostUserCallbackStruct)
	{
		_pimpl = pimpl;
		_isCopy = 1;

		_onUpdateCallbackStruct = onUpdateCallbackStruct;
		_onNewUserCallbackStruct = onNewUserCallbackStruct;
		_onLostUserCallbackStruct = onLostUserCallbackStruct;
	}

	virtual ~SkeletonTracker()
	{
		if(_isCopy == 0)
		{
			nuitrack_DestroySkeletonTracker(_pimpl);
			destroySkeletonTracker();
		}
	}

	/**
	 * @brief Add a callback for the skeleton data update request.
	 *
	 * @param [in] callback Callback to be invoked after the skeleton data update request.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnUpdate
	 */
	uint64_t connectOnUpdate(const OnUpdate& callback)
	{
		return _onUpdateCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the skeleton data update request.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnUpdate
	 */
	void disconnectOnUpdate(uint64_t handler)
	{
		_onUpdateCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Add a callback for the new active user appearance event.
	 *
	 * @param [in] callback Callback to be invoked after the skeleton data update request,
	 * if a new active user is appeared.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnNewUser
	 */
	uint64_t connectOnNewUser(const OnNewUser& callback)
	{
		return _onNewUserCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the new active user appearance event.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnNewUser
	 */
	void disconnectOnNewUser(uint64_t handler)
	{
		_onNewUserCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Add a callback for the active user disappearance event.
	 *
	 * @param [in] callback Callback to be invoked after the skeleton data update request,
	 * if an active user is found to be missing.
	 * @return Registered callback ID. You can use it to remove the callback.
	 * @see disconnectOnLostUser
	 */
	uint64_t connectOnLostUser(const OnLostUser& callback)
	{
		return _onLostUserCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the active user disappearance event.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnLostUser
	 */
	void disconnectOnLostUser(uint64_t handler)
	{
		_onLostUserCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Set maximum number of users for tracking.
	 *
	 * @note The function supports tracking from 0 to 6 users.
	 * By default, the skeleton of 2 users is tracked.
	 * Tracking of more than 2 users may lead to performance loss.
	 * @param [in] numUsers Maximum active user number to be set.
	 */
	void setNumActiveUsers(int numUsers)
	{
		nuitrack_SetNumActiveUsers(_pimpl, numUsers);
	}

	/**
	 * @brief Returns true if auto tracking is enabled, false otherwise.
	 * @note The default value is determined by the %Nuitrack config file.
	 * @see setAutoTracking
	 */
	bool isAutoTracking() const
	{
		return nuitrack_IsAutoTracking(_pimpl);
	}

	/**
	 * @brief Set user skeleton auto tracking state.
	 *
	 * Call setAutoTracking(true) to enable auto tracking.
	 * Call setAutoTracking(false) to disable auto tracking.
	 *
	 * When auto tracking is enabled, tracking of the skeleton of a user begins
	 * immediately when the user appears in the frame. Otherwise, you must manually
	 * start tracking of the user's skeleton.
	 *
	 * @param [in] tracking Auto tracking state to be set.
	 * @see startTracking
	 * @see connectOnNewUser
	 * @see isAutoTracking
	 */
	void setAutoTracking(bool tracking)
	{
		nuitrack_SetAutoTracking(_pimpl, tracking);
	}

	/**
	 * @brief Start tracking of a user.
	 *
	 * @param [in] userID ID of user which tracking should be started.
	 * @see stopTracking
	 * @see isTracking
	 */
	void startTracking(int userID)
	{
		nuitrack_StartTracking(_pimpl, userID);
	}

	/**
	 * @brief Stop tracking of a user.
	 *
	 * @param [in] userID ID of user which tracking should be stopped.
	 * @see startTracking
	 * @see isTracking
	 */
	void stopTracking(int userID)
	{
		nuitrack_StopTracking(_pimpl, userID);
	}

	/**
	 * @brief Get user tracking state.
	 *
	 * @return True if user is being tracked, false otherwise.
	 * @see startTracking
	 * @see stopTracking
	 */
	bool isTracking(int userID)
	{
		return nuitrack_IsTracking(_pimpl, userID);
	}

	/**
	 * @brief Returns smart pointer to the last avilable SkeletonData.
	 */
	SkeletonData::Ptr getSkeletons()
	{
		SkeletonTrackerDataPtr data = nuitrack_GetSkeletonTrackerData(_pimpl);
		SkeletonData::Ptr newFrame(new SkeletonData(data));
		return newFrame;
	}

	/**
	 * @brief Returns last skeleton data processing time in milliseconds.
	 */
	float getProcessingTime() const
	{
		return nuitrack_GetSkeletonTrackerProcessingTime(_pimpl);
	}

	bool canUpdate() const
	{
		return nuitrack_GetNuitrackModuleCanUpdate(_pimpl);
	}

	/**
	 * @brief Returns the last processed data timestamp in microseconds.
	 *
	 * Returns timestamp corresponding to the last estimation of the skeletal pose.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp()
	{
		return nuitrack_GetNuitrackModuleTimestamp(_pimpl);
	}

protected:
	/** @warning For internal use only. */
	static void onUpdateCallback(SkeletonTrackerData* frame, SkeletonTracker* tracker)
	{
		SkeletonData::Ptr newFrame(new SkeletonData(frame));

		tracker->_onUpdateCallbackStruct->executeAllCallbacks(newFrame);
	}

	/** @warning For internal use only. */
	static void onNewUserCallback(SkeletonTracker* tracker, int usedID)
	{

		SkeletonTracker::Ptr ptr = SkeletonTracker::Ptr(
				new SkeletonTracker(tracker->_pimpl, tracker->_onUpdateCallbackStruct,
					tracker->_onNewUserCallbackStruct, tracker->_onLostUserCallbackStruct));

		tracker->_onNewUserCallbackStruct->executeAllCallbacks(ptr, usedID);
	}

	/** @warning For internal use only. */
	static void onLostUserCallback( SkeletonTracker* tracker, int usedID)
	{

		SkeletonTracker::Ptr ptr = SkeletonTracker::Ptr(
				new SkeletonTracker(tracker->_pimpl, tracker->_onUpdateCallbackStruct,
					tracker->_onNewUserCallbackStruct, tracker->_onLostUserCallbackStruct));

		tracker->_onLostUserCallbackStruct->executeAllCallbacks(ptr, usedID);
	}

	/** @warning For internal use only. */
	void destroySkeletonTracker()
	{
		if(_onUpdateCallbackStruct)
			delete _onUpdateCallbackStruct;
		if(_onNewUserCallbackStruct)
			delete _onNewUserCallbackStruct;
		if(_onLostUserCallbackStruct)
			delete _onLostUserCallbackStruct;
	}

	NuitrackModule* _pimpl; ///< @warning For internal use only.
	int8_t _isCopy; ///< @warning For internal use only.

	CallbackStruct<SkeletonData::Ptr>* _onUpdateCallbackStruct; ///< @warning For internal use only.
	CallbackStruct2p<SkeletonTracker::Ptr, int>* _onNewUserCallbackStruct; ///< @warning For internal use only.
	CallbackStruct2p<SkeletonTracker::Ptr, int>* _onLostUserCallbackStruct; ///< @warning For internal use only.

	SkeletonTrackerCallbackWrapper _callbackWrapper; ///< @warning For internal use only.
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_SKELETONTRACKER_H_ */
