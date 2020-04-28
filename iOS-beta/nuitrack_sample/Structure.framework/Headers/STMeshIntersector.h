/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>


#pragma mark - STMeshIntersector API

@interface STMeshIntersector : NSObject

- (instancetype)initWithMesh:(STMesh*)inputMesh;

/** Intersect the mesh with a ray specified by the origin and end points.
 If TRUE is returned, `intersection` will contain the first (x, y, z) coordinate on the mesh that the ray intersects when traveling from the origin to the end.
 @param origin The origin of ray.
 @param end The end of ray.
 @param intersection The intersection point to the mesh if intersection happens.
 @return TRUE if there is an intersection, FALSE otherwise
 */
- (BOOL)intersectWithRayOrigin:(GLKVector3)origin rayEnd:(GLKVector3)end intersection:(GLKVector3 *)intersection normal:(GLKVector3 *)normal ignoreBackFace:(BOOL)ignoreBackFace;

- (BOOL)intersectWithRayOrigin:(GLKVector3)origin rayEnd:(GLKVector3)end intersection:(GLKVector3 *)intersection intersectionFaceIndex:(int *) intersectionFaceIndex ignoreBackFace:(BOOL)ignoreBackFace;

- (BOOL)faceIsOnAPlane:(int)faceIndex normal:(GLKVector3 *)normal;

@end
