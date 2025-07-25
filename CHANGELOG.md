# Release v0.38.5

**Release Date**: 11 Jul 2025  
**Nuitrack Runtime version**: 0.38.5  
**Nuitrack SDK version**: 1.14.5  

* *Nuitrack Viewer*: Stream Mirroring Added and Stream Rotation Refined
* Stability Improved for all supported platforms 

# Release v0.38.4

**Release Date**: 6 Jun 2025  
**Nuitrack Runtime version**: 0.38.4  
**Nuitrack SDK version**: 1.14.4  

## Improvements and Bug Fixes

* *(Motionless detection)* UserTracker now detect users without additional movements towards the sensor
* UserTracker: floor segmentation (and user segmentation as a consequence) improved for complex cases 
* Major *Nuitrack Viewer* update
  * You can choose timestamp source to control stream synchronization through new combined (RGB, depth) visualization
  * Increased rendering performance
  * Visualization for raw depth data and tracking results was streamlined
* Added support for Orbbec sensors with the latest firmware version (updated OrbbecSDK)
* Unity / C# wrapper:
  * Fixed activation statuses 
  * Fixed a crash that occurred when activating via C# without an internet connection
* Android packages which were unstable on recent versions are now significantly stabilized
* Python packages revisited with multiple fixes, will be out of beta status in next revision

## Known Issues
* Linux ARM64 package behaves unstable on some devices (i.e. Jetson Nano), will be fixed in next revision.


# Release v0.38.2

**Release Date**: 3 Mar 2025  
**Nuitrack Runtime version**: 0.38.2  
**Nuitrack SDK version**: 1.14.2  

* Redesigned Nuitrack app - now it includes a *Nuitrack Viewer*, fully-featured testing tool for any supported sensor(s)
  * You can choose RGB & Depth resolution and framerate, album or portrait orientation, control sensor position, etc.
* Nuitrack now is significantly more stable on any non-default resolution modes (more fixes/optimizations are coming)

# Release v0.38.1

**Release Date**: 3 Feb 2025  
**Nuitrack Runtime version**: 0.38.1  
**Nuitrack SDK version**: 1.14.1  

* Femto Mega - added initial support
* Femto Bolt and other Orbbec sensors - Depth/RGB syncronization issue handling
* Nuitrack.exe - proper support for portrait mode 

# Release v0.38.0

**Release Date**: 8 Jan 2025  
**Nuitrack Runtime version**: 0.38.0  
**Nuitrack SDK version**: 1.14.0  

## Bug Fixes and Improvements
* Depth sensing - numerous fixes, in particular for Azure Kinect, Orbbec Astra (multiple revisions)
* Scene segmentation and user tracking - improved robustness, additional options for floor detection / scene segmentation

## Known Issues
* Nuitrack.exe works unstable when depth map rotation is set (examples and other applications are not impacted)

# Release v0.37.24

**Release Date**: 1 Jul 2024  
**Nuitrack Runtime version**: 0.37.24  
**Nuitrack SDK version**: 1.13.24  

## Bug Fixes and Improvements
* Kinect v2 (Windows): Fixed an issue that confused the left and right sides of a skeleton
* Kinect Azure: Fixed an issue with Unreal Engine 5 plugin startup

# Release v0.37.23

**Release Date**: 15 Jun 2024  
**Nuitrack Runtime version**: 0.37.23  
**Nuitrack SDK version**: 1.13.23  

## Bug Fixes and Improvements
* Classical Skeleton Tracking: 
  * Improved stability on Kinect v2
  * Improved tracking quality

# Release v0.37.22

**Release Date**: 7 Jun 2024  
**Nuitrack Runtime version**: 0.37.22  
**Nuitrack SDK version**: 1.13.22  

## Bug Fixes and Improvements
* [Docker](https://hub.docker.com/r/nuitrack/nuitrack): Improved support
* Unreal Engine: Nuitrack runtime now supports the newest 5.4 version
  * Updated Nuitrack package is available from the [official marketplace](https://www.unrealengine.com/marketplace/en-US/product/nuitrack-real-time-body-tracking)

# Release v0.37.21

**Release Date**: 1 Jun 2024  
**Nuitrack Runtime version**: 0.37.21  
**Nuitrack SDK version**: 1.13.21  

## Bug Fixes and Improvements
* [**TouchDesigner plugin**](TouchDesigner): The official release is now available 
  * Now you can activate [Nuitrack AI Subscription](https://cognitive.3divi.com/app/nuitrack/basket/license-selection/) and start using the plugin without restrictions

# Release v0.37.20

**Release Date**: 24 May 2024  
**Nuitrack Runtime version**: 0.37.20  
**Nuitrack SDK version**: 1.13.20  

## Bug Fixes and Improvements
* Nuitrack Installer for Windows: fixed a bug that caused the installation to hang at 66%

# Release v0.37.19

**Release Date**: 17 May 2024  
**Nuitrack Runtime version**: 0.37.19  
**Nuitrack SDK version**: 1.13.19  

## Bug Fixes and Improvements
* Skeleton Tracking on Kinect v2 (Windows), Orbbec Astra 2 and Gemini 2/2L sensors: 
  * Improved quality and fixed problem with sudden track disappearance

# Release v0.37.18

**Release Date**: 8 May 2024  
**Nuitrack Runtime version**: 0.37.18  
**Nuitrack SDK version**: 1.13.18  

## Bug Fixes and Improvements
* CSV Recorder: [Data Import and 3D Skeleton Visualization python example](doc/CSV_Recorder.md#example-of-use-in-python)
* CSV Recorder: Positions of unobserved joints are filtered out from the export result
* New Tutorial: [Recommended approach to precisely track palms 3D positions](doc/Hand_Tracking.md)

# Release v0.37.17

**Release Date**: 26 Apr 2024  
**Nuitrack Runtime version**: 0.37.17  
**Nuitrack SDK version**: 1.13.17  

## Bug Fixes and Improvements
* Fixed bugs in the user interface of the Nuitrack application (activation tool)
* CSV Recorder now records a full set of skeletal joints

# Release v0.37.16

**Release Date**: 19 Apr 2024  
**Nuitrack Runtime version**: 0.37.16  
**Nuitrack SDK version**: 1.13.16  

## Bug Fixes and Improvements
* Added the ability [to write a skeleton data to CSV](doc/CSV_Recorder.md) via Nuitrack.exe
* `NuitrackSDK.unitypackage`: improved stability of avatar's legs in the frontal case

# Release v0.37.15

**Release Date**: 13 Apr 2024  
**Nuitrack Runtime version**: 0.37.15  
**Nuitrack SDK version**: 1.13.15

## Bug Fixes and Improvements
* Fixed Unity applications crash on Android (arm32)
* Fixed compatibility with TouchDesigner 2023 and later versions
* Improved stability of [Kinect v2](https://nuitrack.notion.site/Microsoft-Kinect-v2-655f2c8ad72e422097eea8d85fd09316) on Windows

# Release v0.37.14

**Release Date**: 05 Apr 2024  
**Nuitrack Runtime version**: 0.37.14  
**Nuitrack SDK version**: 1.13.14

## New Features
* Nuitrack AI Skeletal Tracking now supports latest Ryzen CPU's (series 7000/8000)
* Significant reduction in CPU usage (up to 60% less) for Nuitrack AI Skeletal Tracking
* Improved inference performance for Nuitrack AI Skeletal Tracking

## Bug Fixes and Improvements
* Fixed Kinect V1.8 (PID: 0x02bf) detection on Windows
* Fixed RealSense L515 re-activation if the license was initially activated on Nuitrack versions before v0.37.9

## Known Issues
* Unity applications will crash  on Android (arm32) for versions v0.37.13 / v0.37.14

# Release v0.37.13

**Release Date**: 25 Mar 2024  
**Nuitrack Runtime version**: 0.37.13  
**Nuitrack SDK version**: 1.13.13  

## New Features
* Now, during execution, Nuitrack notifies when the sensor is disconnected from the USB port

## Bug Fixes and Improvements
* Fixed an issue that made it impossible to use drag n drop in the Unity editor after initializing Nuitrack
* Fixed crash when disconnecting the sensor while Nuitrack is running (for Orbbec Astra/Astra Pro sensors)
* Fixed Kinect v2 detection issue on Windows leading to the need to restart the computer

# Release v0.37.12

**Release Date**: 16 Feb 2024  
**Nuitrack Runtime version**: 0.37.12  
**Nuitrack SDK version**: 1.13.12  

## New Features
* Added **[Docker](https://hub.docker.com/r/nuitrack/nuitrack)** support for **Linux arm64**

## Bug Fixes and Improvements
* Added intrinsic camera parameters to the OutputMode structure for the C# API  

# Release v0.37.11

**Release Date**: 3 Feb 2024  
**Nuitrack Runtime version**: 0.37.11  
**Nuitrack SDK version**: 1.13.11  

## Bug Fixes and Improvements
* Kinect v1: sensor detection for additional VID/PID  

# Release v0.37.10

**Release Date**: 26 Jan 2024  
**Nuitrack Runtime version**: 0.37.10  
**Nuitrack SDK version**: 1.13.10  

## New Features
* Added support for **Docker** _(you can find the official Docker image [here](https://hub.docker.com/r/nuitrack/nuitrack))_   
* Added **Python API** for [Linux arm64](PythonNuitrack-beta/pip_packages/dist/linux/py_nuitrack_ubuntu_arm64-0.1.0-py3-none-any.whl)  

# Release v0.37.9

**Release Date**: 19 Jan 2024  
**Nuitrack Runtime version**: 0.37.9  
**Nuitrack SDK version**: 1.13.9  

## Bug Fixes and Improvements
* Fixed simultaneous operation of multiple Orbbec sensors (multi-sensor mode)
* Fixed problem opening *.bag files recorded by Intel Realsense L515

# Release v0.37.8

**Release Date**: 13 Jan 2024  
**Nuitrack Runtime version**: 0.37.8  
**Nuitrack SDK version**: 1.13.8  

## New Features
* [beta] Added support for Orbbec Gemini 2L and Astra 2

## Bug Fixes and Improvements
* Fixed the display of the depth map in the demo visualization in Nuitrack.exe

# Release v0.37.7

**Release Date**: 30 Dec 2023  
**Nuitrack Runtime version**: 0.37.7  
**Nuitrack SDK version**: 1.13.7  

## New Features
* Orbbec Gemini 2XL and Femto Bolt: added support on desktop Windows and Linux

## Bug Fixes and Improvements
* Fixed crash when using Face Recognition via Python API

# Release v0.37.6

**Release Date**: 16 Dec 2023  
**Nuitrack Runtime version**: 0.37.6  
**Nuitrack SDK version**: 1.13.6  

## New Features
* [beta] Added the ability to run a demo from multiple cameras at the same time in Nuitrack.exe

## Bug Fixes and Improvements
* Nuitrack AI Hybrid Mode: improved detection of skeletal limbs

# Release v0.37.5

**Release Date**: 5 Dec 2023  
**Nuitrack Runtime version**: 0.37.5  
**Nuitrack SDK version**: 1.13.5  

## Bug Fixes and Improvements
* Added hints on manual license activation in case of problems with activation in Nuitrack.exe
* Updated `NuitrackSDK.unitypackage`: improved samples and fixed bugs

# Release v0.37.4

**Release Date**: 24 Nov 2023  
**Nuitrack Runtime version**: 0.37.4  
**Nuitrack SDK version**: 1.13.4  

## Bug Fixes and Improvements
* Object Detection (feature): proper operation in Nuitrack.exe
* Kinect v2: sensor detection for additional VID/PID

# Release v0.37.3

**Release Date**: 8 Nov 2023  
**Nuitrack Runtime version**: 0.37.3  
**Nuitrack SDK version**: 1.13.3  

## New Features
* Nuitrack AI Hybrid Mode: now you could get a 2D coordinates for skeleton joints when depth data is not available 
* The [**integration process**](doc/Nuitrack_Integration.md) with Nuitrack has been greatly simplified

## Bug Fixes and Improvements
* Fixed head position detection in **Nuitrack AI Skeletal Tracking** in a case when a person is turned left profile to the camera

# Release v0.37.2

**Release Date**: 28 Oct 2023  
**Nuitrack Runtime version**: 0.37.2  
**Nuitrack SDK version**: 1.13.2  

## Bug Fixes and Improvements
* Improved stability

# Release v0.37.1

**Release Date**: 21 Oct 2023  
**Nuitrack Runtime version**: 0.37.1  
**Nuitrack SDK version**: 1.13.1  

## New Features
* Added the [**failure case recorder**](doc/Failure_Case_Recorder.md) feature for Android platforms

# Release v0.37.0

**Release Date**: 06 Oct 2023  
**Nuitrack Runtime version**: 0.37.0  
**Nuitrack SDK version**: 1.13.0  

## New Features
* Nuitrack.exe was slighty redesigned, error messages should be more informative now
* Orbbec Gemini 2: added support on desktop Windows and Linux

## Bug Fixes and Improvements
* Orbbec Astra: incorrect RGB data streaming from additional/built-in webcam (instead of depth sensor) was fixed

# Release v0.36.17

**Release Date**: 01 Sep 2023  
**Nuitrack Runtime version**: 0.36.17  
**Nuitrack SDK version**: 1.12.17  

## Bug Fixes and Improvements
* Fixed cases of incorrect setting of frame resolution

# Release v0.36.16

**Release Date**: 25 Aug 2023  
**Nuitrack Runtime version**: 0.36.16  
**Nuitrack SDK version**: 1.12.16  

## Bug Fixes and Improvements
* Increased the number of facial points from 21 to 47 (_FDA_ set was replaced by _ESR_)
* Fixed crash when running Nuitrack via Unity on **Android arm32** platform
* Fixed Nuitrack operation with Unity on **Orbbec Persee Plus (Android)**

# Release v0.36.15

**Release Date**: 5 Aug 2023  
**Nuitrack Runtime version**: 0.36.15  
**Nuitrack SDK version**: 1.12.15  

## Bug Fixes and Improvements
* Fixed crash when Face Tracking is manually enabled
* Fixed crash when Gesture Recognition is enabled and trying to perform gestures

# Release v0.36.14

**Release Date**: 28 Jul 2023  
**Nuitrack Runtime version**: 0.36.14  
**Nuitrack SDK version**: 1.12.14  

## Bug Fixes and Improvements
* Microsoft Visual C++ Redistributable packages are built into Nuitrack (no need to install separately anymore)
* Fixed the installation error related to UsbDk on **Windows x86** platform
* Fixed the correct operation of Nuitrack on **Windows x86** platform

# Release v0.36.13

**Release Date**: 20 Jul 2023  
**Nuitrack Runtime version**: 0.36.13  
**Nuitrack SDK version**: 1.12.13  

## Bug Fixes and Improvements
* Added support for **Orbbec Persee Plus (Android and Linux)**
* Added support for **Orbbec Astra Plus** on **Android arm32/arm64** and **Linux arm32/arm64** platforms
* Added support for **Orbbec Femto** and **Orbbec Femto W** on **Windows x64**, **Linux arm32/arm64/x64**, and **Android arm32/arm64** platforms

# Release v0.36.12

**Release Date**: 19 May 2023  
**Nuitrack Runtime version**: 0.36.12  
**Nuitrack SDK version**: 1.12.12  

## Bug Fixes and Improvements
* Init phase / start-up time was significantly optimized
* Nuitrack now supports multiple Kinect 2.0 sensors on Windows (even official Microsoft SDK can't do it)
* Correct operation with Orbbec Astra sensors on Windows w/ Kinect 2.0 Runtime installed

# Release v0.36.11

**Release Date**: 17 Apr 2023  
**Nuitrack Runtime version**: 0.36.11  
**Nuitrack SDK version**: 1.12.11  

## Bug Fixes and Improvements
* Fixed Nuitrack SDK conflicts with applications that use OpenVINO

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.10

**Release Date**: 18 Mar 2023  
**Nuitrack Runtime version**: 0.36.10  
**Nuitrack SDK version**: 1.12.10  

## New Features
* Added new features that will be unlocked gradually in future releases

## Bug Fixes and Improvements
* Improved stability

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.9

**Release Date**: 09 Mar 2023  
**Nuitrack Runtime version**: 0.36.9  
**Nuitrack SDK version**: 1.12.9

## Bug Fixes and Improvements
* Reduced Nuitrack initialization time
* Fixed runability of Nuitrack on bag/oni records using `Nuitrack::setConfigValue` API function

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.8

**Release Date**: 22 Feb 2023  
**Nuitrack Runtime version**: 0.36.8  
**Nuitrack SDK version**: 1.12.8

## Bug Fixes and Improvements
* Fixed `Mirror` and `RotateAngle` options for **Azure Kinect** sensor
* Fixed head position detection in **Nuitrack AI Skeletal Tracking** in a case when a person is turned backwards to the camera

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.7

**Release Date**: 21 Oct 2022  
**Nuitrack Runtime version**: 0.36.7  
**Nuitrack SDK version**: 1.12.7

## New Features
* **Nuitrack** now could process data from [**multiple depth sensors**](doc/Multiple_Depth_Sensors.md) simultaneously

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.6

**Release Date**: 17 Oct 2022  
**Nuitrack Runtime version**: 0.36.6  
**Nuitrack SDK version**: 1.12.6

## Bug Fixes and Improvements
* Fixed an issue with inability to activate some Orbbec Astra Plus sensors
* Fixed rare cases of Nuitrack hanging while calling `getDeviceList` using Kinect V2 sensors

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.5

**Release Date**: 06 Oct 2022  
**Nuitrack Runtime version**: 0.36.5  
**Nuitrack SDK version**: 1.12.5

## Bug Fixes and Improvements
* Fixed an issue where Orbbec Astra Pro sensors could have incorrect RGB streams on Linux platforms

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.36.4

**Release Date**: 30 Sep 2022  
**Nuitrack Runtime version**: 0.36.4  
**Nuitrack SDK version**: 1.12.4

## New Features
* Added the [**failure case recorder**](doc/Failure_Case_Recorder.md) feature

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* **Linux x64** rules do not apply for Orbbec Astra Plus. See the first item from [here](doc/Troubleshooting.md#linux) to apply the workaround 
* Gesture recognition may fail for a sitting pose

# Release v0.36.3

**Release Date**: 08 Sep 2022  
**Nuitrack Runtime version**: 0.36.3  
**Nuitrack SDK version**: 1.12.3

## Bug Fixes and Improvements

* Fixed **Nuitrack** working in headless mode on the **Linux x64** with **Kinect v2**
* Fixed work of Orbbec Astra sensors on the **Linux arm32**

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* **Linux x64** rules do not apply for Orbbec Astra Plus. See the first item from [here](doc/Troubleshooting.md#linux) to apply the workaround 
* Gesture recognition may fail for a sitting pose

# Release v0.36.2

**Release Date**: 03 Sep 2022  
**Nuitrack Runtime version**: 0.36.2  
**Nuitrack SDK version**: 1.12.2

## New Features

* New [**Nuitrack Daemon**](doc/Nuitrack_Daemon.md) application, which allows you to get data from Nuitrack using REST api

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* **Linux x64** rules do not apply for Orbbec Astra Plus. See the first item from [here](doc/Troubleshooting.md#linux) to apply the workaround 
* Gesture recognition may fail for a sitting pose

# Release v0.36.1

**Release Date**: 19 Aug 2022  
**Nuitrack Runtime version**: 0.36.1  
**Nuitrack SDK version**: 1.12.1

## New Features

* Added the [**person re-identification**](doc/Person_Reidentification.md) feature

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* **Linux x64** rules do not apply for Orbbec Astra Plus. See the first item from [here](doc/Troubleshooting.md#linux) to apply the workaround 
* Gesture recognition may fail for a sitting pose

# Release v0.36.0

**Release Date**: 28 June 2022  
**Nuitrack Runtime version**: 0.36.0  
**Nuitrack SDK version**: 1.12.0

## New Features

* Added new features that will be unlocked gradually in future releases

## Bug Fixes and Improvements

* For performance reasons disabled auto exposure for Orbbec Astra Plus by default, but it can be turned on in `nuitrack.config`  

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* **Linux x64** rules do not apply for Orbbec Astra Plus. See the first item from [here](doc/Troubleshooting.md#linux) to apply the workaround 
* Gesture recognition may fail for a sitting pose

# Release v0.35.15

**Release Date**: 25 May 2022  
**Nuitrack Runtime version**: 0.35.15  
**Nuitrack SDK version**: 1.11.14

## New Features

* Added support for the new revision of Orbbec Astra Plus for **Windows x64** and **Linux x64**.

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* **Linux x64** rules do not apply for Orbbec Astra Plus. See the first item from [here](doc/Troubleshooting.md#linux) to apply the workaround 
* Gesture recognition may fail for a sitting pose

# Release v0.35.14

**Release Date**: 18 March 2022  
**Nuitrack Runtime version**: 0.35.14  
**Nuitrack SDK version**: 1.11.13

## Bug Fixes and Improvements

* Fixed TBB conflicts with Unity, UE4, etc.
* Fixed Nuitrack signature

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.35.13

**Release Date**: 03 March 2022  
**Nuitrack Runtime version**: 0.35.13  
**Nuitrack SDK version**: 1.11.12

## New Features

* Added support the **Orbbec Astra** on **Android 9(Pie)** 

## Bug Fixes and Improvements

* Fixed Nuitrack AI Skeletal Tracking for the **Kinect v1 (Linux x64)**

## Known Issues

* Unstable work of Nuitrack on the **Android arm32** platform
* Gesture recognition may fail for a sitting pose

# Release v0.35.12

**Release Date**: 22 Nov 2021  
**Nuitrack Runtime version**: 0.35.12  
**Nuitrack SDK version**: 1.11.11

## New Features

* Added **Python Wrapper(beta)** for **Windows x64** and **Linux x64**, read more in the [readme](PythonNuitrack-beta/README.MD)

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.11

**Release Date**: 29 Oct 2021  
**Nuitrack Runtime version**: 0.35.11  
**Nuitrack SDK version**: 1.11.10

## Bug Fixes and Improvements

* Fixed infinite resizing of Nuitrack logo on **Windows**

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

# Release v0.35.10

**Release Date**: 8 Oct 2021  
**Nuitrack Runtime version**: 0.35.10  
**Nuitrack SDK version**: 1.11.9

## Bug Fixes and Improvements

* Fixed incorrect return value for the `GetInstancesJson` function
* Fixed updating the `pressure` field from the `Hand` structure
* Fixed need to manually install missing dependencies for **Linux**

## Known Issues

* USB cameras permission issue on **Android 9 (Pie) or higher** except for the **Intel RealSense** sensors
* Gesture recognition may fail for a sitting pose

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
