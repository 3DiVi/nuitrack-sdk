// Copyright 3DiVi 2025, Inc. All Rights Reserved.

#pragma once

#include <memory>
#include <functional>
#include "nuitrack/types/Export.h"
#include "nuitrack/types/Error.h"

namespace tdv { namespace nuitrack {
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
