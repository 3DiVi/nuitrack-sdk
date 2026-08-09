//
//  Copyright © 2025 3divi. All rights reserved.
//

#pragma once

#include <nuitrack/Nuitrack.h>
#include "Singleton.h"

namespace sample {

namespace detail
{
    using namespace tdv::nuitrack;
}

enum NuitrackModule
{
    DEPTH_SENSOR = 0,
    COLOR_SENSOR,
    USER_TRACKER,
    SKELETON_TRACKER,
    HAND_TRACKER,
    GESTURE_RECOGNIZER,
    NUMBER_OF_MODULES
};

class NuitrackModules: public Singleton<NuitrackModules>
{
public:
    typedef std::shared_ptr<NuitrackModules> Ptr;

    NuitrackModules();
    ~NuitrackModules();

    void init();
    void release();

    bool checkModule(NuitrackModule module);
    void waitForUpdate(NuitrackModule module = SKELETON_TRACKER);
    float getProcessingTime(NuitrackModule module);
    void clearCallbackData();

    std::shared_ptr<detail::Module> getModule(NuitrackModule module);
    detail::DepthSensor::Ptr getDepthSensorModule();

    detail::DepthFrame::Ptr         getDepthFrame();
    detail::RGBFrame::Ptr           getColorFrame();
    detail::UserFrame::Ptr          getUserFrame();
    detail::SkeletonData::Ptr       getSkeletonData();
    detail::HandTrackerData::Ptr    getHandTrackerData();
    detail::IssuesData::Ptr         getIssuesData();

private:
    uint64_t _issueUpdateHandle;

    detail::DepthSensor::Ptr        _depthSensor;
    detail::ColorSensor::Ptr        _colorSensor;
    detail::UserTracker::Ptr        _userTracker;
    detail::SkeletonTracker::Ptr    _skeletonTracker;
    detail::GestureRecognizer::Ptr  _gestureRecognizer;
    detail::HandTracker::Ptr        _handTracker;

    detail::DepthFrame::Ptr         _depthFrame;
    detail::RGBFrame::Ptr           _colorFrame;
    detail::UserFrame::Ptr          _userFrame;
    detail::SkeletonData::Ptr       _skeletons;
    detail::HandTrackerData::Ptr    _handTrackerData;
    detail::IssuesData::Ptr         _issuesData;

    void onNewDepthFrame(detail::DepthFrame::Ptr _);
    void onNewRGBFrame(detail::RGBFrame::Ptr _);
    void onIssuesUpdate(detail::IssuesData::Ptr _);
    void onUserUpdate(detail::UserFrame::Ptr _);
    void onSkeletonUpdate(detail::SkeletonData::Ptr _);
    void onHandUpdate(detail::HandTrackerData::Ptr _);
    void onNewGesture(detail::GestureData::Ptr _);
};

}