/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark - STSensorController Types

/** Indicates the initialization status of the Structure Sensor.
 
See also:

- [STSensorController initializeSensorConnection]
*/
typedef NS_ENUM(NSInteger, STSensorControllerInitStatus)
{
/// Indicates controller uninitialized because the sensor was not found.
    STSensorControllerInitStatusSensorNotFound      = 0,
/// Indicates controller initialization succeeded.
    STSensorControllerInitStatusSuccess             = 1,
/// Indicates controller was previously initialized.
    STSensorControllerInitStatusAlreadyInitialized  = 2,
/// Indicates controller uninitialized because sensor is waking up.
    STSensorControllerInitStatusSensorIsWakingUp    = 3,
/// Indicates controller uninitialized because of a failure to open the connection.
    STSensorControllerInitStatusOpenFailed          = 4,
/** Indicates controller is uninitialized and sensor is not opened because the application is running in the background.

At the moment we do not support initialiazing the sensor while in the background.
*/
    STSensorControllerInitStatusAppInBackground     = 5,
};

/** Streaming Interruption Reason
 
See also:
 
- [STSensorControllerDelegate sensorDidStopStreaming:]
*/
typedef NS_ENUM(NSInteger, STSensorControllerDidStopStreamingReason)
{
/** Sensor stops streaming because of iOS app will resign active.
This can occur when apps are sent to the background, during fast app switching, or when the notification/control center appears.
*/
    STSensorControllerDidStopStreamingReasonAppWillResignActive = 0
};

/** Constants indicating the Structure Sensor streaming configuration.

See also:

- [STSensorController startStreamingWithOptions:error:]
*/
typedef NS_ENUM(NSInteger, STStreamConfig)
{
/// Invalid stream configuration.
    STStreamConfigInvalid = -1,
    
/// QVGA depth at 30 FPS.
    STStreamConfigDepth320x240 = 0,

/// QVGA depth at 30 FPS, aligned to the color camera.
    STStreamConfigRegisteredDepth320x240_Deprecated_OnlyForPre2017Devices __deprecated_msg("Hardware registration is deprecated and will provide worse results on newer (>= 2017) devices. Please use STStreamConfigDepth320x240 with registeredToColorFrame instead."),

/// QVGA depth and infrared at 30 FPS.
    STStreamConfigDepth320x240AndInfrared320x248,

/// QVGA infrared at 30 FPS.
    STStreamConfigInfrared320x248,

/// VGA depth at 30 FPS.
    STStreamConfigDepth640x480,

/// VGA infrared at 30 FPS.
    STStreamConfigInfrared640x488,

/// VGA depth and infrared at 30 FPS.
    STStreamConfigDepth640x480AndInfrared640x488,

/// VGA depth at 30 FPS, aligned to the color camera.
    STStreamConfigRegisteredDepth640x480_Deprecated_OnlyForPre2017Devices __deprecated_msg("Hardware registration is deprecated and will provide worse results on newer (>= 2017) devices. Please use STStreamConfigDepth640x480 with registeredToColorFrame instead."),
    
/// QVGA depth at 60 FPS. Note: frame sync is not supported with this mode.
    STStreamConfigDepth320x240_60FPS
};


/** Frame Sync Configuration.

Constants indicating whether the driver should attempt to synchronize depth or infrared frames with color frames from AVFoundation.

When frame sync is active (i.e. **not** equal to `STFrameSyncOff`), one of the following methods is used in lieu of [STSensorControllerDelegate sensorDidOutputDepthFrame:], depending on the selected configuration:

- [STSensorControllerDelegate sensorDidOutputSynchronizedDepthFrame:colorFrame:]
- [STSensorControllerDelegate sensorDidOutputSynchronizedInfraredFrame:colorFrame:]

You must then repeatedly call frameSyncNewColorBuffer: from the AVFoundation video capture delegate methods. Otherwise, the sensor controller delegate methods will never deliver any frames. This is simply because synchronized frames cannot be delivered if there are no color frames to synchronize.

@note Frame sync of depth+infrared+RGB and 60 FPS depth are not currently supported.
@note For frame sync to be effective, the AVCaptureDevice must be configured to have a min and max frame rate of 30fps.
*/
typedef NS_ENUM(NSInteger, STFrameSyncConfig)
{
    /// Default mode, no synchronization.
    STFrameSyncOff __attribute__((deprecated)) = 0,
    
    /// Frame sync between AVFoundation video frame and depth frame.
    STFrameSyncDepthAndRgb __attribute__((deprecated)),
    
    /// Frame sync between AVFoundation video frame and infrared frame.
    STFrameSyncInfraredAndRgb __attribute__((deprecated)),
    
} __deprecated_msg("Please switch to using kSTFrameSyncEnabledKey, which specifies a bool value, instead.");

/** Sensor Calibration Type

Calibration types indicate whether a Structure Sensor + iOS device combination has no calibration, approximate calibration, or a device specific calibration from Calibrator.app.
 
See also:

- [STSensorController calibrationType]
 */
typedef NS_ENUM(NSInteger, STCalibrationType)
{
    /// There is no calibration for Structure Sensor + iOS device combination.
    STCalibrationTypeNone = 0,
    
    /// There exists an approximate calibration Structure Sensor + iOS device combination.
    STCalibrationTypeApproximate,
    
    /// There exists a device specific calibration from Calibrator.app of this Structure Sensor + iOS device combination.
    STCalibrationTypeDeviceSpecific,
};

typedef NS_ENUM(NSInteger, STStreamPreset)
{
    STStreamPresetDefault = 0,
    STStreamPresetBodyScanning = 1,
    STStreamPresetOutdoor = 2,
    STStreamPresetRoomScanning = 3,
    STStreamPresetCloseRange = 4,
};

// Dictionary keys for `[STSensorController startStreamingWithOptions:error:]`.
extern NSString* const kSTStreamConfigKey;
extern NSString* const kSTFrameSyncConfigKey __attribute__ ((deprecated));
extern NSString* const kSTFrameSyncEnabledKey;
extern NSString* const kSTHoleFilterEnabledKey;
extern NSString* const kSTHighGainEnabledKey;
extern NSString* const kSTColorCameraFixedLensPositionKey;

extern NSString* const kSTInfraredSensorAutoExposureModeKey;
extern NSString* const kSTInfraredSensorManualExposureKey;
extern NSString* const kSTInfraredSensorManualGainKey;

extern NSString* const kSTDepthStreamPresetKey;
