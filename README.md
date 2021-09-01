## What is Nuitrack™ SDK?

**Nuitrack™** is a 3D tracking middleware developed by **3DiVi Inc**. This is a solution for skeleton tracking and gesture recognition that enables capabilities of Natural User Interface (NUI) on **Android**, **Windows**, and **Linux**.

**Nuitrack™ framework** is multi-language and cross-platform. **Nuitrack™ API**s include the set of interfaces for developing applications, which utilize Natural Interaction. The main purpose of **Nuitrack™** is to establish an API for communication with 3D sensors.

The **Nuitrack™ module** is optimized for ARM based processors, which means that you can use it with Android devices and embedded platforms.

 - Key Features:
   - Full Body Skeletal Tracking (19 Joints)
   - 3D Point Cloud
   - User Masks
   - Gesture Recognition
   - Cross-platform SDK for Android, Windows, and Linux
   - [3D Sensor independent](https://nuitrack.com/#sensors)
   - Unity and Unreal Engine Plugins
   - OpenNI 1.5 compatible: OpenNI module allows you to move your OpenNI based apps developed for Kinect and Asus Xtion to other platforms, including Android

 - Application Areas:
   - Natural User Interface (NUI) for Windows/Linux/Android
   - Games and Training (Fitness, Dance Lessons)
   - Medical Rehabilitation
   - Smart Home
   - Full Body Tracking for AR / VR
   - Audience Analytics
   - Robot Vision

You can learn more about **Nuitrack™** on [nuitrack.com](https://nuitrack.com).

## Getting Started

1. **Clone** this repository. Please note that it's important to clone this repository instead of downloading it. To clone the repository, run the commands below: 

   ```bash
   $ git clone https://github.com/3DiVi/nuitrack-sdk.git
   $ cd nuitrack-sdk
   ```
 
2. Download the **Nuitrack Runtime** installer:

   - using Git LFS:

   ```bash
   $ git lfs install
   $ git lfs pull --include "Platforms/*"
   ```

   - or [this link](/Platforms)

3. Download `NuitrackSDK.unitypackage`:
   - using Git LFS:

   ```bash
   $ git lfs pull --include "Unity3D/*"
   ```
  
   - or [this link](/Unity3D)

4. Install **Nuitrack** to your system following the [Installation Instructions](/doc/Install.md)

5. Activate **Nuitrack** with our [Trial, Perpetual, or Online license](https://nuitrack.com/#pricing)

Now you can use **Nuitrack** and run the samples from the `Examples` folder.

## What’s included in the SDK:
| What | Description |
| --------- | ----------- | 
| **[Documentation](doc/readme.md)** | An offline copy of **Nuitrack** documentation ||
| **[Runtime Components](/Platforms)** | **Nuitrack Runtime** installers for all supported platforms ||
| **[C#/.NET and C++ API](https://download.3divi.com/Nuitrack/doc/annotated.html)** | It allows you to integrate **Nuitrack** with your **C#/C++** applications ||
| **[iOS [beta]](/iOS-beta)** | Get started developing for **iOS** with **Nuitrack** ||
| **[Code Samples](/Examples)** | These basic examples demonstrate how to use **Nuitrack SDK** |
| **[Unity Package](/doc/readme.md#unity-tutorials)** | This package allows you to easily integrate **Nuitrack SDK** into your Unity project |
| **[Unreal Engine Plugin](/doc/readme.md#unreal-engine-tutorials)** | This plugin allows you to develop applications with **UE 4.20** |
