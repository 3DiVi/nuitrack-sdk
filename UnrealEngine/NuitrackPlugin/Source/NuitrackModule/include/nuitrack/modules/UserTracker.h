#ifndef NUITRACK_USERTRACKER_H_
#define NUITRACK_USERTRACKER_H_

#include <functional>

#include "nuitrack/modules/HeaderOnlyAPI_Module.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/types/UserFrame.h"
#include "nuitrack/capi/UserTracker_CAPI.h"
#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/utils/ExceptionTranslator.h"
#include "nuitrack/utils/CallbackStruct.h"


namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup UserTracker_group
 * @brief Represents the interface to the capabilities of the
 * @ref UserTracker_group "Nuitrack User Tracker" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor UserTracker::create.
 * This instance is called %UserTracker module object.
 * To receive the user tracking data, add an UserTracker::OnUpdate callback
 * to the module object with UserTracker::connectOnUpdate method.
 * To handle events of appearance and disappearance of the user, add UserTracker::OnNewUser
 * and UserTracker::OnLostUser callbacks with UserTracker::connectOnNewUser and
 * UserTracker::connectOnLostUser methods respectively.
 */
class UserTracker : public tdv::nuitrack::HeaderOnlyAPI_Module
{
public:
	/**
	 * @brief Smart pointer to access the UserTracker instance.
	 * @see create
	 */
	typedef std::shared_ptr<UserTracker> Ptr;

	/**
	 * @brief The callback type of the user frame update request.
	 *
	 * @see tdv::nuitrack::UserFrame
	 * @see tdv::nuitrack::User
	 * @see connectOnUpdate
	 */
	typedef std::function<void (UserFrame::Ptr)> OnUpdate;

	typedef void (*OnUpdateRawFunctionPtr)(UserFrame*, UserTracker*);

	/**
	 * @brief The callback type of the new user apearance event.
	 *
	 * This callback will be called if a new user appears in the frame.
	 * This callback receive the ID of the new user.
	 * @see connectOnNewUser
	 */
	typedef std::function<void (int)> OnNewUser;

	typedef void (*OnNewUserRawFunctionPtr)(int, UserTracker*);

	/**
	 * @brief The callback type of the user disapearance event.
	 *
	 * This callback will be called if a user disapears from the frame.
	 * This callback receive the ID of the lost user.
	 * @see connectOnLostUser
	 */
	typedef std::function<void (int)> OnLostUser;

	typedef void (*OnLostUserRawFunctionPtr)(int, UserTracker*);

	/**
	 * @brief Create the UserTracker module object.
	 *
	 * @return Smart pointer to a new UserTracker instance.
	 * @note Do not call this method twice. Instead, use the previously
	 * received UserTracker::Ptr.
	 */
	static UserTracker::Ptr create()
	{
		NuitrackModule* pimpl = NULL;
		ExceptionType exception_code = nuitrack_CreateUserTracker(&pimpl);
		ExceptionTranslator::generateExceptionByErrorCode(exception_code);;
		return std::shared_ptr<UserTracker>(new UserTracker(pimpl));
	}

	/** @warning For internal use only. */
	UserTracker(NuitrackModule* pimpl)
	{
		_pimpl = pimpl;

		_onUpdateCallbackStruct = new CallbackStruct<UserFrame::Ptr>();
		_onNewUserCallbackStruct = new CallbackStruct<int>();
		_onLostUserCallbackStruct = new CallbackStruct<int>();

		_callbackWrapper.setUserTracker(this);
		_callbackWrapper.setOnUpdateAddress(&onUpdateCallback);
		_callbackWrapper.setOnNewUserAddress(&onNewUserCallback);
		_callbackWrapper.setOnLostUserAddress(&onLostUserCallback);

		nuitrack_registerUserTrackerCallback(_pimpl, &_callbackWrapper);
	}

	virtual ~UserTracker()
	{
		nuitrack_DestroyUserTracker(_pimpl);
		destroyUserTracker();
	}

	/**
	 * @brief Add a callback for the user frame update request.
	 *
	 * @param [in] callback Callback to be invoked after the user frame update request.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnUpdate
	 */
	uint64_t connectOnUpdate(const OnUpdate& callback)
	{
		return _onUpdateCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the user frame update request.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnUpdate
	 */
	void disconnectOnUpdate(uint64_t handler)
	{
		_onUpdateCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Add a callback for the new user appearance event.
	 *
	 * @param [in] callback Callback to be invoked after the user frame update request,
	 * if a new user is detected.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnNewUser
	 */
	uint64_t connectOnNewUser(const OnNewUser& callback)
	{
		return _onNewUserCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the new user appearance event.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnNewUser
	 */
	void disconnectOnNewUser(uint64_t handler)
	{
		_onNewUserCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Add a callback for the user disappearance event.
	 *
	 * @param [in] callback Callback to be invoked after the user frame update request,
	 * if a user is found to be missing.
	 * @return Registered callback ID. You can use it to remove the callback.
	 * @see disconnectOnLostUser
	 */
	uint64_t connectOnLostUser(const OnLostUser& callback)
	{
		return _onLostUserCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the user disappearance event.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnLostUser
	 */
	void disconnectOnLostUser(uint64_t handler)
	{
		_onLostUserCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Returns smart pointer to the last avilable UserFrame.
	 */
	UserFrame::Ptr getUserFrame()
	{
		UserTrackerDataPtr data = nuitrack_GetUserTrackerData(_pimpl);
		UserFrame::Ptr newFrame(new UserFrame(data));
		return newFrame;
	}

	/**
	 * @brief Returns last frame processing time in milliseconds.
	 */
	float getProcessingTime() const
	{
		return nuitrack_GetUserTrackerProcessingTime(_pimpl);
	}

	bool canUpdate() const
	{
		return nuitrack_GetNuitrackModuleCanUpdate(_pimpl);
	}

	/**
	 * @brief Returns the last processed data timestamp in microseconds.
	 *
	 * Returns timestamp corresponding to the depth data used
	 * in the last user detection.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp()
	{
		return nuitrack_GetNuitrackModuleTimestamp(_pimpl);
	}

private:

	static void onUpdateCallback(UserTrackerData* userFrameImpl, UserTracker* tracker)
	{
		UserFrame::Ptr newFrame(new UserFrame(userFrameImpl));
		tracker->_onUpdateCallbackStruct->executeAllCallbacks(newFrame);
	}

	static void onNewUserCallback(int usedID, UserTracker* tracker)
	{
		tracker->_onNewUserCallbackStruct->executeAllCallbacks(usedID);
	}
	static void onLostUserCallback(int usedID, UserTracker* tracker)
	{
		tracker->_onLostUserCallbackStruct->executeAllCallbacks(usedID);
	}

	void destroyUserTracker()
	{
		if(_onUpdateCallbackStruct)
			delete _onUpdateCallbackStruct;
		if(_onNewUserCallbackStruct)
			delete _onNewUserCallbackStruct;
		if(_onLostUserCallbackStruct)
			delete _onLostUserCallbackStruct;
	}

	NuitrackModule* _pimpl;

	UserTrackerCallbackWrapper _callbackWrapper;

	CallbackStruct<UserFrame::Ptr>* _onUpdateCallbackStruct;
	CallbackStruct<int>* _onNewUserCallbackStruct;
	CallbackStruct<int>* _onLostUserCallbackStruct;
};

} /* namespace nuitrack */
} /* namespace tdv */


#endif /* NUITRACK_USERTRACKER_H_ */
