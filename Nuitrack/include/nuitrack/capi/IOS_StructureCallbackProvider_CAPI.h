#ifndef STRUCTURE_CALLBACK_PROVIDER_CAPI_H_
#define STRUCTURE_CALLBACK_PROVIDER_CAPI_H_

#include "nuitrack/types/Export.h"
#include <stdint.h>

extern "C" NUITRACK_API void StructureCallbackProvider_addDelegate(uint64_t delegate);

extern "C" NUITRACK_API void StructureCallbackProvider_removeDelegate(uint64_t delegate);

#endif //STRUCTURE_CALLBACK_PROVIDER_CAPI_H_
