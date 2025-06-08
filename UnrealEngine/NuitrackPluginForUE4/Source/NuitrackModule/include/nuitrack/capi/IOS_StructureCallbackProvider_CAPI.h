// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include "nuitrack/types/Export.h"
#include <cstdint>

extern "C" NUITRACK_API void StructureCallbackProvider_addDelegate(uint64_t delegate);
extern "C" NUITRACK_API void StructureCallbackProvider_removeDelegate(uint64_t delegate);
