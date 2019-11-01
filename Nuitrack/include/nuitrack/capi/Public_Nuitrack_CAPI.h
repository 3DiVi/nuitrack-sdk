#ifndef PUBLIC_NUITRACK_CAPI_H_
#define PUBLIC_NUITRACK_CAPI_H_

#include <string>
#include <memory>
#include <functional>
#include "nuitrack/types/Export.h"
#include "nuitrack/types/Error.h"

namespace tdv{
namespace nuitrack{
class IssuesData;
class IssueTracker;
}
}

typedef std::function<void (std::shared_ptr<tdv::nuitrack::IssuesData>) > OnIssueUpdate;

extern "C"
{

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_SyncUpdatePublic(tdv::nuitrack::HeaderOnlyAPI_Module*);

NUITRACK_API tdv::nuitrack::ExceptionType nuitrack_WaitSyncUpdatePublic(tdv::nuitrack::HeaderOnlyAPI_Module*);

NUITRACK_API void nuitrack_getIssueTracker(tdv::nuitrack::IssueTracker**);


}

#endif /* PUBLIC_NUITRACK_CAPI_H_ */
