#ifndef NUITRACK_HAND_TRACKER_H_
#define NUITRACK_HAND_TRACKER_H_

#include <functional>

#include "nuitrack/modules/HeaderOnlyAPI_Module.h"
#include "nuitrack/types/Export.h"
#include "nuitrack/types/HandTrackerData.h"
#include "nuitrack/capi/HandTracker_CAPI.h"
#include "nuitrack/utils/ExceptionTranslator.h"
#include "nuitrack/utils/CallbackStruct.h"

namespace tdv
{
namespace nuitrack
{
/**
 * @ingroup HandTracker_group
 * @brief Represents the interface to the capabilities of the
 * @ref HandTracker_group "Nuitrack Hand Tracker" module.
 *
 * To enable the module, you must create an instance of this class.
 * To create the instance, use a special named constructor HandTracker::create.
 * This instance is called %HandTracker module object.
 * To receive the hand tracking data, add an HandTracker::OnUpdate callback
 * to the module object with HandTracker::connectOnUpdate method.
 */
class HandTracker : public tdv::nuitrack::HeaderOnlyAPI_Module
{
public:
	/**
	 * @brief Smart pointer to access the SkeletonTracker instance.
	 * @see create
	 */
	typedef std::shared_ptr<HandTracker> Ptr;

	/**
	 * @brief The callback type of the hand data update request.
	 *
	 * This callback receive a smart pointer to SkeletonData, which contains @ref Skeleton array.
	 *
	 * @see tdv::nuitrack::HandTrackerData
	 * @see tdv::nuitrack::Hand
	 * @see connectOnUpdate
	 */
	typedef std::function<void (HandTrackerData::Ptr)> OnUpdate;

	typedef void (*OnUpdateRawFunctionPtr)(HandTrackerData*, HandTracker*);

	/**
	 * @brief Create the HandTracker module object.
	 *
	 * @return Smart pointer to a new HandTracker instance.
	 * @note Do not call this method twice. Instead, use the previously
	 * received HandTracker::Ptr.
	 */
	static HandTracker::Ptr create()
	{
		NuitrackModule* pimpl = NULL;
		ExceptionType exception_code = nuitrack_CreateHandTracker(&pimpl);
		ExceptionTranslator::generateExceptionByErrorCode(exception_code);
		return std::shared_ptr<HandTracker>(new HandTracker(pimpl));
	}

	virtual ~HandTracker()
	{
		destroyHandTracker();
		nuitrack_DestroyHandTracker(_pimpl);
	}

	/** @warning For internal use only. */
	HandTracker(NuitrackModule* pimpl)
	{
		_pimpl = pimpl;

		_callbackStruct = new CallbackStruct<HandTrackerData::Ptr>();
		_callbackWrapper.setHandTracker(this);
		_callbackWrapper.setFunctionAddress(&onUpdateCallback);
		nuitrack_registerHandTrackerCallback(_pimpl, &_callbackWrapper);
	}

	/**
	 * @brief Add a callback for the hand data update request.
	 *
	 * @param [in] callback Callback to be invoked after the hand data update request.
	 * @return Callback ID. You can use it to remove the callback.
	 * @see disconnectOnUpdate
	 */
	uint64_t connectOnUpdate(const OnUpdate& callback)
	{
		return _callbackStruct->addCallback(callback);
	}

	/**
	 * @brief Remove a callback of the hand data update request.
	 *
	 * @param [in] handler ID of the previously added callback.
	 * @see connectOnUpdate
	 */
	void disconnectOnUpdate(uint64_t handler)
	{
		_callbackStruct->deleteCallback(handler);
	}

	/**
	 * @brief Returns smart pointer to the last avilable HandTrackerData.
	 */
	HandTrackerData::Ptr getData()
	{
		HandTrackerDataInner* data = NULL;
		nuitrack_ReceiveInnerHandTrackerData(_pimpl, &data);
		HandTrackerData::Ptr newFrame(new HandTrackerData(data));
		return newFrame;
	}

	/**
	 * @brief Returns last hand data processing time in milliseconds.
	 */
	float getProcessingTime() const
	{
		return nuitrack_GetHandTrackerProcessingTime(_pimpl);
	}

	bool canUpdate() const
	{
		return nuitrack_GetNuitrackModuleCanUpdate(_pimpl);
	}

	/**
	 * @brief Returns the last processed data timestamp in microseconds.
	 *
	 * Returns timestamp corresponding to the last hand tracking data estimation.
	 * @note The exact meaning of this value depends on the depth provider.
	 */
	virtual uint64_t getTimestamp()
	{
		return nuitrack_GetNuitrackModuleTimestamp(_pimpl);
	}

protected:
	/** @warning For internal use only. */
	static void onUpdateCallback(HandTrackerDataInner* data, HandTracker* tracker)
	{
		HandTrackerData::Ptr newFrame(new HandTrackerData(data));
		tracker->_callbackStruct->executeAllCallbacks(newFrame);
	}
	/** @warning For internal use only. */
	void destroyHandTracker()
	{
		if(_callbackStruct)
			delete _callbackStruct;
	}
	/** @warning For internal use only. */
	NuitrackModule* _pimpl;
	/** @warning For internal use only. */
	HandTrackerCallbackWrapper _callbackWrapper;
	/** @warning For internal use only. */
	CallbackStruct<HandTrackerData::Ptr>* _callbackStruct;
};

} /* namespace nuitrack */
} /* namespace tdv */

#endif /* NUITRACK_HAND_TRACKER_H_ */
