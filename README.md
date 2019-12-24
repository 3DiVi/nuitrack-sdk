## What is Nuitrack™ SDK?

**Nuitrack™** is a 3D tracking middleware developed by **3DiVi Inc**. This is a solution for skeleton tracking and gesture recognition that enables capabilities of Natural User Interface (NUI) on **Android**, **Windows**, and **Linux**.

**Nuitrack™ framework** is multi-language and cross-platform. **Nuitrack™ API**s include the set of interfaces for developing applications, which utilize Natural Interaction. The main purpose of **Nuitrack™** is to establish an API for communication with 3D sensors.

The **Nuitrack™ module** is optimized for ARM based processors, which means that you can use it with Android devices and embedded platforms.

 - Features:
   - Full Body Skeletal Tracking (19 Joints);
   - 3D Point Cloud;
   - User Masks;
   - Gesture Recognition;
   - Cross-platform SDK for Android, Windows, and Linux;
   - 3D Sensor independent: supports Kinect v1, Asus Xtion, Orbbec Astra, Orbbec Persee, Intel RealSense;
   - Unity and Unreal Engine Plugins;
   - OpenNI 1.5 compatible: OpenNI module allows you to move your OpenNI based apps developed for Kinect and Asus Xtion to other platforms, including Android.

 - Application areas:
   - Natural User Interface (NUI) for Windows/Linux/Android;
   - Games and Training (Fitness, Dance Lessons);
   - Medical Rehabilitation;
   - Smart Home;
   - Positional and Full Body Tracking for VR;
   - Audience Analytics;
   - Robot Vision.

You can learn more about **Nuitrack™** on [nuitrack.com](https://nuitrack.com).

## Getting Started

1. Clone or download this repository.
2. Download the **Nuitrack Runtime** installer:

   - using Git LFS:

   ```bash
   $ git lfs install
   $ git lfs pull --include "Platforms/*"
   ```

   - or [this link](./Platforms).

3. Install **Nuitrack** to your system following the [Installation Instructions](https://download.3divi.com/Nuitrack/doc/Installation_page.html).

4. Activate **Nuitrack** with our [Trial, Perpetual, or Online license](https://nuitrack.com/#pricing).

Now you can use **Nuitrack** and run the samples from the `Examples` folder.

## What’s included in the SDK:
| What | Description |
| --------- | ----------- | 
| **Documentation** | An offline copy of **Nuitrack** [documentation](https://download.3divi.com/Nuitrack/doc).||
| **Runtime Components** | **Nuitrack Runtime** installers for all supported platforms. ||
| **C#/.NET Wrapper** | **Nuitrack** supports **C#/.NET API** that allows you to integrate **Nuitrack** with your C# applications. ||
| **Code Samples** | These basic examples demonstrate how to use **Nuitrack SDK**. You can find **C++**/**C#** cross-platform samples with instructions inside. |
| **Unity Package** | This package allows you to [easily integrate](https://download.3divi.com/Nuitrack/doc/UnityTutorials_page.html) **Nuitrack SDK** into your Unity project. |
| **Unreal Engine Plugin** | This plugin allows to [develop](http://download.3divi.com/Nuitrack/doc/UnrealEngine_page.html) C++ applications with **UE 4.20** (Android only). |