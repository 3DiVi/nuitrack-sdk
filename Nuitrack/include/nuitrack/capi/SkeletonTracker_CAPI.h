#ifndef NUITRACK_SKELETONTRACKER_CAPI_H_
#define NUITRACK_SKELETONTRACKER_CAPI_H_

#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/types/Skeleton.h"

namespace tdv{
namespace nuitrack{
class SkeletonTracker;
class SkeletonData;
}
}

typedef struct SkeletonTrackerData* SkeletonTrackerDataPtr;

typedef void(*UserCallback)(NuitrackModulePtr, int);
typedef void(*SkeletonTrackerUpdateCallback)(SkeletonTrackerDataPtr);

typedef void (*SkeletonOnUpdateRawFunctionPtr)(SkeletonTrackerData*, tdv::nuitrack::SkeletonTracker*);
typedef void (*SkeletonOnNewUserRawFunctionPtr)(tdv::nuitrack::SkeletonTracker*, int);
typedef void (*SkeletonOnLostUserRawFunctionPtr)(tdv::nuitrack::SkeletonTracker*, int);

class SkeletonTrackerCallbackWrapper{
 public:
	SkeletonTrackerCallbackWrapper():_tracker(NULL), _onUpdatePtr(NULL), _onNewUserPtr(NULL),
	_onLostUserPtr(NULL) {}

	void setSkeletonTracker(tdv::nuitrack::SkeletonTracker* tracker)
	{
		_tracker = tracker;
	}
	void setOnUpdateAddress(SkeletonOnUpdateRawFunctionPtr funcPtr)
	{
		_onUpdatePtr = funcPtr;
	}
	void setOnNewUserAddress(SkeletonOnNewUserRawFunctionPtr funcPtr)
	{
		_onNewUserPtr = funcPtr;
	}
	void setOnLostUserAddress(SkeletonOnLostUserRawFunctionPtr funcPtr)
	{
		_onLostUserPtr = funcPtr;
	}

	void executeOnUpdate(std::shared_ptr<tdv::nuitrack::SkeletonData> data);
	void executeOnNewUser(std::shared_ptr<tdv::nuitrack::SkeletonTracker>, int id);
	void executeOnLostUser(std::shared_ptr<tdv::nuitrack::SkeletonTracker>, int id);

 private:
	tdv::nuitrack::SkeletonTracker* _tracker;
	SkeletonOnUpdateRawFunctionPtr _onUpdatePtr;
	SkeletonOnNewUserRawFunctionPtr _onNewUserPtr;
	SkeletonOnLostUserRawFunctionPtr _onLostUserPtr;
};

extern "C" void NUITRACK_API nuitrack_registerSkeletonTrackerCallback(NuitrackModule*, SkeletonTrackerCallbackWrapper*);

extern "C" tdv::nuitrack::ExceptionType NUITRACK_API nuitrack_CreateSkeletonTracker(NuitrackModulePtr*);

extern "C" void NUITRACK_API nuitrack_DestroySkeletonTracker(NuitrackModulePtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnNewUser(NuitrackModulePtr, UserCallback);

extern "C" uint64_t NUITRACK_API nuitrack_OnLostUser(NuitrackModulePtr, UserCallback);

extern "C" uint64_t NUITRACK_API nuitrack_OnSkeletonUpdate(NuitrackModulePtr, SkeletonTrackerUpdateCallback);

extern "C" void NUITRACK_API nuitrack_OnNewUserDisconnect(NuitrackModulePtr, uint64_t handle);

extern "C" void NUITRACK_API nuitrack_OnLostUserDisconnect(NuitrackModulePtr, uint64_t handle);

extern "C" void NUITRACK_API nuitrack_OnSkeletonUpdateDisconnect(NuitrackModulePtr, uint64_t handle);

extern "C" SkeletonTrackerDataPtr NUITRACK_API nuitrack_GetSkeletonTrackerData(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_DestroySkeletonTrackerData(SkeletonTrackerDataPtr);
extern "C" void NUITRACK_API nuitrack_AddSkeletonTrackerDataRef(SkeletonTrackerDataPtr);

extern "C" int NUITRACK_API nuitrack_GetNumUsers(SkeletonTrackerDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetSkeletonDataTimestamp(SkeletonTrackerDataPtr);

extern "C" int NUITRACK_API nuitrack_GetSkeletonID(SkeletonTrackerDataPtr, int);

extern "C" void NUITRACK_API nuitrack_GetSkeletonJoint(SkeletonTrackerDataPtr, int, tdv::nuitrack::JointType, tdv::nuitrack::Joint*);

extern "C" bool NUITRACK_API nuitrack_IsAutoTracking(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_SetAutoTracking(NuitrackModulePtr, bool);

extern "C" bool NUITRACK_API nuitrack_IsTracking(NuitrackModulePtr, int);

extern "C" void NUITRACK_API nuitrack_StartTracking(NuitrackModulePtr, int);

extern "C" void NUITRACK_API nuitrack_StopTracking(NuitrackModulePtr, int);

extern "C" void NUITRACK_API nuitrack_SetNumActiveUsers(NuitrackModulePtr, int);

extern "C" float NUITRACK_API nuitrack_GetSkeletonTrackerProcessingTime(NuitrackModulePtr);

extern "C" float NUITRACK_API nuitrack_GetSkeletonTrackerTimestamp(SkeletonTrackerDataPtr);

#endif /* NUITRACK_SKELETONTRACKER_CAPI_H_ */
