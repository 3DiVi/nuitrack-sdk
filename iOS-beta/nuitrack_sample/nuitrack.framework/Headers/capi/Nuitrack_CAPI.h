#ifndef NUITRACK_CAPI_H_
#define NUITRACK_CAPI_H_

#include "nuitrack/types/Export.h"
#include "nuitrack/types/Error.h"

#include "nuitrack/modules/NuitrackModule.h"

typedef NuitrackModule* NuitrackModulePtr;
using tdv::nuitrack::nuitrack_error;

extern "C"
{

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_Initialize();// __attribute__ ((deprecated));

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_InitializeFromConfig(const char*);
NUITRACK_API void nuitrack_InitializeFromConfig_E(const char*, nuitrack_error** error);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_SetConfigValue(const char*, const char*);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetConfigValue(const char* key, char* value, int bufferSize);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_Run();

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_Update();

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_SyncUpdate(NuitrackModulePtr);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_WaitSyncUpdate(NuitrackModulePtr);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_Release();

NUITRACK_API bool nuitrack_GetNuitrackModuleCanUpdate(NuitrackModule*);

NUITRACK_API uint64_t nuitrack_GetNuitrackModuleTimestamp(NuitrackModule*);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetLicense(char* value, int bufferSize);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetInstancesJson(char* value, int bufferSize);
NUITRACK_API void nuitrack_GetInstancesJsonSize(int* size, nuitrack_error** error);// deprecated
NUITRACK_API void nuitrack_GetInstancesJsonData(char* data, nuitrack_error** error); // deprecated
NUITRACK_API char* nuitrack_GetInstancesJsonDataAlloc(nuitrack_error** error);
NUITRACK_API void nuitrack_GetInstancesJsonDataClear(char* resultPtr);

NUITRACK_API void nuitrack_SetParam(const char* value);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetVersion(int* version);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetExceptionType(NuitrackModulePtr module);

NUITRACK_API void nuitrack_GetExceptionMessage(NuitrackModulePtr module, char * message, int size);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetErrorType(nuitrack_error* e);

NUITRACK_API const char* nuitrack_GetErrorMessage(nuitrack_error* e);

NUITRACK_API void nuitrack_DestroyError(nuitrack_error* e);

}

#endif /* NUITRACK_CAPI_H_ */
