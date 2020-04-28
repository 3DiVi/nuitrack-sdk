/* 
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>


#pragma mark - STDepthToRgba Types

/** Constants specifying a depth to color conversion strategy.

See also:

- [STDepthToRgba initWithOptions:error:]
*/
typedef NS_ENUM(NSInteger, STDepthToRgbaStrategy)
{
    /// Linear mapping using a color gradient – pure red encodes the minimal depth, and pure blue encodes the farthest possible depth.
    STDepthToRgbaStrategyRedToBlueGradient = 0,

    /// Linear mapping from closest to farthest depth as a grayscale intensity.
    STDepthToRgbaStrategyGray,
};

// Dictionary keys for `[STDepthToRgba initWithOptions:]`.
extern NSString* const kSTDepthToRgbaStrategyKey;


#pragma mark - STDepthToRgba API

/// Helper class to convert float depth data to RGB values for better visualization.
@interface STDepthToRgba : NSObject

/// Pointer to the RGBA values.
@property (nonatomic, readonly) uint8_t *rgbaBuffer;

/// Width of the output RGBA image.
@property (nonatomic, readonly) int width;

/// Height of the output RGBA image.
@property (nonatomic, readonly) int height;

/** Initialize with required parameters.

@param options The options dictionary. The valid keys are:
 
 - `kSTDepthToRgbaStrategyKey`:
   - Specifies the conversion strategy to use.
   - `NSNumber` integral value equal to one of the STDepthToRgbaStrategy constants.
   - Required.
*/
- (instancetype)initWithOptions:(NSDictionary *)options;

/** Convert the given depth frame to RGBA. The returned pointer is the same as the one accessed through `rgbaBuffer`.

@param frame The depth frame.
*/
- (uint8_t *)convertDepthFrameToRgba:(STDepthFrame *)frame;

@end
