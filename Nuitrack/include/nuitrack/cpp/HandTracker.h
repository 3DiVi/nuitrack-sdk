#pragma once

#include <functional>

#include "nuitrack/cpp/Export.h"
#include "nuitrack/cpp/HandTrackerData.h"
#include "nuitrack/cpp/Module.h"

namespace tdv { namespace nuitrack { namespace cpp {

class HandTracker: public Module
{
public:
    using  Ptr = std::shared_ptr<HandTracker>;
    NUITRACK_API static Ptr create();

    using OnUpdate = std::function<void (HandTrackerData::Ptr)>;

    virtual uint64_t connectOnUpdate(const OnUpdate& callback) = 0;
    virtual void     disconnectOnUpdate(uint64_t handler) = 0;

    virtual HandTrackerData::Ptr getData() = 0;

    virtual float getProcessingTime() const = 0;
};

}}}
