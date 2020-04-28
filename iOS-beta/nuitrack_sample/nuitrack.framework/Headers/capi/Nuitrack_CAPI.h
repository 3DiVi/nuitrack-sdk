#ifndef NUITRACK_CAPI_H_
#define NUITRACK_CAPI_H_

#include "nuitrack/types/Export.h"
#include "nuitrack/types/Error.h"


#include "nuitrack/modules/NuitrackModule.h"

typedef NuitrackModule* NuitrackModulePtr;

extern "C"
{

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_Initialize();// __attribute__ ((deprecated));

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_InitializeFromConfig(const char*);

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

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_GetExceptionType(NuitrackModulePtr module);

NUITRACK_API void nuitrack_GetExceptionMessage(NuitrackModulePtr module, char * message, int size);

}

#endif /* NUITRACK_CAPI_H_ */
