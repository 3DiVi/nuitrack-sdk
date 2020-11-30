#ifndef NUITRACK_USERTRACKER_CAPI_H_
#define NUITRACK_USERTRACKER_CAPI_H_

#include <stdint.h>

#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/types/User.h"

typedef struct UserTrackerData* UserTrackerDataPtr;

typedef void(*UserTrackerUserCallback)(int);
typedef void(*UserTrackerUpdateCallback)(UserTrackerDataPtr);

namespace tdv{
namespace nuitrack{
class UserTracker;
class UserFrame;
}
}

typedef void (*OnUpdateRawFunctionPtr)(UserTrackerData*, tdv::nuitrack::UserTracker*);
typedef void (*OnNewUserRawFunctionPtr)(int, tdv::nuitrack::UserTracker*);
typedef void (*OnLostUserRawFunctionPtr)(int, tdv::nuitrack::UserTracker*);

class UserTrackerCallbackWrapper{
 public:
	UserTrackerCallbackWrapper():_tracker(NULL), _onUpdatePtr(NULL), _onNewUserPtr(NULL),
															_onLostUserPtr(NULL){}
	void setUserTracker(tdv::nuitrack::UserTracker* tracker)
	{
		_tracker = tracker;
	}
	void setOnUpdateAddress(OnUpdateRawFunctionPtr funcPtr)
	{
		_onUpdatePtr = funcPtr;
	}
	void setOnNewUserAddress(OnNewUserRawFunctionPtr funcPtr)
	{
		_onNewUserPtr = funcPtr;
	}
	void setOnLostUserAddress(OnLostUserRawFunctionPtr funcPtr)
	{
		_onLostUserPtr = funcPtr;
	}

	void executeOnUpdate(std::shared_ptr<tdv::nuitrack::UserFrame> userFrame);
	void executeOnNewUser(int id);
	void executeOnLostUser(int id);
private:
	tdv::nuitrack::UserTracker* _tracker;
	OnUpdateRawFunctionPtr _onUpdatePtr;
	OnNewUserRawFunctionPtr _onNewUserPtr;
	OnLostUserRawFunctionPtr _onLostUserPtr;
};


extern "C" void NUITRACK_API nuitrack_registerUserTrackerCallback(NuitrackModule* tracker, UserTrackerCallbackWrapper* wrapper);

extern "C" tdv::nuitrack::ExceptionType NUITRACK_API nuitrack_CreateUserTracker(NuitrackModulePtr*);

extern "C" void NUITRACK_API nuitrack_DestroyUserTracker(NuitrackModulePtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnUserTrackerUpdate(NuitrackModulePtr, UserTrackerUpdateCallback);
extern "C" uint64_t NUITRACK_API nuitrack_UserTrackerOnNewUser(NuitrackModulePtr, UserTrackerUserCallback);
extern "C" uint64_t NUITRACK_API nuitrack_UserTrackerOnLostUser(NuitrackModulePtr, UserTrackerUserCallback);


extern "C" void NUITRACK_API nuitrack_OnUserTrackerUpdateDisconnect(NuitrackModulePtr, uint64_t);
extern "C" void NUITRACK_API nuitrack_UserTrackerOnNewUserDisconnect(NuitrackModulePtr, uint64_t);
extern "C" void NUITRACK_API nuitrack_UserTrackerOnLostUserDisconnect(NuitrackModulePtr, uint64_t);

extern "C" UserTrackerDataPtr NUITRACK_API nuitrack_GetUserTrackerData(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_DestroyUserTrackerData(UserTrackerDataPtr);
extern "C" void NUITRACK_API nuitrack_AddUserTrackerDataRef(UserTrackerDataPtr);

extern "C" uint16_t NUITRACK_API nuitrack_GetUserFrameValueAtIndex(UserTrackerDataPtr ptr, int i);
extern "C" uint16_t NUITRACK_API nuitrack_GetUserFrameValue(UserTrackerDataPtr ptr, int x, int y);

extern "C" size_t NUITRACK_API nuitrack_GetUserFrameRows(UserTrackerDataPtr);

extern "C" size_t NUITRACK_API nuitrack_GetUserFrameCols(UserTrackerDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetUserFrameID(UserTrackerDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetUserFrameTimestamp(UserTrackerDataPtr);

extern "C" NUITRACK_API const uint16_t* nuitrack_GetUserFrameData(UserTrackerDataPtr);

extern "C" size_t NUITRACK_API nuitrack_GetUserFrameNumUsers(UserTrackerDataPtr);

extern "C" void NUITRACK_API nuitrack_GetUserFrameUser(UserTrackerDataPtr, int, tdv::nuitrack::User*);

extern "C" void NUITRACK_API nuitrack_GetUserFrameFloor(UserTrackerDataPtr, tdv::nuitrack::Vector3*);

extern "C" void NUITRACK_API nuitrack_GetUserFrameFloorNormal(UserTrackerDataPtr, tdv::nuitrack::Vector3*);

extern "C" float NUITRACK_API nuitrack_GetUserTrackerProcessingTime(NuitrackModulePtr);

#endif /* NUITRACK_USERTRACKER_CAPI_H_ */
