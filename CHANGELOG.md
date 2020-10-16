# Release v0.34.0
**Release Date**: 09 Oct 2020  
**Nuitrack Runtime version**: 0.34.0  
**Nuitrack SDK version**: 1.8.1

## New Features

* added AMD CPUs compatibility for **Nuitrack AI Skeleton Tracking**
* added support for **Moving Sensor** on `Windows x86_64` and `iOS`
* **Realsense SDK** has been updated to `2.38.1`
* added *Async Init* support to `NuitrackScripts.prefab` in **NuitrackSDK.unitypackage**

## Bug Fixes and Improvements

* **Nuitrack AI Skeleton Tracking**: the model is updated; added estimation of joint orientations
* fixed the memory leak on `Linux x86_64` that occurred in **Moving Sensor** mode
* installation of `libpng12-0` and `libssl1.0.0` on `Ubuntu 20.04 LTS` is no longer required
* fixed the low FPS issue for **Kinect V2** on `Windows x86_64`
* fixed the `Realsense2Module.DeviceHardwareReset` option in `nuitrack.config`
* edited the [Creating an Interactive Multi-Touch Gallery](/doc/Unity_Gallery.md) tutorial
* fixed the application crush on `Android` when starting without a plugged sensor

## Known Issues

 - Exception handling issue in `nuitrack-windows-x86.exe`
 - USB cameras permission issue on **Android 9 (Pie)** devices
 - Gesture recognition may fail for sitting pose

# Release v0.33.0

**Release Date**: 04 Sept 2020  
**Nuitrack Runtime version**: 0.33.0  
**Nuitrack SDK version**: 1.8.0  

## API Changes

* **`Nuitrack SDK v1.8.0` requires `Nuitrack v0.33.0` to be installed**

## New Features

* [AI Skeletal Tracking](/doc/Nuitrack_AI.md#ai-skeleton-tracking)
* [AI Object Detection](/doc/Nuitrack_AI.md#ai-object-detection)
* [Moving Sensor](/doc/Moving_Sensor.md)

## Known Issues

 - Exception handling issue in `nuitrack-windows-x86.exe`
 - USB cameras permission issue on **Android 9 (Pie)** devices
 - Gesture recognition may fail for sitting pose

# Release v0.32.0

**Release Date**: 13 Aug 2020  
**Nuitrack Runtime version**: 0.32.0  
**Nuitrack SDK version**: 1.7.0

## API Changes

* **`Nuitrack SDK v1.7.0` requires `Nuitrack v0.32.0` to be installed**

### C++/C# API

* **Nuitrack Device API** has been implemented. This API allows you to:
  * enumerate and activate compatible depth sensors
  * run Nuitrack with a selected depth sensor

Please refer to [C++](/Examples/nuitrack_device_api_sample/src/main.cpp) or [C#](/Examples/nuitrack_csharp_device_api_sample/Program.cs) examples for more details.

* New function that you can use to get Nuitrack version: `nuitrack::getVersion()` (`nuitrack.GetVersion()` for C#).

## New Features

* Support for **Astra Stereo S U3**.

## Bug Fixes and Improvements

* Fixed performance issue on `Windows x86`.

## Known Issues

 - Exception handling issue in `nuitrack-windows-x86.exe`
 - USB cameras permission issue on **Android 9 (Pie)** devices
 - Gesture recognition may fail for sitting pose

# Release v0.31.0

**Release Date**: 2 Jul 2020  
**Nuitrack Runtime version**: 0.31.0  
**Nuitrack SDK version**: 1.6.0

## API Changes

* **`Nuitrack SDK v1.6.0` requires `Nuitrack v0.31.0` to be installed**

### C# API

* The `IDisposable` pattern was implemented. This pattern is used to release unmanaged resources for all types returned in callbacks:
  * to copy an object returned in a callback, use the `Clone()` method as references to such objects outside the callback body are invalid (because this object can be destroyed after the callback is completed).
  * Examples:

    ```c#
    using (nuitrack.DepthFrame depthFrameCopy = (nuitrack.DepthFrame)depthFrame.Clone())
    {
      ...
    }
    ```

    ```c#
    nuitrack.DepthFrame _depthFrame; // non-local field
    
    void HandleOnDepthSensorUpdateEvent(nuitrack.DepthFrame frame)
    {
        if (_depthFrame != null)
            _depthFrame.Dispose();
        _depthFrame = (nuitrack.DepthFrame)frame.Clone();
        ...
    }
    ```

* The `Frame` class:
  * the type of the `Data` field was changed: now it's `IntPtr` instead of `byte []`. This means that if you want to index elements, you need to use `unsafe` context or explicitly copy the data to the byte array.
  * the `DataSize` field was added. It returns the size of the frame data in bytes.

* The `Clone` method was added for the following types: `DepthFrame`, `ColorFrame`, `UserFrame`, `SkeletonData`, `GestureData`, `HandTrackerData`, `IssuesData`

## New Features

* `Nuitrack_arm64.apk` is released (supports **Android ABI** `arm64-v8a`)
* **Unity 3D**: `IL2CPP` scripting backend support is added
* Stream registration options are supported for **Realsense D400** cameras:
  * set the `Realsense2Module.AlignTo` parameter in the `nuitrack.config` file. Supported values: `none|color|depth`

## Bug Fixes and Improvements

* Significant optimization of GC usage in `nuitrack.net.dll`
* Nuitrack activation tool now supports a license activation via proxy:
  * define the environment variable `TDV_NUITRACK_PROXY` or set `Network.ProxyUrl` parameter in the `nuitrack.config` file, e.g. `proxy.org.com:8080`
* `nuitrack::TerminateException` is thrown after **Realsense D400** camera is disconnected

## Known Issues

 - USB cameras permission issue on **Android 9 (Pie)** devices
 - Gesture recognition may fail for sitting pose

# Release v0.30.0

**Release Date**: 25 Mar 2020  
**Nuitrack Runtime version**: 0.30.0  
**Nuitrack SDK version**: 1.5.0

## Changes

Nuitrack Runtime:

 - added support for Astra Embedded S / Stereo S (Windows/Linux)
 - fixed error with the Mirror settings for Kinect/Kinect V2
 - fixed error with double triggering of onLostuserCallback for UserTracker
 - added HD resolution support of an RGB stream for Orbbec Astra (Windows/Linux/Android)

Nuitrack SDK:

 - added Structure Sensor (Occipital) support for iOS

## Known Issues

 - USB cameras permission issue on **Android 9 (Pie)** devices
 - Gesture recognition may fail for sitting pose

# Release v0.29.0

**Release Date**: 26 Sep 2019  
**Nuitrack Runtime version**: 0.29.0  
**Nuitrack SDK version**: 1.4.1

## Changes

Nuitrack Runtime:

 - Supports Raspberry Pi 3 and Tinkerboard devices (please refer to supported cameras list at http://nuitrack.com)
 - Fixed crash when used in ROS
 - librealsense2 library version updated to v2.25.0
 - Supports updating online licenses with connection via a proxy server

Nuitrack SDK:

 - Boost symbols are local in `libmiddleware.so` now (Linux)

## Known Issues

 - USB cameras permission issue on **Android 9 (Pie)** devices
 - Gesture recognition may fail for sitting pose
 - Orbbec Astra PRO, Orbbec Persee: color stream may not start with HD configuration
