/* 
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/STColorFrame.h>
#import <Structure/STDepthFrame.h>
#import <Structure/STInfraredFrame.h>
#import <Structure/STSensorController+Types.h>


#pragma mark - STSensorController Delegate

/** Sensor Controller Delegate
 
The interface that your application-specific class must implement in order to receive sensor controller callbacks.
 
@warning When creating a new application implementing a sensor controller delegate, the main `Info.plist` needs to contain an additional key "`Supported external accessory protocols`", with the following array of values:
 
 - `io.structure.control`
 - `io.structure.depth`
 - `io.structure.infrared`
 
Without this modification to the plist, the app will not be able to connect to the sensor. All sample apps have this key/value array.
 
See also <[STSensorController sharedController]> & <[STSensorController delegate]>.
 
Delegate Registration Example:
 
    [ STSensorController sharedController ].delegate = self;
*/
__deprecated_msg("Please switch to the STCaptureSession API to handle sensor streaming. Go to http://structure.io/r/capture-session for more information on how to switch.")
@protocol STSensorControllerDelegate <NSObject>

/// @name Connection Status

/// Notify the delegate that the controller established a successful connection to the sensor.
- (void)sensorDidConnect;

/// Notify the delegate that the sensor was disconnected from the controller.
- (void)sensorDidDisconnect;

/** Notify the delegate that the sensor stopped streaming frames to the controller.

@param reason The reason why the stream was stopped. See: STSensorControllerDidStopStreamingReason.
*/
- (void)sensorDidStopStreaming:(STSensorControllerDidStopStreamingReason)reason;

/// @name Power Management

/// Notify the delegate that the sensor has left low power mode.
- (void)sensorDidLeaveLowPowerMode;

/// Notify the delegate that the sensor needs charging.
- (void)sensorBatteryNeedsCharging;

@optional

/// @name Colorless Frames

/** Notify the delegate that the sensor made a new depth frame available to the controller.

If the data is needed beyond the scope of this method, the depthFrame or its data must be copied by the receiver, e.g. using `[STDepthFrame copy]`.

@param depthFrame The new depth frame.
*/
- (void)sensorDidOutputDepthFrame:(STDepthFrame *)depthFrame;

/** Notify the delegate that the sensor made a new infrared frame available to the controller.

If the data is needed beyond the scope of this method, the irFrame and its data must be copied by the receiver.

@param irFrame The new infrared frame.
*/
- (void)sensorDidOutputInfraredFrame:(STInfraredFrame *)irFrame;

/// @name Color-synchronized Frames

/** Notify the delegate that the sensor made a new pair of depth and color frames available to the controller.

Frame sync methods will only be used if `kSTFrameSyncConfigKey` has been configured in [STSensorController startStreamingWithOptions:error:] to sync frames.

Data will only be delivered if [STSensorController frameSyncNewColorBuffer:] is called every time a new sample buffer is available.

The driver needs the CMSampleBuffers in order to return them through these methods.

If the STDepthFrame instance is needed beyond the scope of this function, the data must be copied by the receiver, e.g. using `[STDepthFrame copy]`.
 
See also:

- <[STSensorController startStreamingWithOptions:error:]>
- <[STSensorController frameSyncNewColorBuffer:]>

@param depthFrame The new STDepthFrame depth frame.
@param colorFrame The new STColorFrame color buffer.
*/
- (void)sensorDidOutputSynchronizedDepthFrame:(STDepthFrame *)depthFrame
                                   colorFrame:(STColorFrame *)colorFrame;

/** Notify the delegate that the sensor made a new pair of synchronized infrared and color frames available to the controller.

Frame sync methods will only be used if `kSTFrameSyncConfigKey` has been configured in [STSensorController startStreamingWithOptions:error:] to sync frames.

Data will only be delivered if [STSensorController frameSyncNewColorBuffer:] is called every time a new sample buffer is available.

The driver needs the CMSampleBuffers in order to return them through these methods.

If the STInfraredFrame is needed beyond the scope of this function, the data must be copied by the receiver.

See also:

- <[STSensorController startStreamingWithOptions:error:]>
- <[STSensorController frameSyncNewColorBuffer:]>

@param irFrame The new STInfraredFrame infrared frame.
@param colorFrame The STColorFrame new color buffer.
*/
- (void)sensorDidOutputSynchronizedInfraredFrame:(STInfraredFrame *)irFrame
                                      colorFrame:(STColorFrame *)colorFrame;

@end

//------------------------------------------------------------------------------
#pragma mark - STSensorController API

/** The sensor controller is the central point that manages all the interactions between the sensor and your application-specific delegate class.

Its only instance is available through the sharedController method.

Your custom delegate object can be registered using its delegate property.

See also:

- <STSensorControllerDelegate>
*/
__deprecated_msg("Please switch to the STCaptureSession API to handle sensor streaming. Go to http://structure.io/r/capture-session for more information on how to switch.")
@interface STSensorController : NSObject

/// @name Controller Setup

/** The STSensorController singleton.

Use it to register your application-specific STSensorControllerDelegate delegate.
*/
+ (STSensorController *)sharedController;

/** The STSensorControllerDelegate delegate.

It will receive all notifications from the sensor, as well as raw stream data.
*/
@property(nonatomic, assign) id<STSensorControllerDelegate> delegate;

/** Attempt to connect to the Structure Sensor.

@return Connection has succeeded only if the STSensorControllerInitStatus return value is either one of:

- STSensorControllerInitStatusSuccess
- STSensorControllerInitStatusAlreadyInitialized

@note Many methods (including startStreamingWithOptions:error:) will have no effect until this method succeeds at initializing the sensor.
*/
- (STSensorControllerInitStatus)initializeSensorConnection;

/** This will begin streaming data from the sensor and delivering data using the delegate methods.

Here is some sample code to get registered QVGA depth with depth/color frame sync:

    NSError* error;
    BOOL success = [sensorController
        startStreamingWithOptions:@{
            kSTStreamConfigKey:@(STStreamConfigRegisteredDepth320x240),
            kSTFrameSyncConfigKey:@(STFrameSyncDepthAndRgb)
        }
        error:&error
    ];

Here is some sample code to get VGA infrared images with high gain:

    NSError* error;
    BOOL success = [sensorController
        startStreamingWithOptions:@{
            kSTStreamConfigKey:@(STStreamConfigInfrared640x488),
            kSTHighGainEnabledKey:@YES
        }
        error:&error
    ];
 
@param options Specifies the sensor configuration to use. The valid dictionary keys are:

- `kSTStreamConfigKey`:
  - Specifies the desired streaming configuration.
  - `NSNumber` integral value equal to one of the STStreamConfig constants.
  - Required.
- `kSTFrameSyncConfigKey`:
  - Specifies whether frame sync should be active.
  - `NSNumber` integral value equal to one of the STFrameSyncConfig constants.
  - Defaults to `STFrameSyncOff`.
  - When active, depth frame will be synchronized with the color frames from AVFoundation.
- `kSTHoleFilterEnabledKey`:
  - Specifies whether to enable depth frame hole filtering.
  - `NSNumber` boolean value.
  - Defaults to `@YES` if the stream configuration includes depth.
  - When active, it enables a dilation filter over depth values that has the effect of filling holes.
  - Setting it to `@YES` if the stream configuration does not include depth is invalid.
- `kSTHighGainEnabledKey`:
  - Specifies whether to enable high gain mode.
  - `NSNumber` boolean value.
  - Defaults to `@NO`.
  - When set to `@YES` the sensor gain will be increased, causing better performance in dark or far away objects at the expense of some bright nearby objects.
  - See also: setHighGainEnabled:.
- `kSTColorCameraFixedLensPositionKey`:
  - Specifies a fixed lens position for the color camera.
  - `NSNumber` floating point value.
  - Required when using a registered depth mode.
  - The focus of the color camera has to remain fixed to this value when using a registered depth mode.

@param error will contain detailed information if the provided options are incorrect.

@return `YES` if the streaming options combination is valid, `NO` otherwise, filling in `error` with a detailed message.
*/
- (BOOL)startStreamingWithOptions:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/** Stop streaming data from the sensor.

@warning After this method is called, pending frames may still be delivered.
*/
- (void)stopStreaming;

/** Give the driver a color frame that will be used to synchronize shutters between the iOS camera and the Structure Sensor camera.

When receiving the CMSampleBufferRef from AVFoundation, you should only call this one method and do no other processing.
When a synchronized frame is found, one of the optional synchronized STSensorController delegate methods will be called, at which point you can then process/render the sampleBuffer.

@param sampleBuffer The new color buffer. __Note__: the supported resolutions are 640x480, 2048x1536, 2592x1936, 3264x2448 and 4032x3024.
*/
- (void)frameSyncNewColorBuffer:(CMSampleBufferRef)sampleBuffer;

/// @name Sensor Status

/// Check whether the controlled sensor is connected.
- (BOOL)isConnected;

/// Check whether the controlled sensor is in low-power mode. Low-power mode is used when the sensor is in an idle state, and is entered when the Structure Sensor is out of battery.
- (BOOL)isLowPower;

/// Return an integer in 0..100 representing the battery charge.
- (int)getBatteryChargePercentage;

/// @name Sensor Information

/// Return the name of the controlled sensor, or nil if no sensor is connected.
- (NSString *)getName;

/// Return the serial number of the controlled sensor, or nil if no sensor is connected.
- (NSString *)getSerialNumber;

/// Return the firmware revision of the controlled sensor, or nil if no sensor is connected.
- (NSString *)getFirmwareRevision;

/// Return the hardware revision of the controlled sensor, or nil if no sensor is connected.
- (NSString *)getHardwareRevision;

/// Return true if and only if your sensor firmware needs to be updated to a newer version to be fully compatible with this SDK.
- (bool) isFirmwareUpdateNeeded;

/** Launch the Calibrator app or prompt the user to install it.

An iOS app using the Structure Sensor should present its users with an opportunity to call this method when the following conditions are simultaneously met:

 - The sensor doesn't have a `calibrationType` with value `CalibrationTypeDeviceSpecific`.
 - A registered depth stream is required by the application.
 - The iOS device is supported by the Calibrator app.

@warning For this method to function, your app bundle's info plist must contain the following entry:

    <key>LSApplicationQueriesSchemes</key>
    <array>
        <string>structure-sensor-calibrator</string>
    </array>

@note See the calibration overlay sample code for more details.
@note This method is deprecated in favor of the direct C-function call.

*/
+ (BOOL)launchCalibratorAppOrGoToAppStore __deprecated_msg("use launchCalibratorAppOrGoToAppStore(void) instead.");

/** Return a boolean indicating whether an (at least) approximate depth-color calibration will be available when the sensor is connected to the current device.

This can be used to decide whether it is relevant to show color-specific UI elements before a sensor is connected.
*/
+ (BOOL)approximateCalibrationGuaranteedForDevice;

/** Returns the type of the current depth-color calibration as a STCalibrationType enumeration value.

This value can change depending on the actual device-sensor combination in use.

@warning This method will throw an exception when called while no sensor is connected.
*/
- (STCalibrationType)calibrationType;

/// @name Advanced Setup

/** Enable or disable high sensor gain after the stream was started.

This method can dynamically overwrite the `kSTHighGainEnabledKey` option specified when startStreamingWithOptions:error: was called.
 
@param enabled When set to `YES`, the sensor gain will be increased, causing better performance in dark or far away objects at the expense of some bright nearby objects.
*/
- (void)setHighGainEnabled:(BOOL)enabled;

/** Retrieve the current 4x4 transformation in _column_ major order between the iOS color camera and the Structure Sensor camera.

@param matrix4x4 This output parameter should be a pointer to 16 floating point values in _column_ major order. This is the default ordering of GLKMatrix4.
*/
- (void)colorCameraPoseInSensorCoordinateFrame:(float *)matrix4x4 __deprecated_msg("use STDepthFrame:iOSColorFromDepthExtrinsics: instead.");

@end
