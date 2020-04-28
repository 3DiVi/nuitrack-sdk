//
//  NuitrackModules.cpp
//  nuitrack_sample
//
//  Created by 3DiVi on 13.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#include "NuitrackModules.h"

#define DEPTHSENSOR_ENABLED
#define COLORSENSOR_ENABLED
#define USERTRACKER_ENABLED
#define SKELETONTRACKER_ENABLED
#define GESTURERECOGNIZER_ENABLED
#define HANDTRACKER_ENABLED
#define ISSUECOLBACK_ENABLED

using namespace tdv::nuitrack;
using namespace sample;

template<>
NuitrackModules::Ptr Singleton<NuitrackModules>::_instance = NuitrackModules::Ptr(new NuitrackModules);

NuitrackModules::NuitrackModules():
_issueUpdateHandle(0)
{
    clearCallbackData();
}

NuitrackModules::~NuitrackModules()
{
    clearCallbackData();
}

void NuitrackModules::onIssuesUpdate(IssuesData::Ptr data)
{
    _issuesData = data;
}

void NuitrackModules::onNewDepthFrame(DepthFrame::Ptr frame)
{
    _depthFrame = frame;
}

void NuitrackModules::onNewRGBFrame(RGBFrame::Ptr frame)
{
    _colorFrame = frame;
}

void NuitrackModules::onUserUpdate(UserFrame::Ptr frame)
{
    _userFrame = frame;
}

void NuitrackModules::onSkeletonUpdate(SkeletonData::Ptr userSkeletons)
{
    _skeletons = userSkeletons;
}

void NuitrackModules::onHandUpdate(HandTrackerData::Ptr handData)
{
    _handTrackerData = handData;
}

void NuitrackModules::onNewGesture(GestureData::Ptr gestureData)
{
}

void NuitrackModules::init()
{
    clearCallbackData();

#ifndef DEPTHSENSOR_ENABLED
    _depthSensor = 0;
#else
    _depthSensor = DepthSensor::create();
    _depthSensor->connectOnNewFrame([=](DepthFrame::Ptr data){this->onNewDepthFrame(data);});
#endif

#ifndef ISSUECOLBACK_ENABLED
    _issuesData = 0;
#else
    _issueUpdateHandle = Nuitrack::connectOnIssuesUpdate([=](IssuesData::Ptr data){this->onIssuesUpdate(data);});
#endif

#ifndef COLORSENSOR_ENABLED
    _colorSensor = 0;
#else
    _colorSensor = ColorSensor::create();
    _colorSensor->connectOnNewFrame([=](RGBFrame::Ptr data){this->onNewRGBFrame(data);});
#endif

#ifndef USERTRACKER_ENABLED
    _userTracker = 0;
#else
    _userTracker = UserTracker::create();
    _userTracker->connectOnUpdate([=](UserFrame::Ptr data){this->onUserUpdate(data);});
#endif
#ifndef SKELETONTRACKER_ENABLED
    _skeletonTracker = 0;
#else
    _skeletonTracker = SkeletonTracker::create();
    _skeletonTracker->connectOnUpdate([=](SkeletonData::Ptr data){this->onSkeletonUpdate(data);});
#endif

#ifndef GESTURERECOGNIZER_ENABLED
    _gestureRecognizer = 0;
#else
    _gestureRecognizer = GestureRecognizer::create();
    _gestureRecognizer->connectOnNewGestures([=](GestureData::Ptr data){this->onNewGesture(data);});
#endif

#ifndef HANDTRACKER_ENABLED
    _handTracker = 0;
#else
    _handTracker = HandTracker::create();
    _handTracker->connectOnUpdate([=](HandTrackerData::Ptr data){this->onHandUpdate(data);});
#endif
}

void NuitrackModules::release()
{
    Nuitrack::disconnectOnIssuesUpdate(_issueUpdateHandle);

    clearCallbackData();

    _depthSensor = 0;
    _colorSensor = 0;
    _userTracker = 0;
    _skeletonTracker = 0;
    _gestureRecognizer = 0;
    _handTracker = 0;
}

std::shared_ptr<MODULE_CLASS_NAME> NuitrackModules::getModule(NuitrackModule module)
{
    switch(module)
    {
        case DEPTH_SENSOR: return _depthSensor;
        case COLOR_SENSOR: return _colorSensor;
        case USER_TRACKER: return _userTracker;
        case SKELETON_TRACKER: return _skeletonTracker;
        case HAND_TRACKER: return _handTracker;
        case GESTURE_RECOGNIZER: return _gestureRecognizer;
        default:
            return 0;
    }
}

DepthSensor::Ptr NuitrackModules::getDepthSensorModule()
{
    return _depthSensor;
}

bool NuitrackModules::checkModule(NuitrackModule module)
{
    return (bool)getModule(module);
}

void NuitrackModules::waitForUpdate(NuitrackModule module)
{
    if (checkModule(module))
        Nuitrack::waitUpdate(getModule(module));
}

float NuitrackModules::getProcessingTime(NuitrackModule module)
{
    switch(module)
    {
        case USER_TRACKER: return _userTracker->getProcessingTime();
        case SKELETON_TRACKER: return _skeletonTracker->getProcessingTime();
        case HAND_TRACKER: return _handTracker->getProcessingTime();
        case GESTURE_RECOGNIZER: return _gestureRecognizer->getProcessingTime();
        default:
            return 0;
    }
}

void NuitrackModules::clearCallbackData()
{
    _depthFrame = 0;
    _colorFrame = 0;
    _userFrame = 0;
    _skeletons = 0;
    _handTrackerData = 0;
    _issuesData = 0;
}

DepthFrame::Ptr NuitrackModules::getDepthFrame()
{
    return _depthFrame;
}

RGBFrame::Ptr NuitrackModules::getColorFrame()
{
    return _colorFrame;
}

UserFrame::Ptr NuitrackModules::getUserFrame()
{
    return _userFrame;
}

SkeletonData::Ptr NuitrackModules::getSkeletonData()
{
    return _skeletons;
}

HandTrackerData::Ptr NuitrackModules::getHandTrackerData()
{
    return _handTrackerData;
}

IssuesData::Ptr NuitrackModules::getIssuesData()
{
    return _issuesData;
}
