// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <cstdint>

#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/types/OutputMode.h"
#include "nuitrack/types/Color3.h"

typedef struct ColorSensorData* ColorSensorDataPtr;

typedef void(*ColorSensorUpdateCallback)(ColorSensorDataPtr);

namespace tdv { namespace nuitrack {
class ColorSensor;
class RGBFrame;
}
}

typedef void (*OnNewRGBFrameRawFunctionPtr)(ColorSensorData*, tdv::nuitrack::ColorSensor*);

class ColorSensorCallbackWrapper{
 public:
	ColorSensorCallbackWrapper(): _sensor(nullptr), _funcPtr(nullptr) {}
	void setColorSensor(tdv::nuitrack::ColorSensor* sensor) { _sensor = sensor; }
	void setFunctionAddress(OnNewRGBFrameRawFunctionPtr funcPtr) { _funcPtr = funcPtr; }

	void execute(std::shared_ptr<tdv::nuitrack::RGBFrame> rgbFrame);
 private:
	tdv::nuitrack::ColorSensor* _sensor;
	OnNewRGBFrameRawFunctionPtr _funcPtr;
};

extern "C" void NUITRACK_API nuitrack_registerColorSensorCallback(NuitrackModule*, ColorSensorCallbackWrapper*);

extern "C" tdv::nuitrack::ExceptionType NUITRACK_API nuitrack_CreateColorSensor(NuitrackModulePtr*);

extern "C" void NUITRACK_API nuitrack_DestroyColorSensor(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_OnColorSensorUpdate(NuitrackModulePtr, ColorSensorUpdateCallback);
extern "C" void NUITRACK_API nuitrack_OnColorSensorUpdateDisconnect(NuitrackModulePtr, uint64_t handle);

extern "C" ColorSensorDataPtr NUITRACK_API nuitrack_GetColorSensorData(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_DestroyColorSensorData(ColorSensorDataPtr);
extern "C" void NUITRACK_API nuitrack_AddColorSensorDataRef(ColorSensorDataPtr);

extern "C" tdv::nuitrack::Color3 NUITRACK_API nuitrack_GetColorFrameValueAtIndex(ColorSensorDataPtr ptr, int i);
extern "C" tdv::nuitrack::Color3 NUITRACK_API nuitrack_GetColorFrameValue(ColorSensorDataPtr ptr, int x, int y);

extern "C" int NUITRACK_API nuitrack_GetColorFrameRows(ColorSensorDataPtr);

extern "C" int NUITRACK_API nuitrack_GetColorFrameCols(ColorSensorDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetColorFrameID(ColorSensorDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetColorFrameTimestamp(ColorSensorDataPtr);

extern "C" NUITRACK_API const tdv::nuitrack::Color3* nuitrack_GetColorFrameData(ColorSensorDataPtr);

extern "C" void NUITRACK_API nuitrack_GetColorSensorOutputMode(NuitrackModulePtr, tdv::nuitrack::OutputMode*);
