/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

/** Structure SDK Umbrella **/
#import <Structure/STMesh.h>
#import <Structure/STScene.h>
#import <Structure/STMapper.h>
#import <Structure/STTracker.h>
#import <Structure/STKeyFrame.h>
#import <Structure/STColorizer.h>
#import <Structure/STWirelessLog.h>
#import <Structure/STDepthToRgba.h>
#import <Structure/STNormalFrame.h>
#import <Structure/STCubeRenderer.h>
#import <Structure/STOccFileWriter.h>
#import <Structure/STCaptureSession.h>
#import <Structure/STBackgroundTask.h>
#import <Structure/STNormalEstimator.h>
#import <Structure/STKeyFrameManager.h>
#import <Structure/STMeshIntersector.h>
#import <Structure/STSensorController.h>
#import <Structure/STGLTextureShaderGray.h>
#import <Structure/STGLTextureShaderRGBA.h>
#import <Structure/STGLTextureShaderYCbCr.h>
#import <Structure/STCameraPoseInitializer.h>

#if !defined(__cplusplus) && !defined (HAS_LIBCXX)
#   error "Structure framework requires the C++ runtime. See Structure SDK Reference."
# endif

// Make sure the deployment target is higher or equal to iOS 10.
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && (__IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_10_0)
#   error This version of Structure SDK only supports iOS 10 or higher.
#endif

typedef struct {
    const int major;
    const int minor;
    const int patch;
    const char* version;
} SDKVersion;

#ifdef __cplusplus
extern "C" 
{
#endif
    /** Returns a string specifying the current SDK version */
    SDKVersion currentSDKVersion(void);

    /** Launch the Calibrator app or prompt the user to install it.

    An iOS app using the Structure Sensor should present its users with an
    opportunity to call this method when the following conditions are
    simultaneously met:

    - The sensor doesn't have a `calibrationType` with value
    - `CalibrationTypeDeviceSpecific`. A registered depth stream is required by
    - the application. The iOS device is supported by the Calibrator app.

    @warning For this method to function, your app bundle's info plist must
    contain the following entry:

    <key>LSApplicationQueriesSchemes</key> <array>
    <string>structure-sensor-calibrator</string> </array>

    @note See the calibration overlay sample code for more details.
    */
    bool launchCalibratorAppOrGoToAppStore(void);

    /** Launch the Structure app or prompt the user to install it.

    An iOS app using the Structure Sensor should present its users with an
    opportunity to call this method when a firmware update is required. This can
    be queried from the STSensorController directly or by calling
    STCaptureSession:userInstructions.

    @warning For this method to function, your app bundle's info plist must
    contain the following entry:

    <key>LSApplicationQueriesSchemes</key> <array> <string>structure-app</string>
    </array>

    @note See the calibration overlay sample code for more details.
    */
    bool launchStructureAppOrGoToAppStore(void);
#ifdef __cplusplus
};
#endif
