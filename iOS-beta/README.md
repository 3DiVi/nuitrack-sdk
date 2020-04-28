# NUITRACK for iOS [beta]

Support for **Structure** depth sensors only.

This Nuitrack version is for usage in **iOS** apps.
Here is an example of using `nuitrack.framework` in **XCode**.

Requirements:

 - Structure SDK version: **0.11.2**
 - Minimum iOS version: **11.4**;
 - Architecture: **arm64**;
 - Bitcode is **not supported**.

## Setup XCode Project:

1. Create an XCode project (we'll use a "Single View App" with Objective-C language). Also you can set *"General -> Deployment Target"* to *"11.4"* (it's minimum for Nuitrack).

2. Drag-and-drop `nuitrack.framework` and `Structure.framework` to *"Project navigator -> %project name%"*. Make sure that the frameworks were copied to the project directory (next to your `*.xcodeproj` file) because it's a default search path for external frameworks. If you use a different way to include the frameworks to your project, make sure that *"Build Settings -> Framework Search Path"* is correct.

3. To avoid the build error "... has C-linkage specified, but returns user-defined type ...", go to *"Build Settings -> Apple Clang - Custom Compiler Flags -> Other Warning Flags"* and add *"-Wno-return-type-c-linkage"*.

4. Disable Bitcode: go to *"Build Settings -> Build Options -> Enable Bitcode"* and tick *"No"*.

5. Copy the framework: click *"General -> Embedded Binaries -> +"* and select `nuitrack.framework` and `Structure.framework`. After that, check *"General -> Linked Frameworks and Libraries"*: if you see two `nuitrack.framework` or `Structure.framework` in the list, remove one of them.

6. Update your project `Info.plist` to work with Structure Sensor. Add a new key `"SupportedExternalAccessoryProtocols"` (if it doesn't exist) and add 3 items into this key: `"io.structure.depth"`, `"io.structure.infrared"`, `"io.structure.control"`. As an option, you can insert the lines below into the source code of `into.plist`:

        	...
        
        	<key>UISupportedExternalAccessoryProtocols</key>
        	<array>
        		<string>io.structure.depth</string>
        		<string>io.structure.infrared</string>
        		<string>io.structure.control</string>
        	</array>
        
        	...

7. Make sure that the project can use Nuitrack: `"#include <nuitrack/Nuitrack.h>"`, `"tdv::nuitrack::Nuitrack::init();"` (don't forget to set the source file extension to `*.mm` instead of `*.m`).

_**Note:** The Structure SDK uses the main thread at least during the initialization step. Try to use Nuitrack from a different thread and do not keep the main thread always busy or synchronized to Nuitrack._

## Setting Up the Project for Working with an RGB Camera

1. Import the `ACFoundation` framework and add a request for access to the RGB camera of the device:

    		#import <AVFoundation/AVFoundation.h>

    		...
    			// ask for access to camera once
    			[AVCaptureDevice
    				requestAccessForMediaType:AVMediaTypeVideo
    				completionHandler:^(BOOL granted) {
    					NSLog(@"CameraAccess: %s \n", (granted?"true":"false"));
    				}
    			];
    		...


2. Add `AVFoundation.framework` to *"General -> Linked Frameworks and Libraries"*;

3. Update your project `Info.plist`. Add a new key `"Privacy - Camera Usage Description"` and fill it with your own value. As an option, you can insert the lines below to the source code of `into.plist`:

    		...

    		<key>NSCameraUsageDescription</key>
    		<string>Camera image used for visualization</string>
    		...


## Configuring Nuitrack

You can configure Nuitrack in two ways: after Nuitrack initialization or using a configuration file.
The configuration file contains the main parameters by default. You can find it in the framework `nuitrack.framework/data/nuitrack.config`.
To override the parameters specified in `nuitrack.config`, you have to call the function `Nuitrack::setConfigValue(*,*)` after Nuitrack initialization.

Here is a list of useful Nuitrack parameters:
 - `"DepthProvider.RotateAngle"`: Rotation of received frames. _Possible values: `0`, `90`, `180`, `270`_;
 - `"DepthProvider.RGB"`: Support for RGB frames. _Possible values: `"Auto"`, `"On"`, `"Off"`_;
 - `"DepthProvider.Depth2ColorRegistration"`: Registration. _Possible values: `false`, `true`_;
 - `"DepthProvider.Mirror"`: Image mirroring. _Possible values: `false`, `true`_.

Here is an example of configuring/updating the parameters of Nuitrack initialization:

        	...
        
        	//inintialize nuitrack
        	Nuitrack::init(config_file);
        
        	//rotate frames
        	Nuitrack::setConfigValue("DepthProvider.RotateAngle", "90");
        	//turn registration mode on
        	Nuitrack::setConfigValue("DepthProvider.Depth2ColorRegistration", "true");
        	//turn mirror mode on
        	Nuitrack::setConfigValue("DepthProvider.Mirror", "true");
        
        	...

## Nuitrack Activation

Nuitrack framework contains the tool for automatic activation. Now Nuitrack can be activated directly from the application.

To activate the license, you have to specify the key in the `"ActivationKey"` field of the configuration. Also, the application should have access to the Internet for activation. If you use proxy, set it in the `"Network.ProxyUrl"` field of the configuration. To get a result of Nuitrack activation use `Nuitrack::getConfigValue("ActivationResult")` method after DepthSensor module initialization. For example:

		...

		// inintialize nuitrack
		Nuitrack::init();

		// set config
		Nuitrack::setConfigValue("ActivationKey", "xxxxxxxxxx");
		Nuitrack::setConfigValue("Network.ProxyUrl", "192.168.1.2:1234");

		// inintialize DepthSensor module
		DepthSensor::create();

		// get activation result (possible values: "FAIL" or a name of activated license type)
		std::string activation_result = Nuitrack::getConfigValue("ActivationResult");

		...

_**Note**: "ActivationKey" and "Network.ProxyUrl" parameters should be set immediately after Nuitrack initialization._

## Nuitrack Sample

There is an XCode project `nuitrack_sample` next to this `README` file. The sample was created by following the above steps and includes all Nuitrack modules. You could use it as a reference example. All you need to do is to setup *"General -> Signing -> Team"* and connect your device to XCode in development mode.

## Unity package for iOS

Support for iOS was added in the latest release of `NuitrackSDK.unitypackage`. Follow the steps below to run Unity samples on iOS:

1. Create a new **Unity 3D** project.

2. Import `NuitrackSDK.unitypackage` (disable the project `Tutorials/Zombie Nightmare (RIFT)` to speed up loading).

3. Open the scene `/Assets/NuitrackSDK/NuitrackDemos/allModulesScene.unity`.

4. Exclude the platforms *"Editor"* and *"Standalone"* for `/Assets/NuitrackSDK/Nuitrack/NuitrackAssembly/nuitrack.net.dll`.

5. Include the platforms *"Editor"* and *"Standalone"* for `/Assets/NuitrackSDK/Nuitrack/NuitrackAssembly/iOS/nuitrack.net.dll`.

6. Drag-and-drop `nuitrack.framework` and `Structure.framework` to `/Assets/NuitrackSDK/Nuitrack/NuitrackAssembly/iOS/` or other directory.

7. Tick `Add to Embedded binaries` parameter in `Platform settings` for added frameworks.

8. Open `File > Build Settings` and click *"Add Open Scenes"* to add *"allModulesScene"*.

9. In *"Build Settings"*, click *"Player Settings"* and set the following parameters:

     - `Target minimum iOS version` to *"11.4"*
     - `Architecture` to *"ARM64"*

10. Open `File > Build Settings` and click *"Build"* to build the **Xcode** project for **iOS**.

11. Open the **XCode** project and set up *Team ID*.

12. Select a device and run the **XCode** project.

_**Note**: Unity samples (except `NuitrackDemos/allModulesScene`) weren't updated to be used with Structure SDK (please read "Note" in the section "Setup XCode Project"). Therefore, they might not initilize **Structure Sensor** on a cold boot._
