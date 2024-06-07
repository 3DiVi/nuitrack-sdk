#ifndef NUITRACK_GESTURE_RECOGNIZER_H_
#define NUITRACK_GESTURE_RECOGNIZER_H_

#include <functional>

#include "nuitrack/modules/HeaderOnlyAPI_Module.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/types/GestureData.h"
#include "nuitrack/capi/GestureRecognizer_CAPI.h"
#include "nuitrack/utils/ExceptionTranslator.h"
#include "nuitrack/utils/CallbackStruct.h"

namespace tdv
{
namespace nuitrack
{

/**
 * @ingroup GestureRecognizer_group
 * @brief Represents the interface to the capabilities of the
 * @ref GestureRecognizer_group "Nuitrack Gesture Recognizer" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor GestureRecognizer::create.
 * This instance is called %GestureRecognizer module object.
 * To receive the gesture progress estimation data, add an GestureRecognizer::OnUpdate callback
 * to the module object with GestureRecognizer::connectOnUpdate method.
 * To handle event of user state change, add GestureRecognizer::OnUserStateChange callback
 * with SkeletonTracker::connectOnUserStateChange method.
 * To handle event of new gesture detection, add GestureRecognizer::OnNewGestures callback
 * with SkeletonTracker::connectOnNewGestures method.
 */
class GestureRecognizer : public tdv::nuitrack::HeaderOnlyAPI_Module
{
public:
	typedef std::shared_ptr<GestureRecognizer> Ptr;

	/**
	 * @brief The callback type of the new gesture detection event.
	 *
	 * This callback is called when it is detected that the user is
	 * performing a new gesture.
	 * This callback receive a smart pointer to GestureData.
	 * @see connectOnNewGestures
	 */
	typedef std::function<void (GestureData::Ptr)> OnNewGestures;
	typedef void (*OnNewGesturesRawFunctionPtr)(GestureData*, GestureRecognizer*);

	/**
	 * @brief The callback type of the user state change event.
	 *
	 * This callback will be called when it is detected that the
	 * user state has changed.
	 * This callback receive a smart pointer to UserStateData.
	 * @see connectOnUserStateChange
	 */
	typedef std::function<void (UserStateData::Ptr)> OnUserStateChange;
	typedef void (*OnUserStateChangeRawFunctionPtr)(UserStateData*, GestureRecognizer*);

	/**
	 * @brief The callback type of the user gesture data update request.
	 *
	 * This callback receive a smart pointer to UserGesturesStateData.
	 * @see tdv::nuitrack::UserGesturesStateData
	 * @see tdv::nuitrack::UserGesturesState
	 * @see connectOnUpdate
	 */
	typedef std::function<void (UserGesturesStateData::Ptr)> OnUpdate;
	typedef void (*OnUpdateRawFunctionPtr)(UserGesturesStateData*, GestureRecognizer*);

	/**
	 * @brief Create the GestureRecognizer module object.
	 *
	 * @return Smart pointer to a new GestureRecognizer instance.
	 * @note Do not call this method twice. Instead, use the previously
	 * received GestureRecognizer::Ptr.
	 */
	static GestureRecognizer::Ptr create()
	{
		NuitrackModule* pimpl = NULL;
		ExceptionType exception_code = nuitrack_CreateGestureRecognizer(&pimpl);
		ExceptionTranslator::generateExceptionByErrorCode(exception_code);
		return std::shared_ptr<GestureRecognizer>(new GestureRecognizer(pimpl));
	}

	/** @warning For internal use only. */
	GestureRecognizer(NuitrackModule* pimpl)
	{
		_pimpl = pimpl;

		_onNewGesturesCallbackStruct = new CallbackStruct<GestureData::Ptr>();
		_onUserStateChangeCallbackStruct = new CallbackStruct<UserStateData::Ptr>();
		_onUpdateCallbackStruct = new CallbackStruct<UserGesturesStateData::Ptr>();

		_callbackWrapper.setGestureRecognizer(this);
		_callbackWrapper.setOnNewGestureAddress(&onNewGesturesCallback);
		_callbackWrapper.setOnUserStateChangeAddress(&onUserStateChangeCallback);
		_callbackWrapper.setOnUpdateAddress(&onUpdateCallback);
		nuitrack_registerGestureRecognizerCallback(_pimpl, &_callbackWrapper);
	}

	virtual ~GestureRecognizer()
	{
		nuitrack_DestroyGestureRecognizer(_pimpl);
		destroyGestureRecognizer();
	}

	/**
	 * @brief Add a callback for the new gesture detection event.
	 *
	 * @param [in] callback Callback to be invoked after the gesture data update request,
	 * if it is detected that the user is performing a new gesture.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnNewGestures
	 */
	uint64_t connectOnNewGestures(const OnNewGestures& callback)
	{
		return _onNewGesturesCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the new gesture detection event.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnNewGestures
	 */
	void disconnectOnNewGestures(uint64_t handler)
	{
		_onNewGesturesCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Add a callback for the user state change event.
	 *
	 * @param [in] callback Callback to be invoked after the skeleton data update request,
	 * if it is detected that the user state has changed.
	 * @return Registered callback ID. You can use it to remove the callback.
	 * @see disconnectOnUserStateChange
	 */
	uint64_t connectOnUserStateChange(const OnUserStateChange& callback)
	{
		return _onUserStateChangeCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the user state change event.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnUserStateChange
	 */
	void disconnectOnUserStateChange(uint64_t handler)
	{
		_onUserStateChangeCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Add a callback for the gesture state data update request.
	 *
	 * @param [in] callback Callback to be invoked after the gesture state
	 * data update request.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnUpdate
	 */
	uint64_t connectOnUpdate(const OnUpdate& callback)
	{
		return _onUpdateCallbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the gesture state data update request.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnUpdate
	 */
	void disconnectOnUpdate(uint64_t handler)
	{
		_onUpdateCallbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Returns last gesture recognition time in milliseconds.
	 */
	float getProcessingTime() const
	{
		return nuitrack_GetGestureRecognizerProcessingTime(_pimpl);
	}

	/**
	 * @brief Set control gesture recognition state.
	 *
	 * Call setControlGesturesStatus(true) to enable control gestures.
	 * Call setControlGesturesStatus(false) to disable control gestures.
	 *
	 * @param [in] status Control gesture recognition state to be set.
	 */
	void setControlGesturesStatus(bool status)
	{
		nuitrack_UserGesturesSetControlStatus(_pimpl, status);
	}

	/** @warning For internal use only. */
	void destroyGestureRecognizer()
	{
		if(_onNewGesturesCallbackStruct)
			delete _onNewGesturesCallbackStruct;
		if(_onUserStateChangeCallbackStruct)
			delete _onUserStateChangeCallbackStruct;
		if(_onUpdateCallbackStruct)
			delete _onUpdateCallbackStruct;
	}

	bool canUpdate() const
	{
		return nuitrack_GetNuitrackModuleCanUpdate(_pimpl);
	}

	/**
	 * @brief Returns the last processed data timestamp in microseconds.
	 *
	 * Returns timestamp corresponding to the last estimation of gestures.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp()
	{
		return nuitrack_GetNuitrackModuleTimestamp(_pimpl);
	}

protected:
	/** @warning For internal use only. */
	static void onNewGesturesCallback(GestureRecognizerData* data, GestureRecognizer* tracker)
	{
		GestureData::Ptr newFrame(new GestureData(data));
		tracker->_onNewGesturesCallbackStruct->executeAllCallbacks(newFrame);
	}
	/** @warning For internal use only. */
	static void onUserStateChangeCallback(UsersStateChanges* data, GestureRecognizer* tracker)
	{
		UserStateData::Ptr newFrame = UserStateData::Ptr(new UserStateData(data));
		tracker->_onUserStateChangeCallbackStruct->executeAllCallbacks(newFrame);
	}
	/** @warning For internal use only. */
	static void onUpdateCallback(GestureRecognizerUserGesturesStateData* data, GestureRecognizer* tracker)
	{
		UserGesturesStateData::Ptr newFrame = UserGesturesStateData::Ptr(new UserGesturesStateData(data));
		tracker->_onUpdateCallbackStruct->executeAllCallbacks(newFrame);
	}
	/** @warning For internal use only. */
	NuitrackModule* _pimpl;
	/** @warning For internal use only. */
	GestureRecognizerCallbackWrapper _callbackWrapper;
	/** @warning For internal use only. */
	CallbackStruct<GestureData::Ptr>* _onNewGesturesCallbackStruct;
	CallbackStruct<UserStateData::Ptr>* _onUserStateChangeCallbackStruct;
	CallbackStruct<UserGesturesStateData::Ptr>* _onUpdateCallbackStruct;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_GESTURE_RECOGNIZER_H_ */
