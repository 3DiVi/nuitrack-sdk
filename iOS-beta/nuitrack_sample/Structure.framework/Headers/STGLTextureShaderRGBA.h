/* 
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STGLTextureShaderRGBA API

/// STGLTextureShaderRGBA instances can render OpenGL ES 2D textures in RGBA format.
@interface STGLTextureShaderRGBA : NSObject

/// Enable the underlying shader program.
- (void)useShaderProgram;

/** Render the texture on a fullscreen quad using the given GL_TEXTUREX unit.

@param textureUnit A given native OpenGL texture unit to render.
*/
- (void)renderTexture:(GLint)textureUnit;

@end