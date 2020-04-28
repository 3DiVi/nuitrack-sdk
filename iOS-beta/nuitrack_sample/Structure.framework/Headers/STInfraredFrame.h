/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STInfraredFrame API

/** Infrared Frame.
 
STInfraredFrame is the raw infrared frame object for frames streaming from Structure Sensor.
*/
@interface STInfraredFrame : NSObject<NSCopying>

/// Contiguous chunk of `width * height` pixels.
@property (readwrite, nonatomic) uint16_t *data;

/// Frame width.
@property (readwrite, nonatomic) int width;

/// Frame height.
@property (readwrite, nonatomic) int height;

/** Capture timestamp in seconds since the iOS device boot (same clock as CoreMotion and AVCapture). */
@property (readwrite, nonatomic) NSTimeInterval timestamp;

@end