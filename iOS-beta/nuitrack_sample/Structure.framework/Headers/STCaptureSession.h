/*
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/STCaptureSession+Types.h>
#import <Structure/STSensorController+Types.h>
#import <Structure/STOccFileWriter.h>


#pragma mark - STCaptureSessionDelegate API

/** Capture Session Delegate

The interface that your application-specific class must implement in order to receive capture session callbacks.

These callbacks replace the previous callbacks used when initializing the iOS camera and Structure Sensor separately.

@warning When creating a new application implementing a sensor controller delegate, the main `Info.plist` needs to contain an additional key "`Supported external accessory protocols`", with the following array of values:

 - `io.structure.control`
 - `io.structure.depth`
 - `io.structure.infrared`

Without this modification to the plist, the app will not be able to connect to the sensor. All sample apps have this key/value array.

See also <[STCaptureSession delegate]>

Delegate Registration Example:

    [STCaptureSession newCaptureSession].delegate = self;
*/
@protocol STCaptureSessionDelegate <NSObject>

/// @name Connection Status

/** Notify the delegate that the sensor entered a given mode.

If the sensor is not being used (using iOS camera only), then this delegate will
never be signaled, however is still required to be implemented (can be a no-op).

The modes are described as follows:

 - Ready : The sensor is connected and available to stream.
 - Waking up : The sensor is in the process of leaving low-power mode.
 - Not Connected : The sensor is not connected.
 - Battery depleted : The battery has been depleted and the sensor should be charged.
 - Unknown : The sensor has entered an unknown state.

@param captureSession The capture session object that signaled the delegate.
@param mode The mode that the sensor has entered. See: STCaptureSessionSensorMode.
*/
- (void)captureSession:(STCaptureSession *)captureSession sensorDidEnterMode:(STCaptureSessionSensorMode)mode;

/** Notify the delegate that the color camera entered a given mode.

If the color camera is not being used (using Structure Sensor only), then this
delegate will never be signaled, however is still required to be implemented
(can be a no-op).

The modes are described as follows:

 - Ready : The color camera has connected and available to stream.
 - Permission denied : The color camera cannot be connected to because the permission was denied by the user.
 - Unknown : The color camera has entered an unknown state.

@param captureSession The capture session object that signaled the delegate.
@param mode The mode that the iOS color camera has entered. See STCaptureSessionColorCameraMode.
*/
- (void)captureSession:(STCaptureSession *)captureSession colorCameraDidEnterMode:(STCaptureSessionColorCameraMode)mode;

@optional

/// @name Power Management

/** Notify the delegate that the sensor is connected or disconnected from the charger.

The modes are described as follows:

 - Connected : The charger is connected.
 - Disconnected : The charger is disconnected.
 - Unknown : The sensor charging state is unknown.

@param captureSession The capture session object that signaled the delegate.
@param chargerState The mode that the iOS color camera has entered. See STCaptureSessionSensorChargerState.
*/
- (void)captureSession:(STCaptureSession *)captureSession sensorChargerStateChanged:(STCaptureSessionSensorChargerState)chargerState;

/// @name AVCaptureSession Status

/** Notify the delegate that the AVCaptureSession for streaming iOS color camera frames has been started. This can be used to set both exposure and whitebalance to auto.

@param captureSession The capture session object that signaled the delegate.
@param avCaptureSession The AVCaptureSession object used to control the iOS color cameras.
*/
- (void)captureSession:(STCaptureSession *)captureSession didStartAVCaptureSession:(AVCaptureSession *)avCaptureSession;

/** Notify the delegate that the AVCaptureSession for streaming iOS color camera frames has been stopped.

@param captureSession The capture session object that signaled the delegate.
@param avCaptureSession The AVCaptureSession object used to control the iOS color cameras.
 */
- (void)captureSession:(STCaptureSession *)captureSession didStopAVCaptureSession:(AVCaptureSession *)avCaptureSession;

/// @name Capture Session sample output

/** Notify the delegate of data arriving (of a given sample type).

The sample types can be broken down as follows:

 - DepthFrame : The sample dictionary contains an entry for an STDepthFrame.
 - ColorFrame : The sample dictionary contains an entry for an STColorFrame.
 - InfraredFrame : The sample dictionary contains an entry for an STInfraredFrame.
 - SynchronizedFrames : The sample dictionary contains entries for synchronized depth, color, or infrared frames.
 - DeviceMotionData : The sample dictionary contains an entry for iOS CoreMotion data.
 - GyroData : The sample dictionary contains an entry for raw gyroscope data.
 - AccelData : The sample dictionary contains an entry for raw accelerometer data.

These all correspond to the kSTCaptureSessionSampleEntryXXXKey key entries at the top of this file.

@param captureSession The capture session object that signaled the delegate.
@param sample An NSDictionary containing the sample objects (e.g. STDepthFrame, STColorFrame, etc) specified by the sample type.
@param type The type of data sent from the capture session. See STCaptureSessionSampleType.
*/
- (void)captureSession:(STCaptureSession *)captureSession didOutputSample:(NSDictionary *)sample type:(STCaptureSessionSampleType)type;

/** Notify the delegate that the lens detector has determined a change in the state of the lens

This delegate will function differently based on the value of
`_captureSession.lensDetection`. Explicitly:

 - STLensDetectorOff : This delegate will never be notified; the detector is turned off.
 - STLensDetectorOn : This delegate will be notified of the lens it detects, after setting `_captureSession.lens` to that value (if known).
 - STLensDetectorWarnOnMismatch : The delegate will be notified of the lens it detects, but does not change the lens type that the capture session has set.

In all cases above the lens type can still be set manually, however be wary of
setting the lens type manually when the lens detector is on (not WarnOnMismatch),
as the value of the lens type is likely to be overwritten.

The status of the lens that can be sent to this delegate will be one of the following:

 - Normal : There is no WVL unit attached to the Structure Sensor bracket.
 - WideVisionLens : There is a WVL unit attached to the StructureSensor bracket.
 - PerformingInitialDetection : The detector has started, but has not yet collected enough unique frames to make a decision.
 - Unknown : The detector cannot fully determine if a WVL unit is attached or not attached to the Structure Sensor bracket.

@param captureSession The capture session object that signaled the delegate.
@param detectedLensStatus The status of the lens that the detector has detected. See STDetectedLensStatus.
*/
- (void)captureSession:(STCaptureSession *)captureSession onLensDetectorOutput:(STDetectedLensStatus)detectedLensStatus;

@end


//------------------------------------------------------------------------------
#pragma mark - STCaptureSession API

/** The capture session is the central point that manages all interactions between the sensor, iOS color camera, and your application-specific delegate class.

More than one instance of the capture session can be created, however only one
instance can connect to the sensor at a given time, and iOS will restrict you
from using more than one video device at a time.

Your custom delegate object can be registered using its delegate property.

See also:

 - <STCaptureSessionDelegate>
*/
@interface STCaptureSession : NSObject

/// @name Capture Session instantiation and factory methods

/** Creates a new capture session.

This creates a capture session expecting to stream data from the iOS color
camera and Structure Sensor.
*/
+ (instancetype) newCaptureSession;

/** Creates a new capture session with the iOS color camera disabled.

This creates a capture session that streams just Structure Sensor data.
*/
+ (instancetype) newCaptureSessionWithIOSCameraDisabled;

/** Creates a new capture session from an OCC file.

This creates a capture session expecting to not connect to any sensors, but to
read and stream direct sensor data from an OCC file and function as if a sensor
was directly connected. This allows for playing back recorded data as if it were
live.
*/
+ (instancetype) newCaptureSessionFromOccFile:(NSString*)occFilePath;

/// @name Capture Session delegate properties

/** The STCaptureSession delegate queue.

This is the queue / thread that the delegate callbacks are expected to be
executed on.

Defaults to `dispatch_get_main_queue()`.
*/
@property(nonatomic) dispatch_queue_t delegateQueue;

/** The STCaptureSession delegate.

Use it to register your application-specific STCaptureSessionDelegate delegate.

Defaults to nil.
*/
@property(nonatomic, assign) id<STCaptureSessionDelegate> delegate;

/// @name Capture Session streaming

/** Controls whether to stream data from connected sensors.

Can be thought of as "whether we would like to be streaming."

Streaming can only be enabled / disabled after `startMonitoringWithOptions:options` has been called.

See also:

 - <[STCaptureSession startMonitoringWithOptions:options];>
*/
@property(nonatomic) BOOL streamingEnabled; // whether we'd like to stream

/** A property to inform the user whether or not streaming is actually occurring.

See also:

 - <[STCaptureSession streamingEnabled];>
*/
@property(nonatomic,readonly) BOOL isStreaming; // whether we are actually streaming

/// @name Capture Session settings and configuration

/** Modify or get dynamic properties of the capture session.

These properties represent dynamic options that can be configured at any point.
Examples of this include color camera exposure, white balance, etc. A simple
example could be as follows:

    _captureSession.properties = @{
        kSTCaptureSessionPropertyIOSCameraExposureModeKey: @(STCaptureSessionIOSCameraExposureModeAuto),
        kSTCaptureSessionPropertyIOSCameraWhiteBalanceModeKey: @(STCaptureSessionIOSCameraWhiteBalanceModeAuto),
    };

In this example, both the exposure and white balance on the iOS color camera are
set to auto, and will be automatically handled by iOS.

@warning It is an error to try and set auto-exposure and a locked ISO value. An exception will be raised if this combination of keys are used.

You can identify which keys correspond to dynamic properties, as keys will be
named kSTCaptureSessionPropertyXXX.

- `kSTCaptureSessionPropertyIOSCameraFocusModeKey` :
  - Specifies what mode to set the color camera focus to.
  - `NSInteger` integral value equal to one of the `STCaptureSessionIOSCameraFocusMode` constants.
  - Defaults to a locked focus position set at calibration time.
- `kSTCaptureSessionPropertyIOSCameraExposureModeKey` :
  - Specifies what mode to set the color camera exposure to.
  - `NSInteger` integral value equal to one of the `STCaptureSessionIOSCameraExposureMode` constants.
  - Defaults to auto exposure.
- `kSTCaptureSessionPropertyIOSCameraISOModeKey` :
  - Specifies what mode to set the color camera ISO to.
  - `NSInteger` integral value equal to one of the `STCaptureSessionIOSCameraISOMode` constants.
  - Defaults to auto ISO.
- `kSTCaptureSessionPropertyIOSCameraWhiteBalanceModeKey` :
  - Specifies what mode to set the color camera white balance to.
  - `NSInteger` integral value equal to one of the `STCaptureSessionIOSCameraWhiteBalanceMode` constants.
  - Defaults to auto white balance.
- `kSTCaptureSessionPropertySensorIRExposureModeKey` :
  - Specifies what mode to set the IR sensor exposure to (Mark II sensors only, currently).
  - `NSInteger` integral value equal to one of the `STCaptureSessionSensorIRExposureMode` constants.
  - Defaults to a locked exposure determined by the sensor depth preset that is chosen.

The following properties represent the values to use when locking one or more of
the above color camera properties to a custom value. The units represent what one
would typically use when using the standard AVCaptureDevice API.

- `kSTCaptureSessionPropertyIOSCameraFocusValueKey` :
  - Specifies what position in [0.0 1.0] to set the focus lens position of the color camera.
  - `NSFloat` float value equal to the focus position desired.
  - SLAM performance is typically better when the focus position is similar to what was used during calibration.
- `kSTCaptureSessionPropertyIOSCameraExposureValueKey` :
  - Specifies what length of time (in seconds) to set for the color camera exposure.
  - `NSFloat` float value equal to the time in seconds to use as the target color camera exposure.
- `kSTCaptureSessionPropertyIOSCameraISOValueKey` :
  - Specifies what ISO speed to set for the color camera ISO.
  - `NSFloat` float value equal to the desired ISO of the color camera.
- `kSTCaptureSessionPropertyIOSCameraWhiteBalanceRedGainValueKey` :
  - Specifies the value of the red gain value for white balance.
  - `NSFloat` float value in the range of [1.0 maxWhiteBalanceGain] for the red gain.
- `kSTCaptureSessionPropertyIOSCameraWhiteBalanceGreenGainValueKey` :
  - Specifies the value of the green gain value for white balance.
  - `NSFloat` float value in the range of [1.0 maxWhiteBalanceGain] for the green gain.
- `kSTCaptureSessionPropertyIOSCameraWhiteBalanceBlueGainValueKey` :
  - Specifies the value of the blue gain value for white balance.
  - `NSFloat` float value in the range of [1.0 maxWhiteBalanceGain] for the blue gain.
- `kSTCaptureSessionPropertySensorIRExposureValueKey` :
  - Specifies the what length of time (in seconds) to set for the IR / Depth exposure (Mark II only)
  - `NSFloat` float value equal to the time in seconds to use as the target IR / Depth exposure
- `kSTCaptureSessionPropertySensorIRAnalogGainValueKey` :
  - Specifies what analog gain mode (1x, 2x, 4x, 8x) to set on the IR sensor (Mark II only)
  - `NSInteger` integral value equal to one of the `STCaptureSessionSensorAnalogGainMode` constants.
  - Defaults to `STCaptureSessionSensorAnalogGainMode8_0` for an 8x IR gain.

See also:

 - <STCaptureSessionIOSCameraFocusMode>
 - <STCaptureSessionIOSCameraExposureMode>
 - <STCaptureSessionIOSCameraISOMode>
 - <STCaptureSessionIOSCameraWhiteBalanceMode>
 - <STCaptureSessionSensorIRExposureMode>
 - <STCaptureSessionSensorAnalogGainMode>
*/
@property(nonatomic,retain) NSDictionary* properties;

/** Property for setting or getting the current color camera lens type that the capture session is using.

Describes the current lens configuration (normal or wide vision) that is
attached to the bracket for the Structure Sensor. This is important as each lens
type will correspond to an individual calibration corresponding to it from
Structure Sensor Calibrator.

See also:

 - <STLens>
*/
@property(atomic,readwrite) STLens lens;

/** Property for managing the lens detector from the capture session.

The value this property is set to controls the behavior of the lens detector
within the capture session (i.e. whether it is enabled / on, disabled / off, or
merely warns when the detected lens does not match the type of lens set in
`_captureSession.lens`)

See also:

 - <STLensDetectorState>
 - <[STCaptureSessionDelegate captureSession:onLensDetectorOutput:]>
*/
@property(nonatomic,readwrite) STLensDetectorState lensDetection;

/** Property to describe the last status sent by the lens detector.

The value this property is set to is derived from the result of the lens
detector. Thus, if the lens detector is disabled / off, then this value will
mean nothing.

See also:

 - <[STDetectedLensStatus]
 - <[STCaptureSession lensDetection]>
 - <[STCaptureSessionDelegate captureSession:onLensDetectorOutput:]>
*/
@property(nonatomic,readonly) STDetectedLensStatus lastDetectedLens;

/// Property to read the sensor battery level of the controlled Structure Sensor, or nil if no sensor is connected.
@property(nonatomic,readonly) int sensorBatteryLevel;

/// Property to read the last mode entered by a Structure Sensor.
@property(nonatomic,readonly) STCaptureSessionSensorMode sensorMode;

/// Property to read the name of the controlled Structure Sensor, or nil if no sensor is connected.
@property(nonatomic,readonly) NSString* sensorName;

/// Property to read the serial number of the controlled sensor, or nil if no sensor is connected.
@property(nonatomic,readonly) NSString* sensorSerialNumber;

/// Property to read the firmware revision of the controlled sensor, or nil if no sensor is connected.
@property(nonatomic,readonly) NSString* sensorFirmwareRevision;

/// Property to read the hardware revision of the controlled sensor, or nil if no sensor is connected.
@property(nonatomic,readonly) NSString* sensorHardwareRevision;

/// Property to tell whether or not the Structure Sensor charger of the connected sensor is plugged in.
@property(nonatomic,readonly) BOOL isSensorChargerConnected;

/** Property that provides access to a set of user facing warnings.

These warnings are meant to inform STCaptureSession users about important status
considerations of the capture session. This could be anything from notifying
that the sensor is not connected, to needing to run Calibrator.

An example of how this might be used could be as follows:

    STCaptureSessionUserInstruction userInstructions = _captureSession.userInstructions;

    bool needToConnectSensor = userInstructions & STCaptureSessionUserInstructionNeedToConnectSensor;
    bool needToRunCalibrator = userInstructions & STCaptureSessionUserInstructionNeedToRunCalibrator;

    if (needToConnectSensor)
    {
        // Show message to user about connecting the Structure Sensor
    }

    if (needToRunCalibrator)
    {
        // Show calibration overlay, or some message that calls to
        // [STCaptureSession launchCalibratorOrGoToAppStore];
        //
        // NOTE: If you have an approximate calibration (see
        // <[STCaptureSession calibrationType]>), this flag will still be set.
    }

See also:

 - <STCaptureSessionUserInstruction>
 - <[STCaptureSession calibrationType]>
*/
@property(nonatomic,readonly) STCaptureSessionUserInstruction userInstructions;

/// @name OCC writing

/** Property that provides access to a class that handles the OCC writing functionality of the capture session.

By using the OCC writer, incoming frames and events can be saved to a file at
some local file location. These frames and events are stored in such a way that
the OCC file can be replayed as a sensor replacement (see
<[STCaptureSession newCaptureSessionFromOccFile:]>).

When <[STOccFileWriter stopWriting]> or <[STOccFileWriter cancelWriting]> are
called, this object will reset itself to a new instance, and the old value of
this object will be invalid. This also means that H264 compression, if used,
will also need to be set again on the new writer instance.

See also:

 - <STOccFileWriter>
*/
@property(nonatomic,readonly) STOccFileWriter* occWriter;

/// @name Capture Session instance methods

/** Launch the Calibrator app or prompt the user to install it.

An iOS app using the Structure Sensor should present its users with an
opportunity to call this method when the following conditions are
simultaneously met:

 - The sensor doesn't have a `calibrationType` with value `CalibrationTypeDeviceSpecific`.
 - A registered depth stream is required by the application.
 - The iOS device is supported by the Calibrator app.

@warning For this method to function, your app bundle's info plist must contain the following entry:

 <key>LSApplicationQueriesSchemes</key>
 <array>
 <string>structure-sensor-calibrator</string>
 </array>

@note See the calibration overlay sample code for more details.
*/
- (BOOL) launchCalibratorAppOrGoToAppStore;

/** This method sets up the sensor configuration and starts monitoring for sensors (Structure Sensor and iOS color camera).

Configuration here refers to the static options for the capture session (e.g.
whether to connect to a depth or infrared stream, what resolution to stream
color camera frames at).

- `kSTCaptureSessionOptionDepthSensorEnabledKey` :
  - Specifies whether we want to enable the depth stream from a Structure Sensor.
  - `BOOL` value, true if-and-only-if you want to stream depth from a Structure Sensor.
  - Defaults to `@NO`.
- `kSTCaptureSessionOptionInfraredSensorEnabledKey` :
  - Specifies whether we want to enable the infrared stream from a Structure Sensor.
  - `BOOL` value, true if-and-only-if you want to stream infrared from a Structure Sensor.
  - Defaults to `@NO`.
- `kSTCaptureSessionOptionDepthSensorVGAEnabledIfAvailableKey` :
  - Specifies whether we want a VGA depth stream from the Structure Sensor, if available.
  - `BOOL` value, true if-and-only-if you want to stream VGA depth.
  - Defaults to `@NO`.
- `kSTCaptureSessionOptionSensorAndIOSCameraSyncEnabledKey` :
  - Specifies whether to synchronize iOS color camera and Structure Sensor depth / infrared frames.
  - `BOOL` value, true if-and-only-if you want frame sync enabled.
  - Defaults to `@YES` in most cases, except where the color camera is disabled.
- `kSTCaptureSessionOptionIOSCameraKey` :
  - Specifies which iOS camera to connect to.
  - `NSNumber` integral value equal to one of the `STCaptureSessionIOSCamera` constants.
  - Set by default by the capture session factory methods (e.g. newCaptureSession).
- `kSTCaptureSessionOptionColorResolutionKey` :
  - Specifies the desired resolution of the streamed color frames.
  - `NSNumber` integral value equal to one of the `STCaptureSessionColorResolution` constants.
  - Defaults to VGA resolution.
- `kSTCaptureSessionOptionColorMaxFPSKey` :
  - Specifies the maximum FPS to try and stream with the iOS color camera. May not be possible depending on the resolution and format.
  - `NSFloat` float value specifying the maximum FPS to stream color frames at.
  - Defaults to 30.0 FPS.
- `kSTCaptureSessionOptionUseAppleCoreMotionKey`
  - Specifies whether to stream Apple CoreMotion data or raw gyroscope / accelerometer data.
  - `BOOL` value, true if-and-only-if you wish to receive CoreMotion data from the capture session.
  - Defaults to `@NO`
- `kSTCaptureSessionOptionToggleDepthSensorAutomaticallyKey`
  - Specifies whether to toggle the depth sensor on and off automatically when it becomes connected.
  - `BOOL` value, true if-and-only-if you wish to toggle the depth sensor automatically.
  - Defaults to `@YES`.
- `kSTCaptureSessionOptionStartOCCAfterSecondsKey`
  - Specifies the number of seconds to skip in OCC playback when streaming from an OCC file.
  - `NSDouble` float value, specifying the amount of time since the beginning of OCC playback to wait before streaming.
  - Defaults to zero.
- `kSTCaptureSessionOptionSimulateRealtimePlaybackKey`
  - Specifies whether to simulate real-time effects of playback when streaming from an OCC file.
  - Real-time effects can for example be dropped frames, missed events, etc.
  - `BOOL` value, true if-and-only-if you want to simulate real-time effects of playback while streaming.
  - Defaults to `@NO`.
- `kSTCaptureSessionOptionDepthStreamPresetKey`
  - Specifies a depth sensor preset to optimize the depth range, exposure, and other settings to optimize for specific use cases.
  - e.g. Optimize for close-range depth when using the body-scanning preset, or optimize the sensor for mid-to-long range depth when using the room-scanning preset
  - `NSInteger` integral value specifying one of the `STCaptureSessionPreset` constants.
  - Defaults to the default preset.



@param options A dictionary containing the sensor and device configuration for the capture session.
*/
- (void) startMonitoringWithOptions:(NSDictionary*)options;

/** Returns the type of the current depth-color calibration for a Structure Sensor and current value of `_captureSession.lens`.

This value can change depending on the actual device-sensor combination in use.

@warning This method will throw an exception when called while no sensor is connected.

See also:

 - <[STCaptureSession calibrationTypeWithLens:]>
*/
- (STCalibrationType) calibrationType;

/** Returns the type of the current depth-color calibration for a Structure Sensor and given lens type.

This value can change depending on the actual device-sensor combination in use.

@warning This method will throw an exception when called while no sensor is connected.

See also:

 - <[STCaptureSession calibrationType]>
*/
- (STCalibrationType) calibrationTypeWithLens:(STLens)lens;

@end

//------------------------------------------------------------------------------
#pragma mark - Helper methods for STCaptureSession color camera properties
/// @name Helper methods for STCaptureSession color camera properties

#ifdef __cplusplus
extern "C" {
#endif
    /// Returns an NSDictionary to be set in `_captureSession.properties` that locks
    /// all properties to their current values.
    NSDictionary* STCaptureSessionPropertiesLockAllColorCameraPropertiesToCurrent(void);

    /// Returns an NSDictionary to be set in `_captureSession.properties` that locks
    /// all properties to their current values, but with a provided target exposure.
    NSDictionary* STCaptureSessionPropertiesLockAllColorCameraPropertiesToCurrentWithTargetExposure(float targetExposure);

    /// Returns an NSDictionary to be set in `_captureSession.properties` that sets
    /// exposure and white balance to auto mode.
    NSDictionary* STCaptureSessionPropertiesSetColorCameraAutoExposureISOAndWhiteBalance(void);
#ifdef __cplusplus
};
#endif
