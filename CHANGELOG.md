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
