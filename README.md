<p align="center"><a href="https://nuitrack.com/"><img src="doc/img/nuitrack-logo.png" width="70%" /></a></p>

## What's New ? 
- **:white_check_mark: May'22 - 0.35.15 - Official support for [Orbbec Astra+](https://youtu.be/NP5ayeqUr4I)**
- :white_check_mark: Nov'21 - 0.35.12 - [Python API](/PythonNuitrack-beta)

*Coming soon*:
- :soon: Holistic skeletal tracking on multiple sensors
- :soon: Person re-identification
- :soon: Support for new Orbbec Astra Pro+, Persee+

## What is Nuitrack™ SDK?

<p align="center"><a href="https://nuitrack.com/"><img src="doc/img/nuitrack-teaser.gif" width="50%" /></a></p>

**Nuitrack™** is an ultimate 3D body tracking solution developed by **[3DiVi Inc](https://www.3divi.com/)**.

It enables skeletal tracking and body motion analytics applications for virtually any widespread 
- depth sensors (Orbbec Astra, Kinect v1/v2, [Kinect Azure](https://youtu.be/K7O-361UlfI), [Intel Realsense](https://youtu.be/gMPtV4NXtUo), Asus Xtion, LIPS, Structure Sensor, etc.)
- hardware platforms (x64, x86, ARMv7, ARMv8)
- OSes (Windows, Linux, Android, iOS)
- and development environments (C++, C#, Python, Unity, Unreal)

Being initially inspired by Microsoft Kinect, **Nuitrack™**'s mission is to provide strong skeletal tracking baseline for next generation of immersive and analytical applications beyond any specific platform or hardware. Think of it as *"Kinect for anything"*.

With its performance and flexibility resulting from 10 years of development **Nuitrack™** is capable to support wide range of applications:
- starting from a real-time gesture recognition on small-footprint embedded platform like [Raspberry Pi4](https://youtu.be/qyt4U7ZBj90) 
- to a large-scale multisensor analytical system (which is launched on 18-Cores workstation system)

Now it's all yours - Try it, Use it, Challenge it!

You can learn more about **Nuitrack™** on [nuitrack.com](https://nuitrack.com).

## Key Features
   - Full Body Skeletal Tracking (19 Joints)
   - 3D Point Cloud
   - User Masks
   - Gesture Recognition
   - [3D Sensor independent](https://nuitrack.com/#sensors)
   - Unity and Unreal Engine Plugins

## Application Areas
   - Natural User Interface (NUI) for Windows/Linux/Android
   - Games and Training (Fitness, Dance Lessons)
   - Medical Rehabilitation
   - Smart Home
   - Full Body Tracking for AR / VR
   - Audience Analytics
   - Robot Vision

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
| **[Python Wrapper [beta]](/PythonNuitrack-beta)** | **Nuitrack** supports **Python API** that allows you to integrate **Nuitrack** with your Python applications ||
| **[iOS [beta]](/iOS-beta)** | Get started developing for **iOS** with **Nuitrack** ||
| **[Code Samples](/Examples)** | These basic examples demonstrate how to use **Nuitrack SDK** |
| **[Unity Package](/doc/readme.md#unity-tutorials)** | This package allows you to easily integrate **Nuitrack SDK** into your Unity project |
| **[Unreal Engine Plugin](/doc/readme.md#unreal-engine-tutorials)** | This plugin allows you to develop applications with **UE 4.20** |
