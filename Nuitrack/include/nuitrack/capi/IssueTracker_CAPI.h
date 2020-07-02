#ifndef NUITRACK_ISSUE_TRACKER_CAPI_H_
#define NUITRACK_ISSUE_TRACKER_CAPI_H_

#include <memory>

namespace tdv{
namespace nuitrack{
class Issue;
class IssuesData;
class IssueTracker;
}
}

struct IssueTrackerData;


typedef void (*OnNewIssueRawFunctionPtr)(IssueTrackerData* data);

class IssueTrackerCallbackWrapper
{
public:
	typedef std::shared_ptr<IssueTrackerCallbackWrapper> Ptr;

	IssueTrackerCallbackWrapper() : _sensor(NULL), _funcPtr(NULL) {}
	void setIssueTracker(tdv::nuitrack::IssueTracker* sensor)
	{
		_sensor = sensor;
	}
	void setFunctionAddress(OnNewIssueRawFunctionPtr funcPtr)
	{
		_funcPtr = funcPtr;
	}

	void execute(std::shared_ptr<tdv::nuitrack::IssuesData> issuesData);
private:
	tdv::nuitrack::IssueTracker* _sensor;
	OnNewIssueRawFunctionPtr _funcPtr;
};

extern "C" NUITRACK_API void* nuitrack_getIssuesCallbackStruct();
extern "C" void NUITRACK_API nuitrack_setIssuesCallbackStruct(void*);

extern "C" void NUITRACK_API nuitrack_registerIssuesTrackerCallback(IssueTrackerCallbackWrapper* wrapper);

typedef struct IssueTrackerData* IssueTrackerDataPtr;
typedef void(*IssueTrackerUpdateCallback)(IssueTrackerDataPtr);

extern "C" uint64_t NUITRACK_API nuitrack_OnIssueTrackerUpdate(IssueTrackerUpdateCallback);
extern "C" void NUITRACK_API nuitrack_OnIssueTrackerUpdateDisconnect(uint64_t);
extern "C" void NUITRACK_API nuitrack_CreateIssueTrackerData(IssueTrackerDataPtr*, tdv::nuitrack::IssuesData*);
extern "C" void NUITRACK_API nuitrack_DestroyIssueTrackerData(IssueTrackerDataPtr);

extern "C" void NUITRACK_API nuitrack_AddIssueTrackerDataRef(IssueTrackerDataPtr);

extern "C" bool NUITRACK_API nuitrack_GetOcclusionIssue(IssueTrackerDataPtr dataPtr, int userId);
extern "C" void NUITRACK_API nuitrack_GetFrameBorderIssue(IssueTrackerDataPtr dataPtr, int userId,
	bool* left, bool* right, bool* top);

extern "C" bool NUITRACK_API nuitrack_GetSensorIssue(IssueTrackerDataPtr dataPtr,
										  char* buffer,
										  int bufferSize);


#endif /* NUITRACK_ISSUE_TRACKER_CAPI_H_ */
