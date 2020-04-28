/* 
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STGLTextureShaderYCbCr API

/// STGLTextureShaderYCbCr instances can render OpenGL ES 2D textures in YCbCr format.
@interface STGLTextureShaderYCbCr : NSObject

/// Enable the underlying shader program.
- (void)useShaderProgram;

/// Enable the underlying shader program and undistort the YCbCr texture.
- (void) useShaderProgramWithUndistortion:(STIntrinsics*)stIntrinsics;

/** Render the texture on a fullscreen quad using the given GL_TEXTUREX unit.

@param lumaTextureUnit A given native OpenGL luminance texture unit to render.
@param chromaTextureUnit A given native OpenGL chroma texture unit to render.
*/
- (void)renderWithLumaTexture:(GLint)lumaTextureUnit chromaTexture:(GLint)chromaTextureUnit;

@end