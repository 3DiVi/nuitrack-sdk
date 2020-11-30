#ifndef NUITRACK_DEPTHSENSOR_CAPI_H_
#define NUITRACK_DEPTHSENSOR_CAPI_H_

#include <stdint.h>

#include "nuitrack/capi/Nuitrack_CAPI.h"
#include "nuitrack/types/OutputMode.h"
#include "nuitrack/types/Vector3.h"

typedef struct DepthSensorData* DepthSensorDataPtr;

typedef void(*DepthSensorUpdateCallback)(DepthSensorDataPtr);

namespace tdv{
namespace nuitrack{
class DepthSensor;
class DepthFrame;
}
}

typedef void (*OnNewFrameRawFunctionPtr)(DepthSensorData*, tdv::nuitrack::DepthSensor*);

class DepthSensorCallbackWrapper
{
 public:
	DepthSensorCallbackWrapper():_sensor(NULL), _funcPtr(NULL) {}
	void setDepthSensor(tdv::nuitrack::DepthSensor* sensor)
	{
		_sensor = sensor;
	}
	void setFunctionAddress(OnNewFrameRawFunctionPtr funcPtr)
	{
		_funcPtr = funcPtr;
	}

	void execute(std::shared_ptr<tdv::nuitrack::DepthFrame> depthFrame);
 private:
	tdv::nuitrack::DepthSensor* _sensor;
	OnNewFrameRawFunctionPtr _funcPtr;
};

extern "C" void NUITRACK_API nuitrack_registerDepthSensorCallback(NuitrackModule*, DepthSensorCallbackWrapper*);

extern "C" tdv::nuitrack::ExceptionType NUITRACK_API nuitrack_CreateDepthSensor(NuitrackModulePtr*);

extern "C" void NUITRACK_API nuitrack_DestroyDepthSensor(NuitrackModulePtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnDepthSensorUpdate(NuitrackModulePtr, DepthSensorUpdateCallback);
extern "C" void NUITRACK_API nuitrack_OnDepthSensorUpdateDisconnect(NuitrackModulePtr, uint64_t);

extern "C" DepthSensorDataPtr NUITRACK_API nuitrack_GetDepthSensorData(NuitrackModulePtr);

extern "C" void NUITRACK_API nuitrack_DestroyDepthSensorData(DepthSensorDataPtr);
extern "C" void NUITRACK_API nuitrack_AddDepthSensorDataRef(DepthSensorDataPtr);

extern "C" uint16_t NUITRACK_API nuitrack_GetDepthFrameValueAtIndex(DepthSensorDataPtr ptr, int i);
extern "C" uint16_t NUITRACK_API nuitrack_GetDepthFrameValue(DepthSensorDataPtr ptr, int x, int y);

extern "C" size_t NUITRACK_API nuitrack_GetDepthFrameRows(DepthSensorDataPtr);

extern "C" size_t NUITRACK_API nuitrack_GetDepthFrameCols(DepthSensorDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetDepthFrameID(DepthSensorDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_GetDepthFrameTimestamp(DepthSensorDataPtr);

extern "C" NUITRACK_API const uint16_t* nuitrack_GetDepthFrameData(DepthSensorDataPtr);

extern "C" NUITRACK_API NUITRACK_DEPRECATED const uint16_t* nuitrack_GetRgbFrameData(DepthSensorDataPtr);

extern "C" void NUITRACK_API nuitrack_GetDepthSensorOutputMode(NuitrackModulePtr, tdv::nuitrack::OutputMode*);

extern "C" tdv::nuitrack::CVector3 NUITRACK_API nuitrack_ctypes_ConvertProjToRealCoordsXYZ(NuitrackModulePtr, int, int, uint16_t);
extern "C" tdv::nuitrack::CVector3 NUITRACK_API nuitrack_ctypes_ConvertProjToRealCoordsVector3(NuitrackModulePtr, tdv::nuitrack::CVector3);

extern "C" tdv::nuitrack::CVector3 NUITRACK_API nuitrack_ctypes_ConvertRealToProjCoordsXYZ(NuitrackModulePtr, float, float, float);
extern "C" tdv::nuitrack::CVector3 NUITRACK_API nuitrack_ctypes_ConvertRealToProjCoordsVector3(NuitrackModulePtr, tdv::nuitrack::CVector3);

extern "C" bool NUITRACK_API nuitrack_IsDepthSensorMirror(NuitrackModulePtr);
extern "C" void NUITRACK_API nuitrack_SetDepthSensorMirror(NuitrackModulePtr, bool);


#endif /* NUITRACK_DEPTHSENSOR_CAPI_H_ */
