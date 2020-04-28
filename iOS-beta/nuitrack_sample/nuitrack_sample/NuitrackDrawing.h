//
//  NuitrackDrawing.hpp
//  nuitrack_sample
//
//  Created by 3DiVi on 07.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#ifndef NuitrackDrawing_hpp
#define NuitrackDrawing_hpp

#import <UIKit/UIKit.h>

#include "nuitrack/Nuitrack.h"
#include <stdio.h>

class NuitrackDrawing
{
public:
    static CGContextRef StartDrawing(UIImage* image);
    static UIImage* StopDrawing(CGContextRef ctx);

    static void IncreaseAllPixelsValue(CGContextRef ctx, float coef);
    static void DyeUsers(CGContextRef ctx);
    static void DrawSkeletons(CGContextRef ctx);
    static void DrawHandState(CGContextRef ctx);

    static void DrawNuitrackInfo(CGContextRef ctx);
    static void DrawText(CGContextRef ctx, NSString* str, float x, float y, size_t lenght);

private:
    static void DrawCircle(CGContextRef ctx, float x, float y, float r, UIColor* color, float thickness, UIColor* thickness_color);
    static void DrawCircle(CGContextRef ctx, float x, float y, float r, UIColor* color);

    static void DrawHand(CGContextRef ctx,tdv::nuitrack::Hand::Ptr hand, tdv::nuitrack::Skeleton userSkeleton, tdv::nuitrack::JointType jtype, UIColor* color);

    static void DrawLimbs(CGContextRef ctx, const std::vector<tdv::nuitrack::Joint>& joints);
    static void DrawOrientations(CGContextRef ctx, const std::vector<tdv::nuitrack::Joint>& joints, float length, int width);

    static void DrawLine(CGContextRef ctx, const tdv::nuitrack::Joint& j1, const tdv::nuitrack::Joint& j2);
    static void CGContextDrawLine(CGContextRef ctx, float x1, float y1, float x2, float y2, UIColor* color);
};


#endif /* NuitrackDrawing_hpp */
