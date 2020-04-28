/* 
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STGLTextureShaderGray API

/// STGLTextureShaderGray instances can render OpenGL ES 2D textures in single-channel luminance format.
@interface STGLTextureShaderGray : NSObject

/// Enable the underlying shader program.
- (void)useShaderProgram;

/** Render the texture on a fullscreen quad using the given GL_TEXTUREX unit.

@param lumaTextureUnit A given native OpenGL texture unit to render.
*/
- (void)renderWithLumaTexture:(GLint)lumaTextureUnit;

@end