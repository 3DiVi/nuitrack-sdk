//
//  NuitrackDrawing.cpp
//  nuitrack_sample
//
//  Created by 3DiVi on 07.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#include "NuitrackDrawing.h"
#include "NuitrackModules.h"
#include "ImageConversions.h"

using namespace sample;
using namespace detail;

static const int userColor[8][3] =
{
    {200, 0, 0},    //cv::Vec3b(200, 0, 0),
    {0, 200, 0},    //cv::Vec3b(0, 200, 0),
    {0, 0, 200},    //cv::Vec3b(0, 0, 200),
    {255, 255, 0},  //cv::Vec3b(255, 255, 0),
    
    {0, 255, 255},  //cv::Vec3b(0, 255, 255),
    {255, 0, 255},  //cv::Vec3b(255, 0, 255),
    {127, 0, 255},  //cv::Vec3b(127, 0, 255),
    {127, 255, 0}   //cv::Vec3b(127, 255, 0)
};

struct Point3f{
    float x,y,z;
    Point3f(float _x, float _y, float _z){
        x = _x;
        y = _y;
        z = _z;
    }
    Point3f& operator=(const Point3f& obj2){
        x = obj2.x;
        y = obj2.y;
        z = obj2.z;
        return *this;
    }
    Point3f operator+(const Point3f obj2){
        return Point3f(x + obj2.x, y + obj2.y, z + obj2.z);
    }
    Point3f operator*(float mult){
        return Point3f(x * mult, y * mult, z * mult);
    }
};

CGContextRef NuitrackDrawing::StartDrawing(UIImage* image)
{
    // begin a graphics context of sufficient size
    UIGraphicsBeginImageContext(image.size);
    // draw original image into the context
    [image drawAtPoint:CGPointZero];
    // get the context for CoreGraphics
    return UIGraphicsGetCurrentContext();
}

UIImage* NuitrackDrawing::StopDrawing(CGContextRef ctx)
{
    UIImage *retImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return retImage;
}

void NuitrackDrawing::DrawNuitrackInfo(CGContextRef ctx)
{
    NSString* msg = @"";
    if (NuitrackModules::instance()->checkModule(USER_TRACKER))
    {
        msg = [NSString stringWithFormat:@"%@U : %1.1f ms\n", msg, NuitrackModules::instance()->getProcessingTime(USER_TRACKER)];
    }
    if (NuitrackModules::instance()->checkModule(SKELETON_TRACKER))
    {
       msg = [NSString stringWithFormat:@"%@S : %1.1f ms\n", msg, NuitrackModules::instance()->getProcessingTime(SKELETON_TRACKER)];
    }
    if (NuitrackModules::instance()->checkModule(GESTURE_RECOGNIZER))
    {
        msg = [NSString stringWithFormat:@"%@G : %1.1f ms\n", msg, NuitrackModules::instance()->getProcessingTime(GESTURE_RECOGNIZER)];
    }
    if (NuitrackModules::instance()->checkModule(HAND_TRACKER))
    {
        msg = [NSString stringWithFormat:@"%@H : %1.1f ms\n", msg, NuitrackModules::instance()->getProcessingTime(HAND_TRACKER)];
    }
    printf("%s", [msg UTF8String]);
}

void NuitrackDrawing::DrawText(CGContextRef ctx, NSString* str, float x, float y, size_t lenght)
{
    // maybe later
}

void NuitrackDrawing::DrawHandState(CGContextRef ctx)
{
    auto skeletons = NuitrackModules::instance()->getSkeletonData();
    auto handTrackerData = NuitrackModules::instance()->getHandTrackerData();
    
    if (!handTrackerData)
        return;

    for (auto userHands : handTrackerData ->getUsersHands())
    {
        Skeleton userSkeleton;
        uint8_t findSkeleton = 0;
        if (skeletons)
        {
            for (const Skeleton& skeleton : skeletons->getSkeletons())
            {
                if (skeleton.id == userHands.userId)
                {
                    userSkeleton = skeleton;
                    findSkeleton = 1;
                    break;
                }
            }
        }

        if (findSkeleton == 0)
            continue;

        if (userHands.leftHand)
        {
            DrawHand(ctx, userHands.leftHand, userSkeleton, JOINT_LEFT_WRIST, [UIColor blueColor]);
        }

        if (userHands.rightHand)
        {
            DrawHand(ctx, userHands.rightHand, userSkeleton, JOINT_RIGHT_WRIST, [UIColor redColor]);
        }
    }
}

void NuitrackDrawing::DrawHand(CGContextRef ctx, Hand::Ptr hand, Skeleton userSkeleton, JointType jtype, UIColor* color)
{
    if (!hand)
        return;

    auto free_hand_color = [UIColor colorWithRed:100.0/255.0 green:100.0/255.0 blue:100.0/255.0 alpha:1.0];

    CGSize ctx_size;
    ctx_size.width = CGBitmapContextGetWidth(ctx);
    ctx_size.height = CGBitmapContextGetHeight(ctx);

    DrawCircle(ctx,ctx_size.width * hand->x,
               ctx_size.height * hand->y,
               5.0, color,
               1, [UIColor whiteColor]);

    Vector3 proj = userSkeleton.joints[jtype].proj;
    DrawCircle(ctx,ctx_size.width * proj.x,
               ctx_size.height * proj.y,
               8.0, free_hand_color,
               4, [UIColor whiteColor]);

    if (hand->click)
    {
        DrawCircle(ctx,ctx_size.width *
                    proj.x,
                    ctx_size.height *
                    proj.y, 10.0, color);
    }
}

void NuitrackDrawing::DrawCircle(CGContextRef ctx, float x, float y, float r, UIColor* color, float thickness, UIColor* thickness_color)
{
    DrawCircle(ctx, x, y, r + thickness, thickness_color);
    DrawCircle(ctx, x, y, r, color);
}

void NuitrackDrawing::DrawCircle(CGContextRef ctx, float x, float y, float r, UIColor* color)
{
    // set stroking color and draw circle
    [color setFill];

    // make circle rect 5 px from border
    CGRect circleRect = CGRectMake(x-r, y-r, r*2, r*2);

    // draw circle
    CGContextFillEllipseInRect(ctx, circleRect);
}

void NuitrackDrawing::DyeUsers(CGContextRef ctx)
{
    auto userFrame = NuitrackModules::instance()->getUserFrame();

    if(!userFrame)
        return;

    auto users = userFrame->getUsers();
    uint8_t* userMap = (uint8_t*)userFrame->getData();

    auto issuesData = NuitrackModules::instance()->getIssuesData();
    std::map<int, bool> userIssue;

    CGSize ctx_size;
    ctx_size.width = CGBitmapContextGetWidth(ctx);
    ctx_size.height = CGBitmapContextGetHeight(ctx);

    if (issuesData)
    {
        for (auto user: users)
        {
            sample::detail::OcclusionIssue::Ptr oi = issuesData->getUserIssue<sample::detail::OcclusionIssue>(user.id);
            sample::detail::FrameBorderIssue::Ptr fi = issuesData->getUserIssue<sample::detail::FrameBorderIssue>(user.id);
            userIssue[user.id] = (fi || oi);
        }
    }

    unsigned char* ctx_data = (unsigned char *)CGBitmapContextGetData(ctx);
    size_t rowBytes = CGBitmapContextGetBytesPerRow(ctx);
    const int bytes_per_pixel = 4;

    for(int i = 0; i < ctx_size.height; i++)
    {
        for(int j = 0; j < ctx_size.width; j++)
        {
            uint16_t userID = *((uint16_t*)(userMap + i*(int)ctx_size.width*2 + j*2));
            if (userID)
            {
                float coeff = (userIssue[userID]) ? 0.3f : 1.0f;
                ctx_data[i*rowBytes + j*bytes_per_pixel + 0] = userColor[userID & 7][2] * coeff;
                ctx_data[i*rowBytes + j*bytes_per_pixel + 1] = userColor[userID & 7][1] * coeff;
                ctx_data[i*rowBytes + j*bytes_per_pixel + 2] = userColor[userID & 7][0] * coeff;
            }
        }
    }
}

void NuitrackDrawing::IncreaseAllPixelsValue(CGContextRef ctx, float coef)
{
    unsigned char *p = (unsigned char *)CGBitmapContextGetData(ctx);
    size_t rowBytes = CGBitmapContextGetBytesPerRow(ctx);
    size_t rowCount = CGBitmapContextGetHeight(ctx);
    const int bytes_per_pixel = 4;

    for(int i = 0; i < rowCount; i++)
    {
        for(int j = 0; j < rowBytes; j += bytes_per_pixel)
        {
            p[i*rowBytes + j + 0] *= coef;  //blue
            p[i*rowBytes + j + 1] *= coef;  //green
            p[i*rowBytes + j + 2] *= coef;  //red
            //p[bytes_per_pixel*i + 3];     //alpha
        }
    }
}

void NuitrackDrawing::DrawSkeletons(CGContextRef ctx)
{
    auto skeletons = NuitrackModules::instance()->getSkeletonData();
    
    if (!skeletons)
        return;
    
    for (auto skeleton : skeletons->getSkeletons())
    {
        DrawLimbs(ctx, skeleton.joints);
        DrawOrientations(ctx, skeleton.joints, 40.0f, 2);
    }
}

void NuitrackDrawing::DrawLimbs(CGContextRef ctx, const std::vector<Joint>& joints)
{
    DrawLine(ctx, joints[JOINT_HEAD], joints[JOINT_NECK]);
    DrawLine(ctx, joints[JOINT_NECK], joints[JOINT_LEFT_COLLAR]);
    DrawLine(ctx, joints[JOINT_LEFT_COLLAR], joints[JOINT_TORSO]);
    DrawLine(ctx, joints[JOINT_LEFT_COLLAR], joints[JOINT_LEFT_SHOULDER]);
    DrawLine(ctx, joints[JOINT_LEFT_COLLAR], joints[JOINT_RIGHT_SHOULDER]);
    DrawLine(ctx, joints[JOINT_WAIST], joints[JOINT_LEFT_HIP]);
    DrawLine(ctx, joints[JOINT_WAIST], joints[JOINT_RIGHT_HIP]);
    DrawLine(ctx, joints[JOINT_TORSO], joints[JOINT_WAIST]);
    DrawLine(ctx, joints[JOINT_LEFT_SHOULDER], joints[JOINT_LEFT_ELBOW]);
    DrawLine(ctx, joints[JOINT_LEFT_ELBOW], joints[JOINT_LEFT_WRIST]);
    DrawLine(ctx, joints[JOINT_LEFT_WRIST], joints[JOINT_LEFT_HAND]);
    DrawLine(ctx, joints[JOINT_RIGHT_SHOULDER], joints[JOINT_RIGHT_ELBOW]);
    DrawLine(ctx, joints[JOINT_RIGHT_ELBOW], joints[JOINT_RIGHT_WRIST]);
    DrawLine(ctx, joints[JOINT_RIGHT_WRIST], joints[JOINT_RIGHT_HAND]);
    DrawLine(ctx, joints[JOINT_RIGHT_HIP], joints[JOINT_RIGHT_KNEE]);
    DrawLine(ctx, joints[JOINT_LEFT_HIP], joints[JOINT_LEFT_KNEE]);
    DrawLine(ctx, joints[JOINT_RIGHT_KNEE], joints[JOINT_RIGHT_ANKLE]);
    DrawLine(ctx, joints[JOINT_LEFT_KNEE], joints[JOINT_LEFT_ANKLE]);
}

void NuitrackDrawing::DrawOrientations(CGContextRef ctx, const std::vector<Joint>& joints, float length, int width)
{
    auto depthSensor = NuitrackModules::instance()->getDepthSensorModule();
    auto depthFrame = depthSensor->getDepthFrame();

    if (!depthSensor || !depthFrame)
        return;

    CGSize ctx_size;
    ctx_size.width = CGBitmapContextGetWidth(ctx);
    ctx_size.height = CGBitmapContextGetHeight(ctx);

    // TODO remove usage of depthFrame (normalized coordinates in conversions)
    float xScale = (float)ctx_size.width / depthFrame->getCols();
    float yScale = (float)ctx_size.height / depthFrame->getRows();

    for (int j = 0; j < joints.size(); ++j)
    {
        if (joints[j].type == JOINT_NONE)
            continue;

        if (joints[j].confidence < 0.15)
            continue;

        Orientation orient = joints[j].orient;

        Point3f position(joints[j].real.x, joints[j].real.y, joints[j].real.z);
        Point3f x(orient.matrix[0], orient.matrix[3], orient.matrix[6]);
        Point3f y(orient.matrix[1], orient.matrix[4], orient.matrix[7]);
        Point3f z(orient.matrix[2], orient.matrix[5], orient.matrix[8]);

        Point3f positionX = position + x * length;
        Point3f positionY = position + y * length;
        Point3f positionZ = position + z * length ;

        Vector3 proj = depthSensor->convertRealToProjCoords(position.x, position.y, position.z);
        Vector3 projX = depthSensor->convertRealToProjCoords(positionX.x, positionX.y, positionX.z);
        Vector3 projY = depthSensor->convertRealToProjCoords(positionY.x, positionY.y, positionY.z);
        Vector3 projZ = depthSensor->convertRealToProjCoords(positionZ.x, positionZ.y, positionZ.z);

        CGContextDrawLine(ctx, proj.x * xScale, proj.y * yScale, projX.x * xScale, projX.y * yScale, [UIColor redColor]);
        CGContextDrawLine(ctx, proj.x * xScale, proj.y * yScale, projY.x * xScale, projY.y * yScale, [UIColor greenColor]);
        CGContextDrawLine(ctx, proj.x * xScale, proj.y * yScale, projZ.x * xScale, projZ.y * yScale, [UIColor blueColor]);
    }
}

void NuitrackDrawing::CGContextDrawLine(CGContextRef ctx, float x1, float y1, float x2, float y2, UIColor* color)
{
    [color setStroke];

    // Create the path first - rounded rectangle
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathMoveToPoint(path, NULL, x1, y1);
    CGPathAddLineToPoint(path, NULL, x2, y2);
    CGPathCloseSubpath(path);

    // Then use it in your draw commands
    CGContextSetLineJoin(ctx, kCGLineJoinMiter);
    CGContextSetLineWidth(ctx, 3.0);

    CGContextAddPath(ctx, path);
    CGContextDrawPath(ctx, kCGPathFillStroke);
    CGPathRelease(path);
}

void NuitrackDrawing::DrawLine(CGContextRef ctx, const Joint& j1, const Joint& j2)
{
    UIColor* line_color = [UIColor whiteColor];
    UIColor* j1_color = [UIColor whiteColor];
    UIColor* j2_color = [UIColor whiteColor];

    if (j1.confidence < 0.15 || j2.confidence < 0.15)
    {
        line_color = [UIColor colorWithRed:200.0/255.0 green:0.0 blue:0.0 alpha:1.0];
        if (j1.confidence < 0.15)
            j1_color = [UIColor colorWithRed:200.0/255.0 green:0.0 blue:0.0 alpha:1.0];
        if (j2.confidence < 0.15)
            j2_color = [UIColor colorWithRed:200.0/255.0 green:0.0 blue:0.0 alpha:1.0];
    }

    CGSize ctx_size;
    ctx_size.width = CGBitmapContextGetWidth(ctx);
    ctx_size.height = CGBitmapContextGetHeight(ctx);

    float xScale = (float)ctx_size.width;
    float yScale = (float)ctx_size.height;

    CGContextDrawLine(ctx, j1.proj.x * xScale, j1.proj.y * yScale, j2.proj.x * xScale, j2.proj.y * yScale, line_color);
    
    DrawCircle(ctx, j1.proj.x * xScale, j1.proj.y * yScale, 5, j1_color, 2, [UIColor whiteColor]);
    DrawCircle(ctx, j2.proj.x * xScale, j2.proj.y * yScale, 5, j2_color, 2, [UIColor whiteColor]);
    
}
