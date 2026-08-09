// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/cpp/IssuesData.h"
#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/Error.h"
#include "nuitrack/cpp/NuitrackModule.h"
#include "nuitrack/cpp/SkeletonTracker.h"
#include "nuitrack/cpp/Types.h"

using tdv::nuitrack::nuitrack_error;

using ret = tdv::nuitrack::ExceptionType;

extern "C" {

/// Nuitrack::*
NUITRACK_API ret nuitrack_Initialize(); // __attribute__ ((deprecated));

NUITRACK_API ret  nuitrack_InitializeFromConfig(const char*);
NUITRACK_API void nuitrack_InitializeFromConfig_E(const char*, nuitrack_error** error);

NUITRACK_API ret nuitrack_SetConfigValue(const char*, const char*);
NUITRACK_API ret nuitrack_GetConfigValue(const char* key, char* value, int bufferSize);

NUITRACK_API ret  nuitrack_Run();
NUITRACK_API void nuitrack_Update(nuitrack_error**);
NUITRACK_API void nuitrack_SyncUpdate(NuitrackModule*, nuitrack_error**);
NUITRACK_API void nuitrack_WaitSyncUpdate(NuitrackModule*, nuitrack_error**);
NUITRACK_API bool nuitrack_runDumpSaving();

NUITRACK_API ret nuitrack_Release();

NUITRACK_API ret nuitrack_GetLicense(char* value, int bufferSize);

NUITRACK_API ret   nuitrack_GetInstancesJson(char* value, int bufferSize);
NUITRACK_API void  nuitrack_GetInstancesJsonSize(int* size, nuitrack_error** error);  // deprecated
NUITRACK_API void  nuitrack_GetInstancesJsonData(char* data, nuitrack_error** error); // deprecated
NUITRACK_API char* nuitrack_GetInstancesJsonDataAlloc(nuitrack_error** error);
NUITRACK_API void  nuitrack_GetInstancesJsonDataClear(char* resultPtr);

NUITRACK_API char* nuitrack_GetMultiSensorSkeletonsJsonDataAlloc(nuitrack_error** error);
NUITRACK_API void  nuitrack_GetMultiSensorSkeletonsJsonDataClear(char* resultPtr);

NUITRACK_API char* nuitrack_GetInternalParamsJsonAlloc(nuitrack_error** error);
NUITRACK_API void  nuitrack_GetInternalParamsJsonClear(char* resultPtr);

NUITRACK_API void* nuitrack_GetFromDataStream(tdv::nuitrack::DataStreamType type, int streamId = 0);
NUITRACK_API void  nuitrack_FreeDataStreamItem(void* item);

NUITRACK_API                     void nuitrack_SetParamI(int);
NUITRACK_API NUITRACK_DEPRECATED void nuitrack_SetParam(const char*);

NUITRACK_API ret nuitrack_GetVersion(int* version);

NUITRACK_API ret         nuitrack_GetExceptionType(NuitrackModule* module);
NUITRACK_API void        nuitrack_GetExceptionMessage(NuitrackModule* module, char * message, int size);
NUITRACK_API ret         nuitrack_GetErrorType(nuitrack_error* e);
NUITRACK_API const char* nuitrack_GetErrorMessage(nuitrack_error* e);
NUITRACK_API void        nuitrack_DestroyError(nuitrack_error* e);

}


/// NuitrackDevice_CAPI.h

extern "C" {
// Nuitrack::*
NUITRACK_API ret nuitrack_GetDeviceList(struct NuitrackDeviceHolder** bufferForDevices, int bufferMaxSize);
NUITRACK_API ret nuitrack_SetDevice(NuitrackDeviceHolder* dev);
NUITRACK_API ret nuitrack_deleteNuitrackDeviceImpl(NuitrackDeviceHolder* dev);

// NuitrackDeviceImpl::*
NUITRACK_API ret nuitrack_nuitrackDevice_getInfo(NuitrackDeviceHolder* dev, int info_type, char* out);

NUITRACK_API ret nuitrack_nuitrackDevice_getVideoModeList(NuitrackDeviceHolder*             dev,
                                                          int                               stream_type,
                                                          int                               list_index,
                                                          tdv::nuitrack::device::VideoMode& out);

NUITRACK_API ret nuitrack_nuitrackDevice_getVideoModeListSize(NuitrackDeviceHolder* dev, int stream_type, int& out);

NUITRACK_API ret nuitrack_nuitrackDevice_getSelectedVideoMode(NuitrackDeviceHolder*             dev,
                                                              int                               stream_type,
                                                              tdv::nuitrack::device::VideoMode& out);

NUITRACK_API ret nuitrack_nuitrackDevice_setVideoMode(NuitrackDeviceHolder*            dev,
                                                      int                              stream_type,
                                                      tdv::nuitrack::device::VideoMode vm);

NUITRACK_API ret nuitrack_nuitrackDevice_getStringBufferSizeConst(int& out);

NUITRACK_API ret nuitrack_nuitrackDevice_getDeviceListLimitConst(int& out);

NUITRACK_API ret nuitrack_nuitrackDevice_getActivationStatus(NuitrackDeviceHolder*                    dev,
                                                             tdv::nuitrack::device::ActivationStatus& out);

NUITRACK_API void nuitrack_nuitrackDevice_activate(NuitrackDeviceHolder*           dev,
                                                   const char*                     activation_key,
                                                   tdv::nuitrack::nuitrack_error** e);
}

/// Public_Nuitrack::*
namespace tdv { namespace nuitrack {

class IssuesDataPIMPL;
class IssueTracker;
using BaseModuleType = Module;

}}

// using OnIssueUpdate = std::function<void(tdv::nuitrack::IssuesData::Ptr)>;

extern "C" {
NUITRACK_API ret  nuitrack_SyncUpdatePublic(tdv::nuitrack::BaseModuleType*);
NUITRACK_API ret  nuitrack_WaitSyncUpdatePublic(tdv::nuitrack::BaseModuleType*);
NUITRACK_API void nuitrack_getIssueTracker(tdv::nuitrack::IssueTracker**);
}


/// IssueTracker::*
namespace tdv { namespace nuitrack { /* class Issue; */ }}

struct IssueTrackerData;


class IssueTrackerCallbackWrapper
{
public:
    using Ptr = std::shared_ptr<IssueTrackerCallbackWrapper>;

    void setIssueTracker(tdv::nuitrack::IssueTracker* sensor) { _sensor = sensor; }
    void setFunctionAddress(void (*funcPtr)(IssueTrackerData* data)) { _funcPtr = funcPtr; }

    void execute(std::shared_ptr<tdv::nuitrack::cpp::IssuesData> issuesData);

private:
    tdv::nuitrack::IssueTracker* _sensor     = nullptr;
    void (*_funcPtr)(IssueTrackerData* data) = nullptr;
};

extern "C" {
NUITRACK_API void* nuitrack_getIssuesCallbackStruct();
NUITRACK_API void  nuitrack_setIssuesCallbackStruct(void*);

NUITRACK_API void nuitrack_registerIssuesTrackerCallback(IssueTrackerCallbackWrapper* wrapper);

NUITRACK_API uint64_t nuitrack_OnIssueTrackerUpdate(void (*)(IssueTrackerData*));
NUITRACK_API void     nuitrack_OnIssueTrackerUpdateDisconnect(uint64_t);
// NUITRACK_API void     nuitrack_CreateIssueTrackerData(IssueTrackerData**, tdv::nuitrack::IssuesData*);
NUITRACK_API void     nuitrack_DestroyIssueTrackerData(IssueTrackerData*);

NUITRACK_API void nuitrack_AddIssueTrackerDataRef(IssueTrackerData*);

NUITRACK_API bool nuitrack_GetSensorIssue       (IssueTrackerData* dataPtr, char* buffer, int bufferSize);
NUITRACK_API bool nuitrack_GetOcclusionIssue    (IssueTrackerData* dataPtr, int userId);
NUITRACK_API void nuitrack_GetFrameBorderIssue  (IssueTrackerData* dataPtr, int userId, bool* left, bool* right, bool* top);
}


/// ColorSensor
namespace tdv { namespace nuitrack { class ColorSensorPIMPL; class RGBFrame; }}

struct FrameHolder; // fwd - ref-counted depth frame holder

class ColorSensorCallbackWrapper
{
public:
    ColorSensorCallbackWrapper(): _sensor(nullptr), _funcPtr(nullptr) {}
    void setColorSensor(tdv::nuitrack::ColorSensorPIMPL* sensor) { _sensor = sensor; }
    void setFunctionAddress(void (*funcPtr)(FrameHolder*, tdv::nuitrack::ColorSensorPIMPL*)) { _funcPtr = funcPtr; }

    void execute(const tdv::nuitrack::RGBFrame::Ptr& rgbFrame);
private:
    tdv::nuitrack::ColorSensorPIMPL* _sensor;
    void (*_funcPtr)(FrameHolder*, tdv::nuitrack::ColorSensorPIMPL*);
};

extern "C" {
NUITRACK_API ret  nuitrack_CreateColorSensor(NuitrackModule**);
NUITRACK_API void nuitrack_DestroyColorSensor(NuitrackModule*);

NUITRACK_API void nuitrack_registerColorSensorCallback(NuitrackModule*, ColorSensorCallbackWrapper*);

NUITRACK_API void nuitrack_OnColorSensorUpdate(NuitrackModule*, void (*)(FrameHolder*));
NUITRACK_API void nuitrack_OnColorSensorUpdateDisconnect(NuitrackModule*, uint64_t handle);

NUITRACK_API FrameHolder* nuitrack_GetColorSensorData(NuitrackModule*);

NUITRACK_API void nuitrack_DestroyColorSensorData(FrameHolder*);
NUITRACK_API void nuitrack_AddColorSensorDataRef(FrameHolder*);

NUITRACK_API tdv::nuitrack::Color3 nuitrack_GetColorFrameValueAtIndex(FrameHolder* ptr, int i);
NUITRACK_API tdv::nuitrack::Color3 nuitrack_GetColorFrameValue(FrameHolder* ptr, int x, int y);

NUITRACK_API void  nuitrack_GetColorSensorOutputMode(NuitrackModule*, tdv::nuitrack::CameraModel*);
NUITRACK_API const tdv::nuitrack::Color3* nuitrack_GetColorFrameData(FrameHolder*);
NUITRACK_API void  nuitrack_WriteColorFrameTextureBGRA(FrameHolder*, uint8_t*, size_t);
}


/// --- DepthSensor_CAPI.h
namespace tdv { namespace nuitrack { class DepthSensorPIMPL; class DepthFrame; }}

class DepthSensorCallbackWrapper
{
public:
    void setDepthSensor(tdv::nuitrack::DepthSensorPIMPL* sensor)                             { _sensor = sensor;   }
    void setFunctionAddress(void (*funcPtr)(FrameHolder*, tdv::nuitrack::DepthSensorPIMPL*)) { _funcPtr = funcPtr; }

    void execute(const std::shared_ptr<tdv::nuitrack::DepthFrame>& depthFrame);

private:
    tdv::nuitrack::DepthSensorPIMPL* _sensor                                                   = nullptr;
    void (*                          _funcPtr)(FrameHolder*, tdv::nuitrack::DepthSensorPIMPL*) = nullptr;
};

extern "C" {
NUITRACK_API void nuitrack_registerDepthSensorCallback(NuitrackModule*, DepthSensorCallbackWrapper*);

/// Sensor
NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_CreateDepthSensor(NuitrackModule**);
NUITRACK_API void                         nuitrack_DestroyDepthSensor(NuitrackModule*);

NUITRACK_API uint64_t nuitrack_OnDepthSensorUpdate(NuitrackModule*, void (*)(FrameHolder*));
NUITRACK_API void     nuitrack_OnDepthSensorUpdateDisconnect(NuitrackModule*, uint64_t);

NUITRACK_API FrameHolder* nuitrack_GetDepthSensorData(const NuitrackModule*);
NUITRACK_API void         nuitrack_GetDepthSensorOutputMode(NuitrackModule*, tdv::nuitrack::CameraModel*);

NUITRACK_API int          nuitrack_GetFrameRows(FrameHolder*);
NUITRACK_API int          nuitrack_GetFrameCols(FrameHolder*);
NUITRACK_API uint64_t     nuitrack_GetFrameID(FrameHolder*);
NUITRACK_API uint64_t     nuitrack_GetFrameTimestamp(FrameHolder*);
NUITRACK_API FrameHolder* nuitrack_UpdateFrameSize(FrameHolder* data, tdv::nuitrack::Size newSize);

/// Depth Frame
// metadata
NUITRACK_API void nuitrack_DestroyDepthSensorData(FrameHolder*);
NUITRACK_API void nuitrack_AddDepthSensorDataRef(FrameHolder*);

// data
NUITRACK_API uint16_t        nuitrack_GetDepthFrameValueAtIndex(FrameHolder* ptr, int i);
NUITRACK_API uint16_t        nuitrack_GetDepthFrameValue(FrameHolder* ptr, int x, int y);
NUITRACK_API const uint16_t* nuitrack_GetDepthFrameData(FrameHolder*);
NUITRACK_API void            nuitrack_WriteDepthFramePointCloudTextureRGBA(FrameHolder*, float*, size_t, tdv::nuitrack::PointCloud::Format);

NUITRACK_API tdv::nuitrack::CVector3 nuitrack_ctypes_ConvertProjToRealCoordsXYZ(NuitrackModule*, int, int, uint16_t);
NUITRACK_API tdv::nuitrack::CVector3 nuitrack_ctypes_ConvertProjToRealCoordsVector3(NuitrackModule*, tdv::nuitrack::CVector3);

NUITRACK_API tdv::nuitrack::CVector3 nuitrack_ctypes_ConvertRealToProjCoordsXYZ(NuitrackModule*, float, float, float);
NUITRACK_API tdv::nuitrack::CVector3 nuitrack_ctypes_ConvertRealToProjCoordsVector3(NuitrackModule*, tdv::nuitrack::CVector3);

NUITRACK_API bool nuitrack_IsDepthSensorMirror(NuitrackModule*);
NUITRACK_API void nuitrack_SetDepthSensorMirror(NuitrackModule*, bool);

NUITRACK_API NUITRACK_DEPRECATED const uint16_t* nuitrack_GetRgbFrameData(FrameHolder*);
}


/// --- UserTracker_CAPI.h
using UserTrackerUserCallback   = void(*)(int);
using UserTrackerUpdateCallback = void(*)(struct FrameHolder*);

namespace tdv { namespace nuitrack { class UserTrackerPIMPL; class UserFrame; } }

using OnUpdateRawFunctionPtr = void(*)(FrameHolder*, tdv::nuitrack::UserTrackerPIMPL*);
using OnNewUserRawFunctionPtr = void(*)(int, tdv::nuitrack::UserTrackerPIMPL*);
using OnLostUserRawFunctionPtr = void(*)(int, tdv::nuitrack::UserTrackerPIMPL*);

class UserTrackerCallbackWrapper
{
public:
	void setUserTracker(tdv::nuitrack::UserTrackerPIMPL* tracker) { _tracker = tracker; }
	void setOnUpdateAddress(OnUpdateRawFunctionPtr funcPtr) { _onUpdatePtr = funcPtr; }
	void setOnNewUserAddress(OnNewUserRawFunctionPtr funcPtr) { _onNewUserPtr = funcPtr; }
	void setOnLostUserAddress(OnLostUserRawFunctionPtr funcPtr) { _onLostUserPtr = funcPtr; }

	void executeOnUpdate(std::shared_ptr<tdv::nuitrack::UserFrame> userFrame);
	void executeOnNewUser(int id);
	void executeOnLostUser(int id);
private:
	tdv::nuitrack::UserTrackerPIMPL* _tracker       = nullptr;
	OnUpdateRawFunctionPtr           _onUpdatePtr   = nullptr;
	OnNewUserRawFunctionPtr          _onNewUserPtr  = nullptr;
	OnLostUserRawFunctionPtr         _onLostUserPtr = nullptr;
};

extern "C" {

NUITRACK_API void nuitrack_registerUserTrackerCallback(NuitrackModule* tracker, UserTrackerCallbackWrapper* wrapper);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_CreateUserTracker(NuitrackModule**);

NUITRACK_API void nuitrack_DestroyUserTracker(NuitrackModule*);

NUITRACK_API uint64_t nuitrack_OnUserTrackerUpdate(NuitrackModule*, UserTrackerUpdateCallback);
NUITRACK_API uint64_t nuitrack_UserTrackerOnNewUser(NuitrackModule*, UserTrackerUserCallback);
NUITRACK_API uint64_t nuitrack_UserTrackerOnLostUser(NuitrackModule*, UserTrackerUserCallback);


NUITRACK_API void nuitrack_OnUserTrackerUpdateDisconnect(NuitrackModule*, uint64_t);
NUITRACK_API void nuitrack_UserTrackerOnNewUserDisconnect(NuitrackModule*, uint64_t);
NUITRACK_API void nuitrack_UserTrackerOnLostUserDisconnect(NuitrackModule*, uint64_t);

NUITRACK_API FrameHolder* nuitrack_GetUserTrackerData(NuitrackModule*);

NUITRACK_API void nuitrack_DestroyUserTrackerData(FrameHolder*);
NUITRACK_API void nuitrack_AddUserTrackerDataRef(FrameHolder*);

NUITRACK_API uint16_t nuitrack_GetUserFrameValueAtIndex(FrameHolder* ptr, int i);
NUITRACK_API uint16_t nuitrack_GetUserFrameValue(FrameHolder* ptr, int x, int y);

NUITRACK_API const uint16_t* nuitrack_GetUserFrameData(FrameHolder*);

NUITRACK_API size_t nuitrack_GetUserFrameNumUsers(FrameHolder*);
NUITRACK_API void   nuitrack_GetUserFrameUser(FrameHolder*, int, tdv::nuitrack::User*);
NUITRACK_API void   nuitrack_GetUserFrameFloor(FrameHolder*, tdv::nuitrack::Vector3*);
NUITRACK_API void   nuitrack_GetUserFrameFloorNormal(FrameHolder*, tdv::nuitrack::Vector3*);
NUITRACK_API float  nuitrack_GetUserTrackerProcessingTime(NuitrackModule*);

}


/// --- SkeletonTracker_CAPI.h
namespace tdv { namespace nuitrack { class SkeletonTrackerPIMPL; class SkeletonData; }}

using SkeletonTrackerDataPtr        = struct SkeletonTrackerData *;
using UserCallback                  = void(*)(NuitrackModule*, int);
using SkeletonTrackerUpdateCallback = void(*)(SkeletonTrackerDataPtr);

using SkeletonOnUpdateRawFunctionPtr   = void(*)(SkeletonTrackerData *, tdv::nuitrack::SkeletonTrackerPIMPL *);
using SkeletonOnNewUserRawFunctionPtr  = void(*)(tdv::nuitrack::SkeletonTrackerPIMPL *, int);
using SkeletonOnLostUserRawFunctionPtr = void(*)(tdv::nuitrack::SkeletonTrackerPIMPL*, int);

class SkeletonTrackerCallbackWrapper
{
public:

	// hpp
	void setSkeletonTracker  (tdv::nuitrack::SkeletonTrackerPIMPL* tracker) { _tracker = tracker;       }
	void setOnUpdateAddress  (SkeletonOnUpdateRawFunctionPtr funcPtr)       { _onUpdatePtr = funcPtr;   }
	void setOnNewUserAddress (SkeletonOnNewUserRawFunctionPtr funcPtr)      { _onNewUserPtr = funcPtr;  }
	void setOnLostUserAddress(SkeletonOnLostUserRawFunctionPtr funcPtr)     { _onLostUserPtr = funcPtr; }

	// cpp
	void executeOnUpdate  (std::shared_ptr<tdv::nuitrack::SkeletonData> data);
	void executeOnNewUser (tdv::nuitrack::cpp::SkeletonTracker::Ptr, int id);
	void executeOnLostUser(tdv::nuitrack::cpp::SkeletonTracker::Ptr, int id);

private:
	tdv::nuitrack::SkeletonTrackerPIMPL* _tracker       = nullptr;
	SkeletonOnUpdateRawFunctionPtr       _onUpdatePtr   = nullptr;
	SkeletonOnNewUserRawFunctionPtr      _onNewUserPtr  = nullptr;
	SkeletonOnLostUserRawFunctionPtr     _onLostUserPtr = nullptr;
};

extern "C" {

NUITRACK_API void nuitrack_registerSkeletonTrackerCallback(NuitrackModule*, SkeletonTrackerCallbackWrapper*);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_CreateSkeletonTracker(NuitrackModule**);

NUITRACK_API void nuitrack_DestroySkeletonTracker(NuitrackModule*);

NUITRACK_API uint64_t nuitrack_OnNewUser(NuitrackModule*, UserCallback);

NUITRACK_API uint64_t nuitrack_OnLostUser(NuitrackModule*, UserCallback);

NUITRACK_API uint64_t nuitrack_OnSkeletonUpdate(NuitrackModule*, SkeletonTrackerUpdateCallback);

NUITRACK_API void nuitrack_OnNewUserDisconnect(NuitrackModule*, uint64_t h);

NUITRACK_API void nuitrack_OnLostUserDisconnect(NuitrackModule*, uint64_t h);

NUITRACK_API void nuitrack_OnSkeletonUpdateDisconnect(NuitrackModule*, uint64_t h);

NUITRACK_API SkeletonTrackerDataPtr nuitrack_GetSkeletonTrackerData(NuitrackModule*);

NUITRACK_API void nuitrack_DestroySkeletonTrackerData(SkeletonTrackerDataPtr);
NUITRACK_API void nuitrack_AddSkeletonTrackerDataRef(SkeletonTrackerDataPtr);

NUITRACK_API int nuitrack_GetNumUsers(SkeletonTrackerDataPtr);

NUITRACK_API uint64_t nuitrack_GetSkeletonDataTimestamp(SkeletonTrackerDataPtr);

NUITRACK_API int nuitrack_GetSkeletonID(SkeletonTrackerDataPtr, int);

NUITRACK_API void nuitrack_GetSkeletonJoint(SkeletonTrackerDataPtr, int, tdv::nuitrack::JointType, tdv::nuitrack::Joint*);

NUITRACK_API bool nuitrack_IsAutoTracking(NuitrackModule*);

NUITRACK_API void nuitrack_SetAutoTracking(NuitrackModule*, bool);

NUITRACK_API bool nuitrack_IsTracking(NuitrackModule*, int);

NUITRACK_API void nuitrack_StartTracking(NuitrackModule*, int);

NUITRACK_API void nuitrack_StopTracking(NuitrackModule*, int);

NUITRACK_API void nuitrack_SetNumActiveUsers(NuitrackModule*, int);

NUITRACK_API float nuitrack_GetSkeletonTrackerProcessingTime(NuitrackModule*);

NUITRACK_API uint64_t nuitrack_GetSkeletonTrackerTimestamp(SkeletonTrackerDataPtr);

}



/// --- HandTracker_CAPI.h
namespace tdv { namespace nuitrack { class HandTrackerPIMPL; class HandTrackerData; }}

struct HandTrackerDataInner;

using OnHandUpdateRawFunctionPtr = void(*)(HandTrackerDataInner*, tdv::nuitrack::HandTrackerPIMPL*);

class HandTrackerCallbackWrapper
{
public:
    void setHandTracker(tdv::nuitrack::HandTrackerPIMPL* tracker) { _tracker = tracker; }
    void setFunctionAddress(OnHandUpdateRawFunctionPtr funcPtr) { _funcPtr = funcPtr; }

    void execute(std::shared_ptr<tdv::nuitrack::HandTrackerData> data);

private:
    tdv::nuitrack::HandTrackerPIMPL* _tracker = nullptr;
    OnHandUpdateRawFunctionPtr       _funcPtr = nullptr;
};

extern "C" {

NUITRACK_API void nuitrack_registerHandTrackerCallback(NuitrackModule*, HandTrackerCallbackWrapper*);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_CreateHandTracker(NuitrackModule**);
NUITRACK_API void                         nuitrack_DestroyHandTracker(NuitrackModule*);
NUITRACK_API float                        nuitrack_GetHandTrackerProcessingTime(NuitrackModule*);

using HandTrackerDataPtr        = HandTrackerDataInner *;
using HandTrackerUpdateCallback = void(*)(HandTrackerDataPtr);

NUITRACK_API uint64_t nuitrack_OnHandTrackerUpdate(NuitrackModule*, HandTrackerUpdateCallback);
NUITRACK_API void     nuitrack_OnHandTrackerUpdateDisconnect(NuitrackModule*, uint64_t);

NUITRACK_API uint64_t nuitrack_GetHandTrackerDataTimestamp(HandTrackerDataPtr);
NUITRACK_API int      nuitrack_HandTrackerGetNumUsers(HandTrackerDataPtr);
NUITRACK_API void     nuitrack_HandTrackerGetUserHands(HandTrackerDataPtr,
                                                       int,
                                                       int*,
                                                       tdv::nuitrack::Hand*,
                                                       tdv::nuitrack::Hand*);
NUITRACK_API void nuitrack_DestroyHandTrackerData(HandTrackerDataPtr);
NUITRACK_API void nuitrack_AddHandTrackerDataRef(HandTrackerDataPtr);
NUITRACK_API void nuitrack_ReceiveInnerHandTrackerData(NuitrackModule*, HandTrackerDataInner**);

}


/// --- GestureRecognizer_CAPI.h

namespace tdv {namespace nuitrack {

class GestureRecognizerPIMPL;
class GestureData;
class UserStateData;
class UserGesturesStateData;

}}

struct UsersStateChanges;
using GestureRecognizerDataPtr                  = struct GestureRecognizerData*;
using GestureRecognizerUserGesturesStateDataPtr = struct GestureRecognizerUserGesturesStateData *;

using OnNewGesturesRawFunctionPtr     = void(*)(GestureRecognizerData *, tdv::nuitrack::GestureRecognizerPIMPL *);
using OnUserStateChangeRawFunctionPtr = void(*)(UsersStateChanges *, tdv::nuitrack::GestureRecognizerPIMPL *);
using OnGestureUpdateRawFunctionPtr   = void(*)(GestureRecognizerUserGesturesStateData *, tdv::nuitrack::GestureRecognizerPIMPL *);

class GestureRecognizerCallbackWrapper
{
public:
	GestureRecognizerCallbackWrapper() : _recognizer(nullptr), _onUpdatePtr(nullptr),
			_onStateChangePtr(nullptr), _onNewGesturesPtr(nullptr) {}
	void setGestureRecognizer(tdv::nuitrack::GestureRecognizerPIMPL* recognizer) { _recognizer = recognizer; }

	void setOnNewGestureAddress(OnNewGesturesRawFunctionPtr funcPtr) { _onNewGesturesPtr = funcPtr; }
	void setOnUserStateChangeAddress(OnUserStateChangeRawFunctionPtr funcPtr) { _onStateChangePtr = funcPtr; }
	void setOnUpdateAddress(OnGestureUpdateRawFunctionPtr funcPtr) { _onUpdatePtr = funcPtr; }

	void executeOnUpdate(std::shared_ptr<tdv::nuitrack::UserGesturesStateData> data);
	void executeOnNewGestures(std::shared_ptr<tdv::nuitrack::GestureData> data);
	void executeOnUserStateChange(std::shared_ptr<tdv::nuitrack::UserStateData> data);
 private:
	tdv::nuitrack::GestureRecognizerPIMPL* _recognizer;
	OnNewGesturesRawFunctionPtr _onNewGesturesPtr;
	OnUserStateChangeRawFunctionPtr _onStateChangePtr;
	OnGestureUpdateRawFunctionPtr _onUpdatePtr;
};

extern "C" {

NUITRACK_API void nuitrack_registerGestureRecognizerCallback(NuitrackModule* tracker, GestureRecognizerCallbackWrapper* wrapper);

// Common functions
NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_CreateGestureRecognizer(NuitrackModule**);
NUITRACK_API void nuitrack_DestroyGestureRecognizer(NuitrackModule*);

NUITRACK_API void nuitrack_UserGesturesSetControlStatus(NuitrackModule*, bool);
NUITRACK_API float nuitrack_GetGestureRecognizerProcessingTime(NuitrackModule*);

// OnNewGesturesCallback

using GestureRecognizerNewGesturesCallback = void(*)(GestureRecognizerDataPtr);

NUITRACK_API uint64_t nuitrack_OnNewGestures(NuitrackModule*, GestureRecognizerNewGesturesCallback);
NUITRACK_API void nuitrack_OnNewGesturesDisconnect(NuitrackModule*, uint64_t);

NUITRACK_API uint64_t nuitrack_GetUserGesturesTimestamp(GestureRecognizerDataPtr);
NUITRACK_API int nuitrack_GetUserGesturesNumGestures(GestureRecognizerDataPtr);
NUITRACK_API void nuitrack_GetUserGesture(GestureRecognizerDataPtr, int, tdv::nuitrack::Gesture*);
NUITRACK_API void nuitrack_DestroyGestureRecognizerData(GestureRecognizerDataPtr);
NUITRACK_API void nuitrack_AddGestureRecognizerDataRef(GestureRecognizerDataPtr);

// OnUsersStateChangedCallback
using UsersStateChangesPtr = struct UsersStateChanges*;
using GestureRecognizerUsersStateChangedCallback = void(*)(UsersStateChangesPtr);

NUITRACK_API uint64_t nuitrack_OnUsersStateChanged(NuitrackModule*, GestureRecognizerUsersStateChangedCallback);
NUITRACK_API void nuitrack_OnUsersStateChangedDisconnect(NuitrackModule*, uint64_t);

NUITRACK_API uint64_t nuitrack_GetUsersStateChangesTimestamp(UsersStateChangesPtr);
NUITRACK_API int nuitrack_GetNumUsersStateChanges(UsersStateChangesPtr);
NUITRACK_API void nuitrack_GetUserStateChange(UsersStateChangesPtr, int, tdv::nuitrack::UserState*);
NUITRACK_API void nuitrack_DestroyUsersStateChanges(UsersStateChangesPtr);
NUITRACK_API void nuitrack_AddUsersStateChangesRef(UsersStateChangesPtr);

// OnUpdateCallback
using GestureRecognizerUpdateCallback = void(*)(GestureRecognizerUserGesturesStateDataPtr);

NUITRACK_API void nuitrack_DestroyUsersStateData(GestureRecognizerUserGesturesStateDataPtr);
NUITRACK_API void nuitrack_AddUsersStateDataRef(GestureRecognizerUserGesturesStateDataPtr);

NUITRACK_API uint64_t nuitrack_OnGesturesUpdate(NuitrackModule*, GestureRecognizerUpdateCallback);
NUITRACK_API void nuitrack_OnGesturesUpdateDisconnect(NuitrackModule*, uint64_t);

NUITRACK_API uint64_t nuitrack_GetUsersGesturesStateTimestamp(GestureRecognizerUserGesturesStateDataPtr);

NUITRACK_API int nuitrack_GetNumUsersGestures(GestureRecognizerUserGesturesStateDataPtr);
NUITRACK_API void nuitrack_GetUserStateData(GestureRecognizerUserGesturesStateDataPtr, int, tdv::nuitrack::UserState*);

NUITRACK_API int nuitrack_GetNumUserGestureState(GestureRecognizerUserGesturesStateDataPtr, int);
NUITRACK_API void nuitrack_GetUserGestureState(GestureRecognizerUserGesturesStateDataPtr, int, int, tdv::nuitrack::GestureState*);

}

/// CustomProvider::*
extern "C" NUITRACK_API void nuitrack_sendData(uint8_t  dataType,
                                               uint32_t width,
                                               uint32_t height,
                                               uint8_t* data,
                                               uint8_t  pixelType,
                                               uint64_t timestamp,
                                               uint32_t id);
