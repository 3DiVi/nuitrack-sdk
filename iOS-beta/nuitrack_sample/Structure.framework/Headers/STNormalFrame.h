/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STNormalFrame API

/** STNormalFrame instances store a processed normal frame with normal vector in each pixel.

See also:

- STNormalEstimator
*/
@interface STNormalFrame : NSObject

/// Image width.
@property (readonly, nonatomic) int width;

/// Image height.
@property (readonly, nonatomic) int height;

/// Pointer to the beginning of a contiguous chunk of (`width` * `height`) normal pixel values.
@property (readonly, nonatomic) const GLKVector3 *normals;

@end