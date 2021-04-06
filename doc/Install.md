# Installation Instructions

## Hardware Requirements and Minimum System Specifications 

* RGBD sensor (see the [list of compatible sensors and platforms](https://nuitrack.com/#sensors))

There are no strict requirements for hardware performance with Nuitrack. RAM usage is below 200MB. There is only one restriction for desktop processors: support for AVX instructions set is required.

## Windows

### Software Requirements 

* Windows 7/Windows 8/Windows 10
* Installed Microsoft Visual C++ Redistributable for Visual Studio:
    * [Visual C++ Redistributable 2015 (x86)](https://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x86.exe)
    * [Visual C++ Redistributable 2015 (x64)](https://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x64.exe)
    * [Visual C++ Redistributable 2017 (x86)](https://aka.ms/vs/15/release/VC_redist.x86.exe)
    * [Visual C++ Redistributable 2017 (x64)](https://aka.ms/vs/15/release/VC_redist.x64.exe)

_**Note**: You can also use the universal links to download the redistributable package for Visual Studio 2015, 2017, and 2019. Download the executable file depending on the architecture of your PC:_  
  * [Visual C++ Redistributable (x86)](https://aka.ms/vs/16/release/vc_redist.x86.exe)
  * [Visual C++ Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)

### Nuitrack Installation  

To install Nuitrack on Windows, follow the steps below: 

1. Download and run [nuitrack-windows-x86.exe](/Platforms/nuitrack-windows-x86.exe) (for Windows 32-bit) or [nuitrack-windows-x64.exe](/Platforms/nuitrack-windows-x64.exe) (for Windows 64-bit). Follow the instructions of the Nuitrack setup assistant.
2. After the installation is complete, **reboot the system** to let the system changes take effect.
3. Activate Nuitrack following the instructions sent to your email after the license purchase.  
4. [Optional] To use OpenNI 1.5 API, register the Nuitrack dynamic module for OpenNI 1.5:
   
  32-bit:
  ```
  "C:\Program Files (x86)\OpenNI\Bin\niReg.exe" -r <install-folder>\nuitrack\bin\libnuitrack_ni.dll <install-folder>\nuitrack\data
  ```

  64-bit:
  ```
  "C:\Program Files\OpenNI\Bin64\niReg64.exe" -r <install-folder>\nuitrack\bin\libnuitrack_ni.dll <install-folder>\nuitrack\data
  ```

_**Note**: To get started with a new device, you must first install the drivers for it. Contact the device vendor to get the drivers._

## Ubuntu Linux 

### Software Requirements 

* Ubuntu 14.04 or above 
* Architecture: AMD64 or ARM 32-bit

### Nuitrack Installation 

To install Nuitrack on Ubuntu, follow the steps below:

1. Download one of the following Debian packages depending on the target architecture:
    * [nuitrack-ubuntu-amd64.deb](/Platforms/nuitrack-ubuntu-amd64.deb) for AMD64
    * [nuitrack-linux-armhf.deb](/Platforms/nuitrack-linux-armhf.deb) for ARM 32-bit
2. Install the downloaded package using the following command: 
```
sudo dpkg -i <downloaded-package-name>.deb
```
3. **Reboot the system** to let the system changes take effect. 
4. Check that the environment variables **NUITRACK_HOME** and **LD_LIBRARY_PATH** are set correctly using the following commands:
```
echo $NUITRACK_HOME
echo $LD_LIBRARY_PATH
```
NUITRACK_HOME should be equal to */usr/etc/nuitrack*. LD_LIBRARY_PATH should include */usr/local/lib/nuitrack* path.

If the environment variables are empty, set them manually using the following commands (as root):
```
echo "export NUITRACK_HOME=/usr/etc/nuitrack" > /etc/profile.d/nuitrack_env.sh
echo "export LD_LIBRARY_PATH=/usr/local/lib/nuitrack" >> /etc/profile.d/nuitrack_env.sh
. /etc/profile.d/nuitrack_env.sh
``` 
5. [For Ubuntu 18.04] Install the [libpng12-0](https://packages.ubuntu.com/xenial/amd64/libpng12-0/download) package.
6. Activate Nuitrack following the instructions sent to your email after the license purchase. 

_**Note**: If you see "ERROR: Couldn't open device ..." message when trying to use Nuitrack, try to set permissions for USB devices with the following command:_
```
sudo chmod -R 777 /dev/bus/usb/
```
## Android

1. Allow your device to install applications from unknown sources. To do this, go to **Settings → Security and tick "Unknown sources"**.
2. Download [Nuitrack.apk](/Platforms/Nuitrack.apk) or [Nuitrack_arm64.apk](/Platforms/Nuitrack_arm64.apk) (for Android 64-bit) and install it. To install the APK package, locate it in a file manager, open and tap "INSTALL".
3. Launch the Nuitrack application. 

<p align="center">
<img width="400" src="img/install_1.png">
</p>
    
4. Wait for the Nuitrack installation. If the Nuitrack installation is successful, the message will be displayed as shown in the picture below:

<p align="center">
<img width="400" src="img/install_2.png">
</p>

5. Activate Nuitrack following the instructions sent to your email after the license purchase. 

## License Activation

You can find the information about the Nuitrack licenses in the [Licensing](/doc/Licensing.md) section and [on our website](https://nuitrack.com/#pricing).

## Troubleshooting 

In this section, you can find the information about the most common errors related to Nuitrack installation and usage and possible solutions. If you cannot find your problem in this section, please take a look at the [Knowledge Base](https://community.nuitrack.com/t/nuitrack-knowledge-base/807) in the [Nuitrack community](https://community.nuitrack.com/) or contact support-nuitrack@3divi.com

### Nuitrack Installation 

* If the installation freezes at 66%, please follow the steps below: 
1. Run `clear_sys_env.bat` as Administrator.
2. Run `maintenance_tool.exe`
3. Install Nuitrack from scratch.

* [Windows] If there were any errors during the automatic setup, please check the environment variables:
    * There should be the `NUITRACK_HOME` variable with the value of `<install-folder>\nuitrack`.
    * The 'PATH' variable should include the path to `<install-folder>\nuitrack\bin`.

_**Note**: To add a new environment variable or change the existing environment variable manually, use the "Environment Variables" dialog. To access it, open the "System" dialog (Win + Break), then select **Advanced system settings → Environment Variables...**_

<p align="center">
<img width="1000" src="img/install_windows.png"><br>
<b>Editing environment variables in Windows 10</b><br>
</p>

### Nuitrack Plugins 

* [Unity] If you run your project with Nuitrack in Unity and encounter the following exception: 

  ```
  NuitrackException (TerminateException): WARNING: Cannot load library module: C:\Program Files\Nuitrack\nuitrack\nuitrack/middleware/NuitrackModule.dll
  ERROR: TBB version mismatch: runtime library version is 9102, but the application was compiled with the 11102 version!
  ```
  follow the steps below (refer to [the Intel® Threading Building Blocks documentation](https://www.threadingbuildingblocks.org/docs/help/reference/appendices/known_issues/interoperability.html) for more details):
    * close the Unity editor;
    * replace the TBB library in your Unity editor with the library from Nuitrack:
      * *Windows*: copy the `tbb.dll` library from `%NUITRACK_HOME%/bin` to your Unity editor folder (for example, `C:\Program Files\Unity\Hub\Editor\2019.4.8f1\Editor`);
      * *Linux*: copy the `libtbb.so.2` library from `/usr/local/lib/nuitrack/` to your Unity editor folders (for example, `/home/user/2019.3.3f1/Editor` and `/home/user/2019.3.3f1/Editor/Data/Tools`);
    * run the Unity editor again.
	
* [Unreal Engine] If you run your project with Nuitrack in Unreal Engine and encounter the following exception: 

  ```
  NuitrackException (TerminateException): WARNING: Cannot load library module: C:\Program Files\Nuitrack\nuitrack\nuitrack/middleware/NuitrackModule.dll
  ERROR: TBB version mismatch: runtime library version is 9102, but the application was compiled with the 11102 version!
  ```
  follow the steps below (refer to [the Intel® Threading Building Blocks documentation](https://www.threadingbuildingblocks.org/docs/help/reference/appendices/known_issues/interoperability.html) for more details):
    * close the Unreal Editor;
    * replace the TBB library in your Unreal Editor with the library from Nuitrack:
      * *Windows*: copy the `tbb.dll` library from `%NUITRACK_HOME%/bin` to your Unreal Editor folder (for example, `C:\Program Files\Epic Games\UE_${VERSION}\Engine\Binaries\Win64`);
    * run the Unreal Editor again.

### 3D Sensor Known Issues 

#### All Sensors

* Make sure that the date and time settings on your device are correct.
* [Windows 10] Make sure that you allowed apps to access your camera: select **Settings → Privacy → Camera** and turn on **"Allow apps to access your camera"**.
* [Ubuntu and Nuitrack v0.28.0 or later] If you installed the .deb package and encounter the following error:
  ```
  WARNING: Can not load library module: /usr/etc/nuitrack/middleware/libNuitrackModule.so
  ERROR: Empty factory for DepthProvider
  ```

  it can indicate that the *libcurl4-openssl-dev* package is not installed to your system. Run the following command to check the presence of this package:
  ```
  ldd /usr/etc/nuitrack/middleware/libNuitrackModule.so | grep curl
  ```

  If you see the output `libcurl.so => not found`, install the package by executing the command:
  ```
  sudo apt-get install libcurl4-openssl-dev
  ```

#### Orbbec Astra Pro 

If your sensor is plugged in but is not detected by Nuitrack and is not displayed in the activation tool, please install the Microsoft Visual C++ 2013 redistributable package (instead of the version for Microsoft Visual C++ 2017). You can download this package on the [official Microsoft website](https://www.microsoft.com/en-us/download/details.aspx?id=40784).

#### Kinect V1

To install the driver for Kinect V1, download [Kinect SDK v1.8](https://www.microsoft.com/en-us/download/details.aspx?id=40278) and follow the [Install Instructions](https://www.microsoft.com/en-us/download/confirmation.aspx?id=40278).

_**Note**: If you use Windows 10, we recommend to run *KinectSDK-v1.8-Setup.exe* in compatibility mode for Windows 8._

#### Kinect V2

Starting from v0.24.0, Nuitrack supports Kinect V2 on Windows (64-bit) and Linux x64. To install the driver for Kinect V2, download [Kinect SDK v2.0](https://www.microsoft.com/en-us/download/details.aspx?id=44561) and follow the [Install Instructions](https://www.microsoft.com/en-us/download/confirmation.aspx?id=44561).

_**Warning**: Kinect SDK v2.0 does not support 32-bit version of Windows._

#### Intel® RealSense™ Depth Camera D400 series

##### Windows/Linux 

* Supported OS versions: Windows 7, Windows 8.1, Windows 10 and Ubuntu 14.04 or higher.
* Before using the sensor, you need to download and install Intel® RealSense™ SDK 2.0 [for Windows](https://goo.gl/hkhUdR) or [for Linux](https://goo.gl/wmFSuG).
* Supported camera firmware version: 5.12.7.100 or higher. To update the camera firmware, please, download the latest firmware from [the official Intel website](https://dev.intelrealsense.com/docs/firmware-releases).

##### Android

Support for RealSense on Android was added in Nuitrack v0.26.0.

* Recommended RealSense D415/D435 firmware version is 5.11.1.0
* Rooted and non-rooted devices can be used.
* Read permission for a root folder is required. You can check the permissions using any file manager, for example, ES File Manager: if the "/" folder is empty, then read permissions for the root folder aren't granted in the current firmware version of your Android device.
* USB-OTG support is required.
* RealSense D415 and D435 were tested with the following Android devices:
    * Odroid XU3 (Android 4.4.4 Kitkat) (rooted)
    * Samsung Galaxy S4 (Android 5 Lollipop) (non-rooted)
    * Samsung Galaxy S5 (Android 6 Marshmallow) (non-rooted)
    * Samsung Galaxy S6 (Android 7 Nougat) (non-rooted)
    * Samsung Galaxy S8/S8+ (Android 8 Oreo) (non-rooted)