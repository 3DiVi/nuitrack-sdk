# Release v0.35.9

**Release Date**: 1 Sep 2021  
**Nuitrack Runtime version**: 0.35.9  
**Nuitrack SDK version**: 1.11.8

## Bug Fixes and Improvements

* Added full support for **Nvidia Jetson**: **Nano**, **TX2**, **Xavier NX**, **AGX Xavier**
* Added support the **Intel Realsense** sensors for the `Linux arm32` platforms (**Raspberry Pi 4** on **Raspberry Pi OS**)
* Removed the popup camera choice dialog on **Windows** platform
* Fixed the memory leak on the **Android** platform
* Fixed black window after second launch of Nuitrack on **Astra Pro** sensors
* Fixed option to disable the color frame on **Intel Realsense** sensors
* **NuitrackSDK.unitypackage**: added helpful hints to error messages

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.8

**Release Date**: 1 Aug 2021  
**Nuitrack Runtime version**: 0.35.8  
**Nuitrack SDK version**: 1.11.7

## Bug Fixes and Improvements

* Improved the user interface of the Nuitrack activation tool
* Fixed support for some Orbbec Astra+ sensors

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.7

**Release Date**: 21 Jul 2021  
**Nuitrack Runtime version**: 0.35.7  
**Nuitrack SDK version**: 1.11.6

## New Features

* Added support the **Intel Realsense** sensors for the `Linux arm64` platforms (**Raspberry Pi 4**, **NVIDIA Jetson TX2**)

## Bug Fixes and Improvements

* Fixed the memory leak in the **Nuitrack AI** mode
* `NuitrackSDK.unitypackage`:
  * added new tutorials (`AR Nuitrack`, `Jump Trainer`, `Final IK`)
  * update working with frames
  * fixed the Unity 2020+ interface problem
  * added the advanced TBB-file error message
  * added using `nuitrack.config` features from the `NuitrackManager` component

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.6

**Release Date**: 19 May 2021  
**Nuitrack Runtime version**: 0.35.6  
**Nuitrack SDK version**: 1.11.5

## New Features

* Added support for the **Orbbec Astra +** cameras (`Windows x86`, `Windows x86_64`, `Ubuntu amd64` and `Linux arm32`)
* Added support for the **Azure Kinect** cameras (`Windows x86`, `Windows x86_64`, and `Ubuntu amd64`)
  * Please check [system requirements](https://docs.microsoft.com/en-us/azure/kinect-dk/system-requirements) for **Azure Kinect**

## Bug Fixes and Improvements

* Fixed camera locking issue on Android

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.5

**Release Date**: 29 April 2021  
**Nuitrack Runtime version**: 0.35.5  
**Nuitrack SDK version**: 1.11.4

## Bug Fixes and Improvements

* `nuitrack_gl_sample`: fixed incorrect termination of the application when pressing the window close button
* Fixed application crashes when AI mode is not used

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.4

**Release Date**: 6 April 2021  
**Nuitrack Runtime version**: 0.35.4  
**Nuitrack SDK version**: 1.11.3

## Bug Fixes and Improvements

* **Nuitrack AI Skeleton Tracking**: improved skeleton tracking quality

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.3

**Release Date**: 31 March 2021  
**Nuitrack Runtime version**: 0.35.3  
**Nuitrack SDK version**: 1.11.2

## New Features

* **Unity**: added the first tutorial on **Nuitrack AI Object Detection**

## Bug Fixes and Improvements

* **Nuitrack AI Skeleton Tracking**: improved accuracy of detecting 3D coordinates of skeleton joints
* **Nuitrack AI Skeleton Tracking**: improved legs position in motion for Moving Sensor mode

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.2

**Release Date**: 22 March 2021  
**Nuitrack Runtime version**: 0.35.2  
**Nuitrack SDK version**: 1.11.1

## SDK Changes

* Updated `nuitrack_device_api_sample`: improved console output

## Bug Fixes

* Fixed a crash when disconnecting the **Intel RealSense** sensors with the enabled `Realsense2DepthProvider.DeviceHardwareReset` option
* Fixed an issue with the detection of **Intel RealSense d455 and L515** sensors on **Android**
* Fixed the types of some returned exceptions

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.1

**Release Date**: 04 Feb 2021  
**Nuitrack Runtime version**: 0.35.1  
**Nuitrack SDK version**: 1.11.0

## SDK Changes

* Added an **Android Studio** project (`nuitrack_android_studio_gl_sample`)
* Added support for the `__ANDROID__` preprocessor directive in the **Android** examples

## Bug Fixes

* Fixed an issue with access rights to the folder `/usr/etc/nuitrack/data` on **Linux**: edited the installation script
* Fixed the license issue on **Linux** (the activated license didn't work for some users)
* Fixed image distortion during rotation in `nuitrack_sample`

## Known Issues

 - USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
 - Gesture recognition may fail for sitting pose

# Release v0.35.0
**Release Date**: 30 Nov 2020  
**Nuitrack Runtime version**: 0.35.0  
**Nuitrack SDK version**: 1.10.0

## API Changes

* **`Nuitrack SDK v1.10.0` requires `Nuitrack v0.35.0` to be installed**

## New Features

* Added **Unreal Engine 4.25** plugins for **Windows** and **Android**. Please refer to new tutorials:
  * [UE4 Basic Project for Windows](/doc/Unreal_Engine_Windows_Tutorial.md)
  * [UE4 Basic Project for Android](/doc/Unreal_Engine_Android_Tutorial.md)
* Added digital signature to the installers `nuitrack-windows-x64.exe` and `nuitrack-windows-x86.exe`
* Added auto-switching between the `nuitrack.net` assembly versions (`Mono`, `IL2CPP`, `iOS`) in the **NuitrackSDK.unitypackage**

## Bug Fixes and Improvements

* Added support for the **Realsense D415/D435/D435i** cameras on **Android 9 (Pie) or higher**
  * **Realsense SDK** has been updated to `v2.38.1` for **Android**

## Known Issues

 - USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
 - Gesture recognition may fail for sitting pose

# Release v0.34.1
**Release Date**: 03 Nov 2020  
**Nuitrack Runtime version**: 0.34.1  
**Nuitrack SDK version**: 1.9.0

## API Changes

* **`Nuitrack SDK v1.9.0` requires `Nuitrack v0.34.1` to be installed**

### C++ API

* Fixed an occasional compiler error `type has C-linkage specified, but returns UDT which is incompatible with C`

## New Features

* Added support for the **Intel Realsense D455 and L515** cameras (`Windows x86`, `Windows x86_64`, and `Ubuntu amd64`)
* `NuitrackSDK.unitypackage`:
  * connection to the **TVico** and **VicoVR** sensors on `Android` is now possible without installing [VicoVR.apk](https://play.google.com/store/apps/details?id=com.vicovr.manager) (only the `SkeletonTracker` data is transferred)

## Bug Fixes and Improvements

* Fixed the exception handling issue in `nuitrack-windows-x86.exe`
* `NuitrackSDK.unitypackage`:
  * fixed issues with *Async Init* mode
* Edited the [Creating an AR Football Game using Nuitrack and ARCore/ARKit](/doc/Unity_AR_Football.md) tutorial

## Known Issues

 - USB cameras permission issue on **Android 9 (Pie) or higher**
 - Gesture recognition may fail for sitting pose

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
