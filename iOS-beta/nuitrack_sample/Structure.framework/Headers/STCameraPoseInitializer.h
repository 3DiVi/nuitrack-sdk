/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STCameraPoseInitializer Types

/// Dictionary keys for [STCameraPoseInitializer initWithVolumeSizeInMeters: options:].
extern NSString* const kSTCameraPoseInitializerStrategyKey;

/** Constants specifying a camera pose initialization strategy.

See also:

- [STCameraPoseInitializer initWithVolumeSizeInMeters:options:]
*/
typedef NS_ENUM(NSInteger, STCameraPoseInitializerStrategy)
{
/** Try to detect a ground plane and set the camera pose such that the cuboid scanning volume lies on top of it.
If no ground plane is found or if the device is not looking downward, place the scanning volume at the distance given by the central depth pixels.
In both cases, the cuboid orientation will be aligned with the provided gravity vector.
__Note:__ This strategy requires depth information from the Structure Sensor.
*/
    STCameraPoseInitializerStrategyTableTopCube = 0,

/** Align the camera orientation using the gravity vector, leaving the translation component to (0,0,0).
__Note:__ This strategy does not require depth information.
*/
    STCameraPoseInitializerStrategyGravityAlignedAtOrigin = 1,

/** Align the camera orientation using the gravity vector, and places the camera center at the center of the scanning volume.
__Note:__ This strategy does not require depth information.
*/
    STCameraPoseInitializerStrategyGravityAlignedAtVolumeCenter = 2,
};

/** Constants specifying a camera pose initialization output.

See also:

- <STCameraPoseInitializer>
*/
typedef struct
{
    /// Whether the pose initializer could find a good pose.
    BOOL hasValidPose;

    /// Estimated camera pose, taking Structure Sensor as a reference.
    GLKMatrix4 cameraPose;

    /// Whether the last cube placement was made with a supporting plane. Useful for STMapper.
    BOOL hasSupportPlane;

    /// Equation of the detected support plane (if hasSupportPlane is true)
    GLKVector4 supportPlane;

} STCameraPoseInitializerOutput;

#pragma mark - STCameraPoseInitializer API

/// Determine an initial camera pose to make the best use of the cuboid scanning volume.
@interface STCameraPoseInitializer : NSObject

/// Width, height and depth of the volume cuboid.
@property (nonatomic) GLKVector3 volumeSizeInMeters;

/// Return the last estimated pose. This is the recommended thread-safe way to get the output.
@property (nonatomic, readonly) STCameraPoseInitializerOutput lastOutput;

/// Most recent estimated camera pose, taking Structure Sensor as a reference.
@property (nonatomic, readonly) GLKMatrix4 cameraPose __deprecated_msg("use lastOutput instead.");

/// Whether the pose initializer could find a good pose.
@property (nonatomic, readonly) BOOL hasValidPose __deprecated_msg("use lastOutput instead.");

/// Whether the last cube placement was made with a supporting plane. Useful for STMapper.
@property (nonatomic, readonly) BOOL hasSupportPlane __deprecated_msg("use lastOutput instead.");

/** Initialize with all the required fields.

@param volumeSize The current volume size in meters. Not used by the `STCameraPoseInitializerStrategyGravityAlignedAtOrigin` strategy.
@param options The options dictionary. The valid keys are:

- `kSTCameraPoseInitializerStrategyKey`
  - Specifies the camera pose initialization strategy.
  - `NSNumber` integral value equal to one of the STCameraPoseInitializerStrategy constants.
  - Required.
*/
- (instancetype)initWithVolumeSizeInMeters:(GLKVector3)volumeSize
                                   options:(NSDictionary *)options;

/** Update the current pose estimate from a depth frame and a CoreMotion gravity vector, using the strategy specified at init.

@param gravityInDeviceFrame a gravity vector in IMU coordinates, e.g. as provided by CMDeviceMotion.gravity.
@param depthFrame the current processed depth from Structure Sensor. Can be `nil` if using the strategies `STCameraPoseInitializerStrategyGravityAlignedAtOrigin` or `STCameraPoseInitializerStrategyGravityAlignedAtVolumeCenter`.
@param error will contain detailed information if the estimation failed.

@return TRUE on success, FALSE on failure.
*/
- (BOOL)updateCameraPoseWithGravity:(GLKVector3)gravityInDeviceFrame depthFrame:(STDepthFrame *)depthFrame error:(NSError* __autoreleasing *)error;

/** Determine which pixels of a depth frame are inside the current scanning volume.

@param depthFrame the current processed depth from Structure Sensor.
@param outputMask should point to an allocated buffer of (`depthFrame.width * depthFrame.height`) pixels. A mask pixel will be 255 if the corresponding 3D point fits inside the volume, 0 if outside or if there is no depth.
*/
- (void)detectInnerPixelsWithDepthFrame:(STDepthFrame*)depthFrame mask:(uint8_t*)outputMask;

@end