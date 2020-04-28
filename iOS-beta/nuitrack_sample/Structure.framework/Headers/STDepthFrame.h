/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>
#import <Structure/STColorFrame.h>

#import <GLKit/GLKit.h>


#pragma mark - STDepthFrame API

/** Depth Frame.

STDepthFrame is the raw depth frame object for frames streaming from Structure Sensor.
*/
@interface STDepthFrame : NSObject<NSCopying>

/// Frame width.
@property (readonly, nonatomic) int width;

/// Frame height.
@property (readonly, nonatomic) int height;

/// Contiguous chunk of `width * height` 16bit shift values.
@property (readonly, nonatomic) uint16_t *shiftData;

/// Contiguous chunk of `width * height` float depth values in millimeters.
@property (readonly, nonatomic) float *depthInMillimeters;

/// Return a version of the depth frame downsampled once.
@property (readonly, nonatomic) STDepthFrame *halfResolutionDepthFrame;

/// Capture timestamp in seconds since the iOS device boot (same clock as CoreMotion and AVCapture).
@property (readonly, nonatomic) NSTimeInterval timestamp;

/** Return a version of the depth frame aligned to the color camera viewpoint.

@param colorFrame By providing an STColorFrame a corresponding STDepthFrame will be returned
@warning Do not use the returned image after the original image has been released.
 */
- (STDepthFrame *)registeredToColorFrame:(STColorFrame*)colorFrame;

/** OpenGL projection matrix representing Structure Sensor virtual camera.
 
This matrix can be used to render a scene by simulating the same camera properties as the Structure Sensor depth camera.
 
@return A projection matrix.
*/
- (GLKMatrix4)glProjectionMatrix;

/** Intrinsic camera parameters.
 
 This struct can be used to get the intrinsic parameters of the current DepthFrame.
 
 @return A set of STIntrinsics intrinsic parameters.
 */
- (STIntrinsics) intrinsics;

/** Test if valid extrinsics exist

    This method will tell you if valid extrinsics for a bracket calibration currently exist for a given frame.

    This can be used to tell whether it's possible to register this frame to another iOS color frame.
*/
- (BOOL) hasValidExtrinsics;

/** Get the extrinsics relating the iOS camera to the depth sensor.
 
 The transformation matrix returned here is in the reference frame of the iOS camera. The coordinate frame is right handed: X right, Y down, Z out. Equivalently, this matrix can transform a 3D point expressed in the Structure Sensor depth stream coordinate system to the iOS camera coordinate system using the following operation
 
 3DPoint_IniOSFrame = iOSColorFromDepthExtrinsics * 3DPoint_InDepthFrame
 
 @return a 4x4 GLKMatrix in _column_ major order, with the correct extrinsics for the current sensor and lens configuration. This value does not change when streaming registered depth, as it reports the mechanical transform between the depth stream and the iOS camera. Will return a NAN matrix when uncalibrated.
 */
- (GLKMatrix4) iOSColorFromDepthExtrinsics;

/** Get the rigid body transformation (RBT) between the iOS color camera and the depth image viewpoint.
 
When using an un-registered mode, this transform is the same as [STSensorController colorCameraPoseInSensorCoordinateFrame:].
However, when using a registered depth mode, the depth frame is already aligned to the color camera viewpoint and thus this transform is identity.
 
The RBT represents the world motion of the RGB camera w.r.t. the Structure Sensor stream viewpoint.
The coordinate frame is right handed: X right, Y down, Z out. Equivalently, this matrix can transform a 3D point expressed in the iOS color camera coordinate system to the Structure Sensor depth stream coordinate system.
 
@param matrix4x4 This output parameter should be a pointer to 16 floating point values in _column_ major order. This is the default ordering of GLKMatrix4.
*/
- (void)colorCameraPoseInDepthCoordinateFrame:(float *)matrix4x4 __deprecated_msg("use STDepthFrame:iOSColorFromDepthExtrinsics: instead.");

/** Improve the accuracy of the depth data. Recommended for long-range data.

This function has a significant runtime cost. For instance, on iPad Air 2 it can take up to 5 milliseconds to complete.

@return FALSE if the correction could not be applied. This can happen when using hardware registered depth or a sensor with an old firmware.
*/
- (BOOL)applyExpensiveCorrection;

@end
