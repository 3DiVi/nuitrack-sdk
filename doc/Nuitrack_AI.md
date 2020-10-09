# Nuitrack AI 

**Nuitrack AI** is the new version of Nuitrack skeleton tracking middleware from 3DiVi based on deep learning. Unlike the previous version of Nuitrack, Nuitrack AI processes not only a depth stream but also an RGB stream from an RGBD sensor. In addition to [skeleton tracking](#nuitrack-ai-skeleton-tracking), Nuitrack AI can also track faces and [objects](#nuitrack-ai-object-detection).

Advantages: 
* 360-degree tracking
* tracking of difficult poses (for example, tracking of a sitting or a lying person)

Nuitrack AI is available from the Nuitrack v0.33.0 release. 

<p align="center">
    <img width="480" src="img/nuitrack_ai_demo.gif">
</p>

## Nuitrack AI Skeleton Tracking

Nuitrack AI Skeleton Tracking is the Nuitrack AI feature that provides full body skeleton tracking (RGBD) based on deep learning.

* Supported platforms:
  * Windows x64
  * Ubuntu amd64
* Hardware requirements:
  * RGBD sensor

To turn on Nuitrack AI skeleton tracking: 
  * open the `nuitrack.config` file from `%NUITRACK_HOME%/data`
  * set the `"Skeletonization.Type"` parameter to `"CNN_HPE"`
  * set the `"DepthProvider.Depth2ColorRegistration"` parameter to `true`

To test skeleton tracking, run `nuitrack_sample.exe` from `%NUITRACK_HOME%/bin` (`/usr/bin/nuitrack_sample` for Ubuntu).

## Nuitrack AI Object Detection 

Nuitrack AI Object Detection is the Nuitrack AI feature that provides object detection based on deep learning. 

* Supported platforms:
  * Windows x64
  * Ubuntu amd64
* Hardware requirements:
  * RGBD sensor
  * CUDA compatible GPU (NVIDIA GTX 1050 Ti or better)
* Software dependencies:
  * [CUDA 9.0](https://developer.nvidia.com/cuda-90-download-archive)
  * [cuDNN 7](https://developer.nvidia.com/rdp/cudnn-archive#a-collapse765-90)

To turn on Nuitrack AI object detection: 
  * open the `nuitrack.config` file from `%NUITRACK_HOME%/data`
  * set the `"CnnDetectionModule.ToUse"` parameter  to `true`

To test AI object detection, run `nuitrack_sample.exe` from `%NUITRACK_HOME%/bin` (`/usr/bin/nuitrack_sample` for Ubuntu).

The following types of objects can be detected on a color stream:
  * bottle
  * cigarette
  * phone
  * laptop
  * bag
  * book
