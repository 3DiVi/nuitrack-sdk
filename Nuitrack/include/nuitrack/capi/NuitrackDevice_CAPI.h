#ifndef NUITRACK_DEVICE_CAPI_H_
#define NUITRACK_DEVICE_CAPI_H_

#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/types/NuitrackDeviceCommon.h"

typedef struct NuitrackDeviceData* NuitrackDeviceDataPtr;

extern "C"
{

NUITRACK_API  tdv::nuitrack::ExceptionType nuitrack_GetDeviceList(
		NuitrackDeviceDataPtr* bufferOfDevices, int bufferSize);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_SetDevice(
		NuitrackDeviceDataPtr dev);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_deleteNuitrackDeviceImpl(
		NuitrackDeviceDataPtr dev);

/*
 * NuitrackDeviceImpl functions
 */

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getInfo(
		NuitrackDeviceDataPtr dev, int info_type, char* out);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getVideoModeList(
		NuitrackDeviceDataPtr dev, int stream_type, int list_index, tdv::nuitrack::device::VideoMode& out);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getVideoModeListSize(
		NuitrackDeviceDataPtr dev, int stream_type, int &out);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getSelectedVideoMode(
		NuitrackDeviceDataPtr dev, int stream_type, tdv::nuitrack::device::VideoMode& out);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_setVideoMode(
		NuitrackDeviceDataPtr dev, int stream_type, tdv::nuitrack::device::VideoMode vm);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getStringBufferSizeConst(int &out);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getDeviceListLimitConst(int &out);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_nuitrackDevice_getActivationStatus(
		NuitrackDeviceDataPtr dev, int &out);

NUITRACK_API void nuitrack_nuitrackDevice_activate(
		NuitrackDeviceDataPtr dev, const char* activation_key, tdv::nuitrack::nuitrack_error** e);
}

#endif /* NUITRACK_DEVICE_CAPI_H_ */
