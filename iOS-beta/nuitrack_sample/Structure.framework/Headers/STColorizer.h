/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/STBackgroundTask.h>
#import <Structure/STScene.h>
#import <Structure/STMesh.h>

#pragma mark -STColorizer Types

/// Dictionary keys for [STColorizer newColorizeTaskWithMesh: scene: keyframes: completionHandler: options: error:].
extern NSString* const kSTColorizerTypeKey;
extern NSString* const kSTColorizerPrioritizeFirstFrameColorKey;
extern NSString* const kSTColorizerTargetNumberOfFacesKey;
extern NSString* const kSTColorizerQualityKey;

/** Constants specifying a colorization strategy for STColorizer.

See also:

- [STColorizer newColorizeTaskWithMesh:scene:keyframes:completionHandler:options:error:]
*/
typedef NS_ENUM(NSInteger, STColorizerType)
{
/// Generate a color for each vertex of the mesh. Best for small objects.
    STColorizerPerVertex = 0,

/** Generate a global texture map, and UV coordinates for each vertex of the mesh. Optimized for large rooms.
    __Note:__ Only 640x480 color images are supported by this colorizer.
*/
    STColorizerTextureMapForRoom = 1,

/// Generates a global texture map, and UV coordinates for each vertex of the mesh. Optimized for objects and people.
    STColorizerTextureMapForObject = 2,
};

/// Constants specifying the quality of STColorizer.
typedef NS_ENUM(NSInteger, STColorizerQuality)
{
/// Use this when speed is not a concern.
    STColorizerUltraHighQuality = 0,

/// Use this to balance between quality and speed.
    STColorizerHighQuality = 1,

/// Use this option when speed is a concern.
    STColorizerNormalQuality = 2,
};


#pragma mark - STColorizer API

/// Uses the color images from a vector of STKeyFrame to colorize an STMesh.
@interface STColorizer : NSObject

/** Returns a background task to colorize the given mesh using the provided keyframes.

@param mesh The STMesh to colorize.
@param scene The STScene context.
@param keyframes Array of keyframes, e.g. as provided by STKeyFrameManager.
@param completionHandler Block to execute once the task is finished or cancelled.
@param options The options dictionary. The valid keys are:

- `kSTColorizerTypeKey`:
  - Specifies the colorizing algorithm.
  - NSNumber integral value equal to one the STColorizerType constants.
  - Required.
- `kSTColorizerPrioritizeFirstFrameColorKey`:
  - Specifies whether the colorizer should give the first frame the highest priority.
  - `NSNumber` boolean value.
  - Defaults to `@NO`.
  - Particularly useful when we want to emphasize the appearance in the first frame, for example, when scanning a human face.
  - Only supported by `STColorizerTextureMapForObject`.
- `kSTColorizerTargetNumberOfFacesKey`:
  - Specifies a target number of faces for the final mesh.
  - NSNumber integral value.
  - Defaults to `@(20000)`.
  - Only supported by `STColorizerTextureMapForObject`.
- `kSTColorizerQualityKey`:
  - Specifies the desired speed/quality trade-off.
  - NSNumber integral value equal to one the STColorizerQuality constants.
  - Defaults to `STColorizerHighQuality`.
  - Only `STColorizerTextureMapForObject` will honor this option.

@param error will contain detailed information if the provided options are incorrect.
@note All the keyframes must have the same image size.
*/
+ (STBackgroundTask*)newColorizeTaskWithMesh:(STMesh *)mesh
                                       scene:(STScene*)scene
                                   keyframes:(NSArray *)keyframes
                           completionHandler:(void(^)(NSError *error))completionHandler
                                     options:(NSDictionary *)options
                                       error:(NSError* __autoreleasing *)error;

@end
