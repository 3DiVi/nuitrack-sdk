/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

// Dictionary keys for [STTracker initWithScene:options:].
extern NSString* const kSTTrackerTypeKey;
extern NSString* const kSTTrackerQualityKey;
extern NSString* const kSTTrackerTrackAgainstModelKey;
extern NSString* const kSTTrackerAvoidPitchRollDriftKey;
extern NSString* const kSTTrackerAvoidHeightDriftKey;
extern NSString* const kSTTrackerAcceptVaryingColorExposureKey;
extern NSString* const kSTTrackerBackgroundProcessingEnabledKey;
extern NSString* const kSTTrackerSceneTypeKey;
extern NSString* const kSTTrackerLegacyKey;

/** Constants specifying the tracking algorithm used by STTracker.

See also:

- [STTracker initWithScene:options:]
*/
typedef NS_ENUM(NSInteger, STTrackerType)
{
/** Specifies a tracker that will only use the depth information from Structure Sensor.

This tracker works best at close/mid-range, in combination with `kSTTrackerTrackAgainstModelKey`.
*/
    STTrackerDepthBased = 0,

/** Specifies a tracker that will use both the depth information from Structure Sensor and the color information from the iOS device camera.

Only `kCVPixelFormatType_420YpCbCr8BiPlanarFullRange` is supported for the color buffer format.
*/
    STTrackerDepthAndColorBased = 1,
};

/** Constants that specify profiles to optimize the tracker for.

 See also:

 - [STTracker initWithScene:options:]
 - [STTracker setOptions:]
 */
typedef NS_ENUM(NSInteger, STTrackerSceneType)
{
/** Specifies a profile that optimizes for scanning objects.

Assumes that the sensor is moving and can rotate and translate.
*/
    STTrackerSceneTypeObject,

/** Specifies a profile that optimizes for scanning objects on a turntable.

Assumes that the sensor is stationary and the object itself rotates.
*/
    STTrackerSceneTypeObjectOnTurntable,

/** Specifies a profile that optimizes for scanning rooms

Assumes that the sensor is moving and can rotate and translate. The scene captured should be on the scale of a typical room scan.
*/
    STTrackerSceneTypeRoom,
};

/** Constants specifying a tracking quality hint to STTracker.

See also:

- [STTracker initWithScene:options:]
- [STTracker setOptions:]
*/
typedef NS_ENUM(NSInteger, STTrackerQuality)
{
/// Best during scanning, but it will also take more CPU resources.
    STTrackerQualityAccurate = 0,

/// Designed for very fast tracking, it works best when tracking against a static mesh (e.g. after a scan has been done), or when the available CPU resources are limited.
    STTrackerQualityFast,
};

/** Constants specifying the quality of the STTracker output.

See also:

- [STTracker poseAccuracy]
- [STTracker trackerHints]
*/
typedef NS_ENUM(NSInteger, STTrackerPoseAccuracy)
{
/// The tracker cannot provide any accuracy information. This typically happens when it gets lost or before it sees any frame.
    STTrackerPoseAccuracyNotAvailable,

/// The tracker pose accuracy is very low. This can happen when the model has been out of view for a long time or if very few pixels have depth data.
    STTrackerPoseAccuracyVeryLow,

/// The tracker pose accuracy is low. This can happen when tracking against a model that is getting too close or out of view.
    STTrackerPoseAccuracyLow,

/// The tracker pose accuracy is approximate. This can happen during fast movements.
    STTrackerPoseAccuracyApproximate,

/// The tracker pose accuracy is nominal.
    STTrackerPoseAccuracyHigh,
};

/** Tracker Hints

An instance of this struct is provided by the tracker to provide feedback on how to reach a stable pose estimation.

See also:

- [STTracker trackerHints]
- [STTracker poseAccuracy]
*/
typedef struct
{
/// The tracker is completely lost and could not provide a pose estimation.
    bool trackerIsLost;

/// The sensor is too close to the scene, creating too many depth values below the sensor range.
    bool sceneIsTooClose;

/// When kSTTrackerTrackAgainstModelKey was set, this is true if the model being scanned in not in the view anymore.
    bool modelOutOfView;
} STTrackerHints;

#ifdef __cplusplus
extern "C" {
#endif
    STTrackerHints STTrackerHints_init (void);
#ifdef __cplusplus
};
#endif
