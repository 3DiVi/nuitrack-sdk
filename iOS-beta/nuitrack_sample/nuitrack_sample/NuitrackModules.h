//
//  NuitrackModules.hpp
//  nuitrack_sample
//
//  Created by 3DiVi on 13.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#ifndef NuitrackModules_hpp
#define NuitrackModules_hpp

#include <nuitrack/Nuitrack.h>
#include "Singleton.h"

#define HEADER_ONLY_MODULE 

#ifdef HEADER_ONLY_MODULE
#define MODULE_CLASS_NAME HeaderOnlyAPI_Module
#else
#define MODULE_CLASS_NAME Module
#endif

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

    std::shared_ptr<detail::MODULE_CLASS_NAME> getModule(NuitrackModule module);
    detail::DepthSensor::Ptr getDepthSensorModule();

    detail::DepthFrame::Ptr getDepthFrame();
    detail::RGBFrame::Ptr getColorFrame();
    detail::UserFrame::Ptr getUserFrame();
    detail::SkeletonData::Ptr getSkeletonData();
    detail::HandTrackerData::Ptr getHandTrackerData();
    detail::IssuesData::Ptr getIssuesData();

private:
    uint64_t _issueUpdateHandle;

    detail::DepthSensor::Ptr _depthSensor;
    detail::ColorSensor::Ptr _colorSensor;
    detail::UserTracker::Ptr _userTracker;
    detail::SkeletonTracker::Ptr _skeletonTracker;
    detail::GestureRecognizer::Ptr _gestureRecognizer;
    detail::HandTracker::Ptr _handTracker;

    detail::DepthFrame::Ptr _depthFrame;
    detail::RGBFrame::Ptr _colorFrame;
    detail::UserFrame::Ptr _userFrame;
    detail::SkeletonData::Ptr _skeletons;
    detail::HandTrackerData::Ptr _handTrackerData;
    detail::IssuesData::Ptr _issuesData;

    void onNewDepthFrame(detail::DepthFrame::Ptr frame);
    void onNewRGBFrame(detail::RGBFrame::Ptr frame);
    void onIssuesUpdate(detail::IssuesData::Ptr data);
    void onUserUpdate(detail::UserFrame::Ptr frame);
    void onSkeletonUpdate(detail::SkeletonData::Ptr userSkeletons);
    void onHandUpdate(detail::HandTrackerData::Ptr handData);
    void onNewGesture(detail::GestureData::Ptr gestureData);
};

}

#endif /* NuitrackModules_hpp */
