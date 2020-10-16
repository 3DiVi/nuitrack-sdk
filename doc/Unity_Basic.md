# Creating your First Unity Project using Nuitrack SDK

In this very first tutorial, you'll learn how to create a basic Unity project using Nuitrack SDK. As a result, you'll get a simple app with an option of skeleton detection and tracking, which can be modified into a full-fledged VR app.

You can find the finished project in **Nuitrack SDK**: **Unity 3D → NuitrackSDK.unitypackage → Tutorials → First Project**

<p align="center">
<img width="450" src="img/Ubasic_image10.gif">
</p>

## Setting up the Environment

1. As a first step, download and install Nuitrack following our [installation instructions](Install.md). 
2. Download Unity [from the official website](https://unity3d.com/get-unity/download).

_**Note**: To ensure stable operation of a project, we recommend you to use Unity 2017.4 or higher for Windows and Linux projects and Unity 2017.4 for Android projects._

3.  Create a new project.

<p align="center">
<img width="650" src="img/Ubasic_image1.png">
</p>

4.  To create a project, select the appropriate platform, for example, Android: **File → Build Settings → Android** and then select **Switch Platform**.

_**Note**: In this tutorial we create an Android project, however, you can create a project using Nuitrack SDK for any platform that you like._

5.  Download and install **SDK** and **JDK**. To do this, select **Edit → Preferences → External Tools** and click **Download** in the relevant sections. After that, your browser will open the web sites, where you can download the required **SDK** and **JDK**.

<p align="center">
<img width="450" src="img/Ubasic_image3.png">
</p>

6.  And now, here is the most interesting part that will allow us to create projects with skeleton detection and tracking. Download [Nuitrack SDK](https://github.com/3DiVi/nuitrack-sdk) and import it to the project (except for the folder **Tutorials/First Project**). To import **Nuitrack SDK**, select **Assets → Import Package → Custom Package → {Root}/NuitrackSDK/Unity3d/Nuitrack.unitypackage** by right-clicking in the **Project** tab.

_**Note**:_  
**What sensors can I use with my app?**  
*You can use any of the supported sensors for your application (see the list of supported sensors at the [Nuitrack official website](https://nuitrack.com/#sensors)). For example, you can use [**TVico**](https://tvico.io/), which is an interactive Android computer with pre-installed Nuitrack. You can find the [TVico User Guide](/doc/TVico_User_Guide.md) in our documentation.*

7.  As a result, you will have a configured development environment with all the necessary components for the build.

<p align="center">
<img width="450" src="img/Ubasic_image2.png">
</p>

## Setting up the Build

1.  Now that we have configured the environment, we need to determine some important features of the project build. First of all, save the empty scene: **File → Save Scenes**

2.  Add the scene to the project: **File → Build Settings → Add Open Scenes** or select **{Saved Scene}** in the **Project** tab and drag-and-drop it to the **Scenes in Build** field of the **Build Settings** window.
    
3.  Do not forget to put you company name and product name in the relevant fields: **File → Build Settings → Player Settings → Company Name, Product Name**.
    
4.  In the **Identification** section, select a name for the build (**Bundle Identifier**) as follows: **com.(CompanyName).(ProductName)**. Keep in mind that you won't be able to build the project with the default name.
    
_**Note**: Do not use numbers when typing in your CompanyName and ProductName._

5.  Also, select minimum API level in this section for correct operation of Nuitrack: **Minimum API Level → Android 4.4 'Kit Kat' (API Level 19)**.

<p align="center">
<img width="450" src="img/Ubasic_image5.png">
</p>

_**Note**: To reduce the size of a final .apk file, select **ARMv7** type of architecture in the **Device Filter** section._

6.  Now that everything is set up, let\'s build the project: **File → Build Settings → Build**

_**Note**_  
*Hotkeys:*  
_**Ctrl + Shift + B** - Build Settings_  
_**Ctrl + B** - Build_  

7.  If the build was successful, a new window will open with your application in the ```.apk``` format, which can be run on the Android device. When you run the app on your device, you will see the image as shown below:

<p align="center">
<img width="450" src="img/Ubasic_image4.png">
</p>

8.  During the project build, all errors and warnings (if any) are displayed in the **Console**.

_**Note**: After the first build, when you have a ready-made .apk file, you can perform build and installation on the device in one click using **Ctrl + B**. To do this, activate **Developer Mode** in the settings of the mobile device and connect it to the computer via USB. Then press **Ctrl + B** in Unity. As a result, the project will be built, installed and launched on your mobile device._

## Initializing the Nuitrack SDK, Setting up the Scene and Checking the Skeleton Detection

1.  Now that your environment is set up, you're set to start doing work. In the **Project** tab, select **Asset → Nuitrack → Prefabs** and drag-and-drop the **NuitrackScripts.prefab** object to the scene or to the **Hierarchy** tab. There must be only one object in the scene. This object contains the scripts that interact with Nuitrack.

2.  Set up the characteristics of the **NuitrackScripts** object by right-clicking on it. Check **Skeleton Tracker Module On** in the **Nuitrack Manager** section in the **Inspector** tab. This very module takes care of detection and tracking of a user's skeleton.

<p align="center">
<img width="550" src="img/Ubasic_image7.png">
</p>

As you can see, there are several more modules in this field. We'll cover them in the following tutorials.

3.  Create an empty C\# Script: **Create C\# Script** by right-clicking in the Project tab.
    
4.  To get information about joints, we first need to detect the user. First, let's check whether the user is in the frame or not using the ```CurrentUserTracker.CurrentUser! = 0``` condition. The result will be displayed as a 'User found' or 'User not found' message, which is stored in the ```message``` variable and displayed by the ```OnGUI()``` method. See the link at the end of the document to learn more about Execution Order of Event Functions.

```cs
using UnityEngine;
 
    public class NativeAvatar : MonoBehaviour
    {
        string message = "";
        
        void Update()
        {
            if (CurrentUserTracker.CurrentUser != 0)
            {
                message = "User found";
            }
            else
            {
                message = "User not found";
            }
        }
        
        // Display the message on the screen
        void OnGUI()
        {
            GUI.color = Color.red;
            GUI.skin.label.fontSize = 50;
            GUILayout.Label(message);
        }
    }

```
_**Note**: Save changes in the script code so that they take effect in the Unity editor._

5.  Create an empty object on the scene so that Unity can execute **NativeAvatar.cs**: **GameObject → Create Empty** and then
drag-and-drop the script to that object.

6.  Build the project (Ctrl + B) and check the app operation on your device.

7.  If everything is done correctly, at this stage the user will be detected. Depending on the result, you will see a message 'User found' or 'User not found' in the scene in the upper right corner. Time to move onto more complex things!

<p align="center">
<img width="450" src="img/Ubasic_image6.png">
</p>

_**Note**_  
**How can I get the full log from the device?**  
*To get the Unity app log from your mobile device, install the Android Debug Bridge (adb) into your computer. Run the following command in the console: `adb logcat -s Unity`. When you run the application on your phone, the log will be displayed in the console.*

## Creating Objects for Skeleton Visualization

1.  Now that we initialized Nuitrack and checked the detection of the user, we can go to the next stage, which presupposes obtaining data on the skeleton and visualization of the joints.
2.  Let's determine the joints of the skeleton, which we need to get: declare the ```nuitrack.JointType``` and ```GameObject``` arrays. Each element of the ```GameObject``` array will correspond to a specific ```typeJoint```. In the app, the joint will be rendered in the form of the ```PrefabJoint``` that we selected.

```cs
public nuitrack.JointType[] typeJoint;
GameObject[] CreatedJoint;
public GameObject PrefabJoint;
```

3.  In Unity, select the required number of joints in the object characteristics: **Native Avatar → Type Joint** and specify the
joint types that you need. Drag-and-drop the prefab that will be used for displaying the user's joints (for example, a white sphere) to the **Prefab Joint**.

<p align="center">
<img width="450" src="img/Ubasic_image9.png">
</p>

_**Note**: To create a prefab in Unity (for example, a sphere), select **GameObject → 3D Object → {Sphere}**. Scale down the sphere that appeared on the scene so that its size is about 10 cm (1 Unity unit ~ 1 m). Create a prefab in the **Project** tab: **Right Click → Create → Prefab**. Then, drag-and-drop the created sphere to the prefab. To learn more about prefabs, see the link at the end of this tutorial._ 

4.  Let's create objects for visualization of joints using the saved prefab: create an array of the same dimension as the ```typeJoint``` array: ```CreatedJoint = new GameObject[typeJoint.Length]```. After that, we start to create their copies on the scene in the loop using the ```Instantiate``` function. Now, we define copies of the objects as children of the object that contains the script. As a result, the position of the parent object will correspond to the position of the sensor.

```cs
void Start()
{
    CreatedJoint = new GameObject[typeJoint.Length];
    for (int q = 0; q < typeJoint.Length; q++)
    {
        CreatedJoint[q] = Instantiate(PrefabJoint);
        CreatedJoint[q].transform.SetParent(transform);
    }
    message = "Skeleton created";
}
```

5.  Build the project (Ctrl + B) and check the app operation on your device. If everything is done correctly, the spheres from the prefab will be located in the position of the object with the script. Since they are yet located at one point, they will look like a single sphere.

<p align="center">
<img width="450" src="img/Ubasic_image8.png">
</p>

## Getting Data, Converting and Scaling the Joints

1.  As soon as we created the objects for visualization of the joints, let's match their positions with the positions of the joints of a real user's skeleton.

2.  Get data on the detected skeleton using ```CurrentUserTracker.CurrentSkeleton```. After this, we process the
information about the joints in the loop.

3.  To receive data on the required joint, call the ```GetJoint``` function from the obtained ```skeleton``` specifying the ```typeJoint[q]```.

4.  Let's calculate the joint position by calling the ```ToVector3()``` function from the current joint: ```Vector3 newPosition = 0.001f*joint.ToVector3()```. To learn more about Vectors in Unity, see the link at the end of this tutorial.

_**Note**: Keep in mind that 1 Unity unit is about 1 m, so we need to adjust the obtained data. To do that, multiply the received values by 0.001 (convert m to mm)._

5.  Set the calculated position ```newPosition``` to the ```CreatedJoint\[q\]``` object, which is matched with the ```typeJoint \[q\]:CreatedJoint\[q\].transform.localPosition = newPosition```.

```cs
void Update()
{
    if (CurrentUserTracker.CurrentUser != 0)
    {
        nuitrack.Skeleton skeleton = CurrentUserTracker.CurrentSkeleton;
        message = "Skeleton found";
        
        for (int q = 0; q < typeJoint.Length; q++)
        {
            nuitrack.Joint joint = skeleton.GetJoint(typeJoint[q]);
            Vector3 newPosition = 0.001f * joint.ToVector3();
            CreatedJoint[q].transform.localPosition = newPosition;
        }
    }
    else
    {
        message = "Skeleton not found";
    }
}
```

_**Note**: For correct detection of the user, the camera in Unity should be set at a distance of approximately 2-3 m from the object, which contains the script. Make sure the camera is facing the object._

6.  And now we are down to the final stretch! Build the project and run the app on your mobile device. Now, if everything was done properly, your skeleton will be detected, tracked and displayed in the app. Good job!

<p align="center">
<img width="450" src="img/Ubasic_image10.gif">
</p>

Now you know how to create a Unity project using Nuitrack SDK. From now on, you can develop a plenty of apps with skeleton tracking! That's all for now. Though this is a very simple example, it covers a large set of basic subjects important to understanding how to use Unity with Nuitrack SDK. In the next tutorials, you'll learn how create more complex and
functional Unity apps with skeleton tracking.

**Useful links:**

-   [Learn more about Prefabs](https://docs.unity3d.com/560/Documentation/Manual/Prefabs.html)
-   [Learn more about Vector3 struct](https://docs.unity3d.com/ScriptReference/Vector3.html)
-   [Information on Execution Order of Event Functions](https://docs.unity3d.com/Manual/ExecutionOrder.html)
