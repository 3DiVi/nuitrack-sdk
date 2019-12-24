# Installation Instructions

## Windows

Supported Windows versions: Windows 7, Windows 8, Windows 10.

To install Nuitrack on Windows, follow the steps below: 

1. Download and run [nuitrack-windows-x86.exe](http://download.3divi.com/Nuitrack/platforms/nuitrack-windows-x86.exe) (for Windows 32-bit) or [nuitrack-windows-x64.exe](http://download.3divi.com/Nuitrack/platforms/nuitrack-windows-x64.exe) (for Windows 64-bit). Follow the instructions of the Nuitrack setup assistant. 
2. **Re-login** to let the system changes take effect. 
3. [Required] Make sure that you have installed Microsoft Visual C++ Redistributable for Visual Studio on your computer. If not, install this package depending on your VS version and architecture:
    * [Visual C++ Redistributable 2015 (x86)](https://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x86.exe)
    * [Visual C++ Redistributable 2015 (x64)](https://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x64.exe)
    * [Visual C++ Redistributable 2017 (x86)](https://aka.ms/vs/15/release/VC_redist.x86.exe)
    * [Visual C++ Redistributable 2017 (x64)](https://aka.ms/vs/15/release/VC_redist.x64.exe)

_**Note**: You can also use the universal links to download the redistributable package for Visual Studio 2015, 2017 and 2019. Download the executable file depending on the architecture of your PC:_  
  * [Visual C++ Redistributable (x86)](https://aka.ms/vs/16/release/vc_redist.x86.exe)
  * [Visual C++ Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)

4. If you observe any issues with automatic setup, set up environment variables manually (**you can skip this step if the environment variables have been set automatically**):
    * Create an environment variable with the name of `NUITRACK_HOME` and value of `<install-folder>\nuitrack`.
    * Add `<install-folder>\nuitrack\bin` to the `PATH` environment variable.

_**Note**: To add a new environment variable or change the existing environment variable manually, use the "Environment Variables" dialog. To access it, open the "System" dialog (Win + Break), then select **Advanced system settings → Environment Variables...**_

<p align="center">
<img width="1000" src="img/install_windows.png"><br>
<b>Editing environment variables in Windows 10</b><br>
</p>

5. [Optional] To use OpenNI 1.5 API, register the Nuitrack dynamic module for OpenNI 1.5:
   
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

Supported Ubuntu version is 14.04 and above. Supported architectures are AMD64 and ARM 32-bit.

To install Nuitrack on Ubuntu, follow the steps below:

1. Download one of the following Debian packages, depending on the target architecture:
    * [nuitrack-ubuntu-amd64.deb](http://download.3divi.com/Nuitrack/platforms/nuitrack-ubuntu-amd64.deb) for AMD64
    * [nuitrack-linux-armhf.deb](http://download.3divi.com/Nuitrack/platforms/nuitrack-linux-armhf.deb) for ARM 32-bit
2. Install the downloaded package using the following command: 
```
sudo dpkg -i <downloaded-package-name>.deb
```
3. Log out to let the system changes take effect. 
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

_**Note**: If you see "ERROR: Couldn't open device ..." message when trying to use Nuitrack, try to set permissions for USB devices with the following command:_
```
sudo chmod -R 777 /dev/bus/usb/
```
## Android

1. Allow your device to install applications from unknown sources. To do this, go to **Settings → Security and tick "Unknown sources"**.
2. Download [Nuitrack.apk](http://download.3divi.com/Nuitrack/platforms/Nuitrack.apk) and install it. To install the APK package, locate it in a file manager, open and tap "INSTALL".
3. Launch the Nuitrack application. 

<p align="center">
<img width="400" src="img/install_1.png">
</p>
    
4. Wait for Nuitrack installation. If the Nuitrack installation is successful, the message will be displayed as shown in the picture below:

<p align="center">
<img width="400" src="img/install_2.png">
</p>

## License Activation

There are two Nuitrack versions: **Nuitrack Trial** and **Nuitrack Pro**.

**Nuitrack Trial** is free and has the time limit. This Nuitrack version stops working after running for three minutes, so you need to restart it. To use Nuitrack Trial, you have to download Nuitrack runtime, run the activation tool and enter the trial license key. You can get the trial license at [our website](https://nuitrack.com/#pricing) or generate a trial key in your [personal account](https://cognitive.3divi.com/). To generate the key in your account, go to the tab “Licenses”, click “Activate” in the box “Trial licenses” and then click “Generate”. Nuitrack Trial is intended for demo and evaluation purposes only. Trial license is not linked to a sensor but it’s linked to your PC.

**Nuitrack Pro** is for commercial applications. It allows to develop and sell applications based on Nuitrack. There are two types of Nuitrack Pro licenses: *online* and *perpetual*:
  * **Nuitrack Pro Online** is a cross-platform license, which is **not linked** to a sensor or PC and fully portable. Online subscription requires periodic connection to the Internet.
  * **Nuitrack Pro Perpetual** is a cross-platform license, which is **linked** to your sensor. This license has unlimited period of validity and you don’t have to connect to the Internet after activation.

You can purchase **Nuitrack Pro Online** and **Nuitrack Pro Perpetual** at [our website](https://nuitrack.com/#pricing). You can manage all your Nuitrack licenses (Trial and Pro) in your [personal account](https://cognitive.3divi.com/).

## 3D Sensor Known Issues 
### All Sensors
* Make sure that the date and time settings on your device are correct.
* [For Windows 10] Make sure that you allowed apps to access your camera: select **Settings → Privacy → Camera** and turn on **"Allow apps to access your camera"**.
* [For Ubuntu and Nuitrack v0.28.0 or later] If you installed the .deb package and encounter the following error:
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

### Kinect V1
To install the driver for Kinect V1, download [Kinect SDK v1.8](https://www.microsoft.com/en-us/download/details.aspx?id=40278) and follow the [Install Instructions](https://www.microsoft.com/en-us/download/confirmation.aspx?id=40278).

_**Note**: If you use Windows 10, we recommend to run *KinectSDK-v1.8-Setup.exe* in compatibility mode for Windows 8._

### Kinect V2

Starting from v0.24.0, Nuitrack supports Kinect V2 on Windows (64-bit) and Linux x64. To install the driver for Kinect V2, download [Kinect SDK v2.0](https://www.microsoft.com/en-us/download/details.aspx?id=44561) and follow the [Install Instructions](https://www.microsoft.com/en-us/download/confirmation.aspx?id=44561).

_**Warning**: Kinect SDK v2.0 does not support 32-bit version of Windows._

### Intel® RealSense™ Depth Camera D415

#### Windows/Linux 

* Supported OS versions: Windows 8.1, Windows 10 and Ubuntu 14.04 or higher.
* Before using the sensor, you need to download and install Intel® RealSense™ SDK 2.0 [for Windows](https://goo.gl/hkhUdR) or [for Linux](https://goo.gl/wmFSuG).
* Supported camera firmware version: 5.8.15 or higher. To update the camera firmware, please, download the latest firmware from [the official Intel website](https://downloadcenter.intel.com/download/27514/Windows-Device-Firmware-Update-Tool-for-Intel-RealSense-D400-Product-Family?v=t).

#### Android

Support for RealSense on Android was added in Nuitrack v.

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

