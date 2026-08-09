#pragma once

#if defined C_API
#include "nuitrack/capi/Nuitrack_CAPI.h"

#elif defined HPP

#include <nuitrack/hpp/Nuitrack.h>

namespace tdv { namespace nuitrack {

using Nuitrack          = NuitrackPIMPL;
using DepthSensor       = DepthSensorPIMPL;
using ColorSensor       = ColorSensorPIMPL;
using UserTracker       = UserTrackerPIMPL;
using SkeletonTracker   = SkeletonTrackerPIMPL;
using HandTracker       = HandTrackerPIMPL;
using GestureRecognizer = GestureRecognizerPIMPL;
using IssuesData        = IssuesDataPIMPL;

namespace device {
using NuitrackDevice    = NuitrackDevicePIMPL;
}


}}

#else

#include "nuitrack/cpp/Nuitrack.h"

namespace tdv { namespace nuitrack {

using Nuitrack          = cpp::Nuitrack;
using DepthSensor       = cpp::DepthSensor;
using ColorSensor       = cpp::ColorSensor;
using UserTracker       = cpp::UserTracker;
using SkeletonTracker   = cpp::SkeletonTracker;
using HandTracker       = cpp::HandTracker;
using GestureRecognizer = cpp::GestureRecognizer;
using IssuesData        = cpp::IssuesData;

namespace device {
using NuitrackDevice    = cpp::NuitrackDevice;
}

}}

#endif
