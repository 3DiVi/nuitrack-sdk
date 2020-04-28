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
