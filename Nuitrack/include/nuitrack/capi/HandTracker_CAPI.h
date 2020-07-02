#ifndef NUITRACK_HAND_TRACKER_CAPI_H_
#define NUITRACK_HAND_TRACKER_CAPI_H_

#include "nuitrack/capi/Nuitrack_CAPI.h"

namespace tdv{
namespace nuitrack{
class HandTracker;
class HandTrackerData;
}
}

struct HandTrackerDataInner;

typedef void (*OnHandUpdateRawFunctionPtr)(HandTrackerDataInner*, tdv::nuitrack::HandTracker*);

class HandTrackerCallbackWrapper{
 public:
	HandTrackerCallbackWrapper():_tracker(NULL), _funcPtr(NULL) {}
	void setHandTracker(tdv::nuitrack::HandTracker* tracker)
	{
		_tracker = tracker;
	}
	void setFunctionAddress(OnHandUpdateRawFunctionPtr funcPtr)
	{
		_funcPtr = funcPtr;
	}

	void execute(std::shared_ptr<tdv::nuitrack::HandTrackerData> data);
 private:
	tdv::nuitrack::HandTracker* _tracker;
	OnHandUpdateRawFunctionPtr _funcPtr;
};



extern "C" void NUITRACK_API nuitrack_registerHandTrackerCallback(NuitrackModule*, HandTrackerCallbackWrapper*);

extern "C" tdv::nuitrack::ExceptionType NUITRACK_API nuitrack_CreateHandTracker(NuitrackModulePtr*);
extern "C" void NUITRACK_API nuitrack_DestroyHandTracker(NuitrackModulePtr);
extern "C" float NUITRACK_API nuitrack_GetHandTrackerProcessingTime(NuitrackModulePtr);

typedef struct HandTrackerDataInner* HandTrackerDataPtr;
typedef void(*HandTrackerUpdateCallback)(HandTrackerDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnHandTrackerUpdate(NuitrackModulePtr, HandTrackerUpdateCallback);
extern "C" void NUITRACK_API nuitrack_OnHandTrackerUpdateDisconnect(NuitrackModulePtr, uint64_t);

extern "C" uint64_t NUITRACK_API nuitrack_GetHandTrackerDataTimestamp(HandTrackerDataPtr);
extern "C" size_t NUITRACK_API nuitrack_HandTrackerGetNumUsers(HandTrackerDataPtr);
extern "C" void NUITRACK_API nuitrack_HandTrackerGetUserHands(HandTrackerDataPtr, int, int*, tdv::nuitrack::Hand*, tdv::nuitrack::Hand*);
extern "C" void NUITRACK_API nuitrack_DestroyHandTrackerData(HandTrackerDataPtr);
extern "C" void NUITRACK_API nuitrack_AddHandTrackerDataRef(HandTrackerDataPtr);
extern "C" void NUITRACK_API nuitrack_ReceiveInnerHandTrackerData(NuitrackModule*, HandTrackerDataInner**);



#endif /* NUITRACK_HAND_TRACKER_CAPI_H_ */
