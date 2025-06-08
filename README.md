<p align="center"><a href="https://nuitrack.com/"><img src="doc/img/nuitrack-logo.png" width="70%" /></a></p>

## What's New (2025) ?
- :white_check_mark: 25Q2 - 0.38.2 - [**Unreal Engine 5 MetaHuman native support**](https://youtu.be/mZu1i1h05UQ) :rocket: 
- :white_check_mark: 25Q2 - 0.38.2 - [**Redesigned Nuitrack App**](https://youtu.be/cyA68b-wVNM?feature=shared) 
- :white_check_mark: 24Q4 - 0.37.24 - [**Unreal Engine 5 is now available directly from official Fab marketplace**](https://www.fab.com/listings/3aa43609-7897-4357-89e8-491917dd70a4)
- :white_check_mark: 24Q2 - 0.37.24 - [Write CSV files using Nuitrack App. No knowledge of C++ is required!](https://youtu.be/I7VpDD3VvEI)
- [**TouchDesigner**](/TouchDesigner) - the official release is now available.
- :movie_camera: [**Multisensor tracking**](/doc/Multiple_Depth_Sensors.md) Please refer to [this page](https://nuitrack.notion.site/Nuitrack-Holistic-Multi-sensor-fusion-Beta-1f102b18d9bd806391e7c5a2edb78360) for details on how to participate in **Nuitrack Holistic** beta testing program.
- :gear: [Failure cases recorder](/doc/Failure_Case_Recorder.md)

---
*Coming soon:*
- :soon: *UE Niagara particle system support*
- :soon: *Body measurements API*
- :soon: *Holistic skeletal tracking with multiple sensors*
- :soon: *Major update on tracking accuracy*

## What is Nuitrack™ SDK?

<p align="center"><a href="https://nuitrack.com/"><img src="doc/img/nuitrack-teaser.gif" width="70%" /></a></p>

**Nuitrack™** is the 3D body / skeletal tracking library for 3D / depth sensors developed by **[3DiVi Inc](https://www.3divi.com/)**.

It enables motion-based applications for any widespread:
- [3D sensors](https://bit.ly/nuitrack-depth-sensors) - Orbbec Astra2 / [Persee2](https://youtu.be/8MrS8yf04pc) / Femto Bolt / Femto Mega, Kinect v1/v2, [Kinect Azure](https://youtu.be/K7O-361UlfI), [Intel Realsense](https://youtu.be/gMPtV4NXtUo), Asus Xtion, LIPS, Structure Sensor, etc.
- hardware platforms - x64, x86, ARMv7, ARMv8
- OSes - Windows, Linux, Android, iOS

Inspired by first Microsoft Kinect, **Nuitrack™**'s mission is to provide strong skeletal tracking baseline for the next generation of immersive and analytical applications.  
Think of it as a *"Kinect for everything"*.

With its performance and flexibility **Nuitrack™** is capable to support the wide range of applications:
- from a real-time gesture recognition on [Raspberry Pi4](https://youtu.be/qyt4U7ZBj90)
- to a large-scale multisensor analytical systems

## Key Features
After being launched with [any supported depth sensor](https://bit.ly/nuitrack-depth-sensors) **Nuitrack** provides:


| **Depth map / 3D Point Cloud** | **Scene analysis, key elements like floor plane** | **Persons tracking and pixel-perfect segmentation for each of them** |
| :------------: |  :----------: | :-------------:  |
| [![Depth Map](https://dl.3divi.com/Nuitrack/img/3dcloud.jpg)](https://youtu.be/nX7kLXv65kU) | [![Floor plane](https://dl.3divi.com/Nuitrack/img/floor_detection.png)](https://youtu.be/5ehEcfCIBAU)  | [![Segmentation](https://dl.3divi.com/Nuitrack/img/segment.png)](/doc/Unity_Segment.md)  |
| **Highly-sophisticated _3D Skeletal Tracking_ for each person** | **Basic _Facial Analysis_ like age and emotion detection** | **_Hand Tracker_ and _Gesture Recognition_ high-level APIs for UI control** |
| [![Skeleton tracking](https://dl.3divi.com/Nuitrack/img/skeleton.jpg)](https://youtu.be/-PSN1AWc5Ro) | [![Face Tracking](https://dl.3divi.com/Nuitrack/img/facetracking.jpg)](https://youtu.be/HOm0-7qL5hk) | [![Hand Tracking and Gesture Recognition](/doc/img/Ugallery_15.gif)](/doc/Unity_Gallery.md) |

Nuitrack has two **Skeletal Tracking** engines:
   - "classical" - fast, stable and lightweight, highly-optimized for embedded hardware and limited CPU usage
   - [AI](https://youtu.be/S8dkf2MEZeM) - deep-learning based engine, which provides greater coverage for complex poses

Essentially Nuitrack provides a **human-centric spatial understanding tool** for your applications to engage with a user in a natural and intelligent way.

## Try out Nuitrack with your sensor

It's as quick and simple as 1-2-3:
1. Download the **Nuitrack Runtime** package for your [Platform of choice](https://github.com/3DiVi/nuitrack-sdk/releases)
2. Install it, in case of any issues please follow the [Installation Instructions](/doc/Install.md)
3. Just plug-in your sensor and launch Nuitrack executable from start menu

## Develop with Nuitrack

| C++ | C# | Python |
| ----| -- | ------ |
| <div align="center"><a href="doc/readme.md"><img src="https://dl.3divi.com/Nuitrack/img/cpp.png" width="70%" alt="" /></a></div> | <div align="center"><a href="doc/readme.md"><img src="https://dl.3divi.com/Nuitrack/img/csharp.png" width="70%" alt="" /></a></div> | <div align="center"><a href="/PythonNuitrack-beta"><img src="https://dl.3divi.com/Nuitrack/img/python.png" width="70%" alt="" /></a></div> | 

| Unity | Unreal Engine 5 Blueprints                                                                                                                                                                                  | :new: Touch Designer | :new: Docker |
| ----- |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------| --------------------------- | ------------ |
| <div align="center"><a href="https://youtu.be/2vYksQlLNWE"><img src="https://dl.3divi.com/Nuitrack/img/unity.png" width="70%" alt="" /></a></div> | <div align="center"><a href="https://www.fab.com/listings/3aa43609-7897-4357-89e8-491917dd70a4"><img src="https://dl.3divi.com/Nuitrack/img/ue.png" width="70%" alt="" /></a></div> | <div align="center"><a href="/TouchDesigner"><img src="https://dl.3divi.com/Nuitrack/img/touchdesigner.png" width="70%" alt="" /></a></div> | <div align="center"><a href="https://hub.docker.com/r/nuitrack/nuitrack"><img src="https://dl.3divi.com/Nuitrack/img/3rdparty/docker/PNG/01-symbol_blue-docker-logo.png" width="70%" alt="" /></a></div>

## Integration

* Nuitrack provides the ability to embed it into your application, which means it does not need to be separately installed on the PC of your customers, for more information, see [here](doc/Nuitrack_Integration.md)

### Additional resources

| Resource                                                             | Description                                                  |
|----------------------------------------------------------------------|--------------------------------------------------------------| 
| [Nuitrack.com](https://nuitrack.com)                                 | general information and license purchasing                   |
| [Licensing Dashboard](https://cognitive.3divi.com)                   | licenses/subscriptions management                            |
| [Troubleshooting page](https://bit.ly/NuitrackTroubleshooting)       | known issues with resolution                                 |
| [Community Forum](https://community.nuitrack.com)                    | troubleshooting, feature discussions                         |
| [Documentation](doc/readme.md)                                       | documentation index                                          |
| [Runtime Components](/Platforms)                                     | packages for all supported platforms                         |
| [C++/C# API](https://download.3divi.com/Nuitrack/doc/annotated.html) | auto-generated API reference (Doxygen)                       |
| [C++/C# Examples](/Examples)                                         | These basic examples demonstrate how to use **Nuitrack SDK** |
| [iOS [beta]](/iOS-beta)                                              | Get started with **Nuitrack** for **iOS**                    |

## Application Areas
- Games and Training (Fitness, Dance Lessons)
- Medical Rehabilitation
- Smart Home
- Natural/Gesture-based User Interface (NUI)
- [Full Body Tracking for AR / VR](https://youtu.be/7JqtB6Dt_9c)
- Audience Analytics
- Robot Vision

## Nuitrack in Academia 
Nuitrack is widely used in serious research, here are just a few selected references:
- [Detecting Short Distance Throwing Motions Using RGB-D Camera](https://www.jstage.jst.go.jp/article/pscjspe/2021A/0/2021A_45/_article/-char/ja/)
- [Planning Collision-Free Robot Motions in a Human–Robot Shared Workspace via Mixed Reality and Sensor-Fusion Skeleton Tracking](https://www.mdpi.com/2079-9292/11/15/2407)
- [Skeleton Driven Action Recognition Using an Image-Based Spatial-Temporal Representation and Convolution Neural Network](https://www.mdpi.com/1424-8220/21/13/4342)
- [Towards a Live Feedback Training System: Interchangeability of Orbbec Persee and Microsoft Kinect for Exercise Monitoring](https://www.mdpi.com/2411-9660/5/2/30)
- [ROBOGait: A Mobile Robotic Platform for Human Gait Analysis in Clinical Environments](https://www.mdpi.com/1424-8220/21/20/6786)
- [Robot-Assisted Gait Self-Training: Assessing the Level Achieved](https://www.mdpi.com/1424-8220/21/18/6213)
