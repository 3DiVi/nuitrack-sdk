#ifndef NUITRACK_GESTURE_RECOGNITZER_CAPI_H_
#define NUITRACK_GESTURE_RECOGNITZER_CAPI_H_

#include "nuitrack/capi/Nuitrack_CAPI.h"

namespace tdv{
namespace nuitrack{
class GestureRecognizer;
class GestureData;
class UserStateData;
class UserGesturesStateData;
}
}

typedef struct GestureRecognizerData* GestureRecognizerDataPtr;
struct UsersStateChanges;
typedef struct GestureRecognizerUserGesturesStateData* GestureRecognizerUserGesturesStateDataPtr;

typedef void (*OnNewGesturesRawFunctionPtr)(GestureRecognizerData*, tdv::nuitrack::GestureRecognizer*);
typedef void (*OnUserStateChangeRawFunctionPtr)(UsersStateChanges*, tdv::nuitrack::GestureRecognizer*);
typedef void (*OnGestureUpdateRawFunctionPtr)(GestureRecognizerUserGesturesStateData*, tdv::nuitrack::GestureRecognizer*);

class GestureRecognizerCallbackWrapper{
 public:
	GestureRecognizerCallbackWrapper():_recognizer(NULL), _onUpdatePtr(NULL), _onStateChangePtr(NULL),
	_onNewGesturesPtr(NULL) {}
	void setGestureRecognizer(tdv::nuitrack::GestureRecognizer* recognizer)
	{
		_recognizer = recognizer;
	}

	void setOnNewGestureAddress(OnNewGesturesRawFunctionPtr funcPtr)
	{
		_onNewGesturesPtr = funcPtr;
	}
	void setOnUserStateChangeAddress(OnUserStateChangeRawFunctionPtr funcPtr)
	{
		_onStateChangePtr = funcPtr;
	}
	void setOnUpdateAddress(OnGestureUpdateRawFunctionPtr funcPtr)
	{
		_onUpdatePtr = funcPtr;
	}

	void executeOnUpdate(std::shared_ptr<tdv::nuitrack::UserGesturesStateData> data);
	void executeOnNewGestures(std::shared_ptr<tdv::nuitrack::GestureData> data);
	void executeOnUserStateChange(std::shared_ptr<tdv::nuitrack::UserStateData> data);
 private:
	tdv::nuitrack::GestureRecognizer* _recognizer;
	OnNewGesturesRawFunctionPtr _onNewGesturesPtr;
	OnUserStateChangeRawFunctionPtr _onStateChangePtr;
	OnGestureUpdateRawFunctionPtr _onUpdatePtr;
};



extern "C" void NUITRACK_API nuitrack_registerGestureRecognizerCallback(NuitrackModule* tracker, GestureRecognizerCallbackWrapper* wrapper);

// Common functions
extern "C" tdv::nuitrack::ExceptionType NUITRACK_API nuitrack_CreateGestureRecognizer(NuitrackModulePtr*);
extern "C" void NUITRACK_API nuitrack_DestroyGestureRecognizer(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_UserGesturesSetControlStatus(NuitrackModulePtr, bool);
extern "C" float NUITRACK_API nuitrack_GetGestureRecognizerProcessingTime(NuitrackModulePtr);

// OnNewGesturesCallback

typedef void(*GestureRecognizerNewGesturesCallback)(GestureRecognizerDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnNewGestures(NuitrackModulePtr, GestureRecognizerNewGesturesCallback);
extern "C" void NUITRACK_API nuitrack_OnNewGesturesDisconnect(NuitrackModulePtr, uint64_t);

extern "C" uint64_t NUITRACK_API nuitrack_GetUserGesturesTimestamp(GestureRecognizerDataPtr);
extern "C" size_t NUITRACK_API nuitrack_GetUserGesturesNumGestures(GestureRecognizerDataPtr);
extern "C" void NUITRACK_API nuitrack_GetUserGesture(GestureRecognizerDataPtr, int, tdv::nuitrack::Gesture*);
extern "C" void NUITRACK_API nuitrack_DestroyGestureRecognizerData(GestureRecognizerDataPtr);
extern "C" void NUITRACK_API nuitrack_AddGestureRecognizerDataRef(GestureRecognizerDataPtr);

// OnUsersStateChangedCallback
typedef struct UsersStateChanges* UsersStateChangesPtr;
typedef void(*GestureRecognizerUsersStateChangedCallback)(UsersStateChangesPtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnUsersStateChanged(NuitrackModulePtr, GestureRecognizerUsersStateChangedCallback);
extern "C" void NUITRACK_API nuitrack_OnUsersStateChangedDisconnect(NuitrackModulePtr, uint64_t);

extern "C" uint64_t NUITRACK_API nuitrack_GetUsersStateChangesTimestamp(UsersStateChangesPtr);
extern "C" size_t NUITRACK_API nuitrack_GetNumUsersStateChanges(UsersStateChangesPtr);
extern "C" void NUITRACK_API nuitrack_GetUserStateChange(UsersStateChangesPtr, int, tdv::nuitrack::UserState*);
extern "C" void NUITRACK_API nuitrack_DestroyUsersStateChanges(UsersStateChangesPtr);
extern "C" void NUITRACK_API nuitrack_AddUsersStateChangesRef(UsersStateChangesPtr);

// OnUpdateCallback
typedef void(*GestureRecognizerUpdateCallback)(GestureRecognizerUserGesturesStateDataPtr);

extern "C" void NUITRACK_API nuitrack_DestroyUsersStateData(GestureRecognizerUserGesturesStateDataPtr);
extern "C" void NUITRACK_API nuitrack_AddUsersStateDataRef(GestureRecognizerUserGesturesStateDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnGesturesUpdate(NuitrackModulePtr, GestureRecognizerUpdateCallback);
extern "C" void NUITRACK_API nuitrack_OnGesturesUpdateDisconnect(NuitrackModulePtr, uint64_t);

extern "C" uint64_t NUITRACK_API nuitrack_GetUsersGesturesStateTimestamp(GestureRecognizerUserGesturesStateDataPtr);

extern "C" int NUITRACK_API nuitrack_GetNumUsersGestures(GestureRecognizerUserGesturesStateDataPtr);
extern "C" void NUITRACK_API nuitrack_GetUserStateData(GestureRecognizerUserGesturesStateDataPtr, int, tdv::nuitrack::UserState*);

extern "C" int NUITRACK_API nuitrack_GetNumUserGestureState(GestureRecognizerUserGesturesStateDataPtr, int);
extern "C" void NUITRACK_API nuitrack_GetUserGestureState(GestureRecognizerUserGesturesStateDataPtr, int, int, tdv::nuitrack::GestureState*);

#endif /* NUITRACK_GESTURE_RECOGNITZER_CAPI_H_ */
