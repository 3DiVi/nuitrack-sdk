# Device API

Nuitrack Device API allows you to enumerate and activate compatible depth sensors and run Nuitrack with a selected depth sensor. Please note that you can use several sensors only if you run several Nuitrack instances (1 sensor = 1 process). 

In *Examples*, you can find two samples that show how to use Nuitrack Device API:
* [`nuitrack_device_api_sample`](/Examples/nuitrack_device_api_sample) (C++)
* [`nuitrack_csharp_device_api_sample`](/Examples/nuitrack_csharp_device_api_sample) (C#)

There's also `nuitrack_device_api_sample` in the Nuitrack runtime that allows you to select and activate a specific sensor by its serial number and run Nuitrack with this sensor. You can find this sample in `%NUITRACK_HOME%/bin` on Windows or in `/usr/bin/` on Linux. 

_**Note:** If you want to run Nuitrack with several depth sensors, we recommend you to use the sensors of the same type, for example, 2 RealSense D435. You can see the list of all supported sensors and platforms [at our website](https://nuitrack.com/#sensors)._

Please refer also to the [Linking Nuitrack to your application](/doc/Nuitrack_linking.md) page. See an example of Nuitrack integration in our tutorial [Integrating Nuitrack with your application (Windows/Ubuntu)](/doc/Tutorial_integration.md).