# Installation Instructions

## Hardware Requirements and Minimum System Specifications 

There are no strict requirements for hardware performance with Nuitrack. RAM usage is below 200MB.

* For desktop processors, support for the AVX instructions set is required
* RGBD sensor (see the [list of compatible sensors and platforms](https://nuitrack.com/#sensors))

## Windows

### Software Requirements 

* Windows 7 or above

### Nuitrack Installation  

Download and install Nuitrack for your platform from [GitHub Releases](https://github.com/3DiVi/nuitrack-sdk/releases/latest).  
Available versions:
* Windows x64: `nuitrack-windows-x64.exe`
* Windows x86: `nuitrack-windows-x86.exe`

## Linux 

### Software Requirements 

* Ubuntu 14.04 or above

### Nuitrack Installation 

Download and install the Nuitrack Debian package for your platform from [GitHub Releases](https://github.com/3DiVi/nuitrack-sdk/releases/latest).  
Available versions:
* Ubuntu x64: `nuitrack-ubuntu-amd64.deb`
* Ubuntu/Debian arm64: `nuitrack-linux-arm64.deb`
* Ubuntu/Debian arm32: `nuitrack-linux-armhf.deb`

## Integration option

* Nuitrack provides two integration options, for more information, see [here](Nuitrack_Integration.md)

## Android

1. Allow your device to install applications from unknown sources. To do this, go to **Settings → Security and tick "Unknown sources"**.
2. Download and install the Nuitrack APK package for your platform from [GitHub Releases](https://github.com/3DiVi/nuitrack-sdk/releases/latest) (to install the APK package, locate it in a file manager, open and tap "INSTALL").  
   Available versions:
   * Android arm64: `Nuitrack_arm64.apk`
   * Android arm32: `Nuitrack.apk`
   * Android (TVico): `TVico.apk`
3. Launch the Nuitrack application. 
   <p align="center">
   <img width="400" src="img/install_1.png">
   </p> 
4. Wait for the Nuitrack installation. If the Nuitrack installation is successful, the message will be displayed as shown in the picture below:
   <p align="center">
   <img width="400" src="img/install_2.png">
   </p>

## License Activation

You can find the information about the Nuitrack licenses in the [Licensing](/doc/Licensing.md) section and [on our website](https://nuitrack.com/#pricing).

You can activate Nuitrack in one of two ways:
* [Using the Nuitrack application](#nuitrack-application)
* [Using API](#device-api)

### Nuitrack Application

The Nuitrack application can be used to check the sensor operation with Nuitrack and activate the Nuitrack license. 

#### Running the Licensing Tool 

* **Windows**:
  * Find the **Nuitrack** application in **Start Menu Windows** and run it. As an option, you can go to `%NUITRACK_HOME%\activation_tool` and run `Nuitrack.exe`.
* **Linux**:
  * Open a terminal and run the command: `nuitrack`
* **Android**:
  * Launch the **Nuitrack** app.

#### Activating the License 

1. Select a depth sensor from the drop-down list in the Nuitrack licensing tool.
2. \[optional\] Click the `Try Nuitrack!` button and wait for the compatibility test to complete. You can do this to make sure that your sensor works correctly with **Nuitrack**.
3. Enter your activation key and click `Activate` to activate the license (see more info about available licenses in [Nuitrack Licensing](/doc/Licensing.md)).
4. Click the `Try Nuitrack!` button to view the Nuitrack demo

### Device API

You can activate **Nuitrack** from your application using [Device API](/doc/Device_API.md).

For **Windows** and **Linux**, `nuitrack_device_api_sample` is included into the **Nuitrack Runtime** installation package. To run `nuitrack_device_api_sample`, open a terminal and run the command `nuitrack_device_api_sample`.

## Troubleshooting

At the [Troubleshooting](https://bit.ly/NuitrackTroubleshooting) page, you can find the most common errors related to Nuitrack installation / usage with possible solutions.  
If you can't find your issue there, please feel free to create a topic at the [Nuitrack community](https://community.nuitrack.com/)
