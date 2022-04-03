## Development

[TOC]

---

### NuitrackSDK

#### Users

`NuitrackManager.Users` - This is a class for accessing the data of detected users and user discovery and loss events.

| Properties | Access level | Value type |Description |
| ------------ | ------------ | ------------ | ------------ |
| MinID | get | `int` | Minimum allowed ID |
| MaxID | get | `int` | Maximum allowed ID |
| Count | get | `int` | The number of users detected at the moment |
| CurrentUserID | get | `int` | ID of the current user |
| Current | get | `UserData` | The controller user. Maybe null. The queue rule is in effect, the current user is considered the first to enter the frame. When the current user leaves the frame, control is transferred to the next detected one) |

| Events | Delegate type |Description |
| ------------ | ------------ | ------------ |
| OnUserEnter | `UserHandler(UserData user)` | Called when a new user has been recognized |
| OnUserExit | `UserHandler(UserData user)` | Called when the user has been lost |

| Methods | Return value | Description |
| ------------ | ------------ | ------------ |
| GetUser | `UserData` | Get a user by ID. Maybe null |
| GetList | `List<UserData>` | Get a list of all users |
| GetEnumerator | `Enumerator` | Get an Enumerator to enumerate via foreach, for example, `foreach (UserData user in NuitrackManager.Users) { ... }` |

#### UserData

Recognized user data:
  * Skeleton (`SkeletonData`)
    * Joint (`SkeletonData.Joint`)
  * LeftHand (`Hand`)
  * RightHand (`Hand`)
  * GestureType (`nuitrack.GestureType`)
  * Face (`nuitrack.Face`)

| Methods | Return value | Description |
| ------------ | ------------ | ------------ |
| BoundingBox | `Rect` | Get a BoundBox rectangle from a frame with the specified width and height |
| AnchoredRect | `Rect` | Get the Rect of the user relative to the parent Rect for the corresponding RectTransform taking into account the anchor |
| SegmentTexture | `Texture` | Get the Texture (Texture2D or RenderTexture - the fastest way for your platform will be selected) segment of this user |
| SegmentTexture2D | `Texture2D` | Get the Texture2D segment of this user |
| SegmentRenderTexture | `RenderTexture` | Get the RenderTexture segment of this user |

#### TrackedUser
A component that allows you to simply implement tracking of the current user or user with a given ID. You can inherit your own class from `TrackedUser` if you need a simple user data acquisition. Tracking options will be displayed in the inspector of your component.

| Properties | Access level | Value type |Description |
| ------------ | ------------ | ------------ | ------------ |
| UseCurrentUserTracker | get / set | `bool` | If True, the current user tracker is used, otherwise the user specified by ID is used |
| UserID | get / set | `bool` | ID of the current user For the case when current user tracker of is used, the ID of the active user will be returned If current user tracker is used and a new ID is set, tracking of the current user will stop |
| IsActive | get | `bool` | True if there is a control user |
| ControllerUser | get | `UserData` | The controller user. Maybe null |

#### NuitrackUtils  
In this namespace, the following extension methods are available to you for various Nuitrack data types:

| Methods | Type | Return value | Description |
| ------------ | ------------ | ------------ | ------------ |
| ToUnityBones | `JointType` | `HumanBodyBones` | Get the HumanBodyBones that matches the JointType |
| ToNuitrackJoint | `HumanBodyBones`  | `JointType` | Get the JointType that matches the HumanBodyBones |
| TryGetMirrored | `JointType`  | `JointType` | Get a symmetrical joint on the other side human (arms, legs). For joints that do not have a symmetrical pair, the  source value will be returned |
| GetParent | `JointType`  | `JointType` | Get a parent joint. For Waist, None will be returned |
| GetChilds | `JointType`  | `List<JointType>` | Get a list of child joints. The `recursive` parameter is responsible for whether the list will contain the nearest children or all in the hierarchy |
| GetNormalDirection | `JointType` | `Vector3` | Get the normal vector for the joint. This is usually a vector towards the child joint |
| ToVector3 | `nuitrack.Vector3` | `Vector3` | Convert raw vector nuitrack to Unity vector |
| ToVector3 | `nuitrack.Joint` | `Vector3` | Get the joint position as a Unity vector (value in millimeters) |
| ToQuaternion | `nuitrack.Joint` | `Quaternion` | Get the joint orientation as a Unity quaternion |
| ToQuaternionMirrored | `nuitrack.Joint` | `Quaternion` | Get the joint mirrored orientation as a Unity quaternion |

---

### NuitrackSDK.Frame

#### ToRenderTexture / ToTexture2D / ToTexture 

Extension methods for Nuitrack frame get the frames from the sensor in the form of Unity textures to display them or perform processing operations

| Type | Methods | Return value | Description |
| ------------ | ------------ | ------------ | ------------ |
| `nuitrack.ColorFrame` <br/>`nuitrack.DepthFrame`  <br/>`nuitrack.UserFrame` | ToRenderTexture | `RenderTexture` | Recommended method for platforms with ComputeShader support |
| `nuitrack.ColorFrame`  <br/>`nuitrack.DepthFrame`  <br/>`nuitrack.UserFrame` | ToTexture2D | `Texture2D` | For platforms with ComputeShader support, it may be slower than GetRenderTexture. If possible, use GetRenderTexture |
| `nuitrack.ColorFrame`  <br/>`nuitrack.DepthFrame`  <br/>`nuitrack.UserFrame` | ToTexture | `Texture` | The method will select the most productive way to get the texture. This can be either RenderTexture or Texture2D. Use this method if you don't care about the texture type |

**Examples**

**Color frame viewer**

Get a color frame and display it in the `RawImage` component.

```csharp
using UnityEngine;
using UnityEngine.UI;

using  NuitrackSDK.Frame;

public class SampleFrameViewer : MonoBehaviour
{
    [SerializeField] RawImage rawImage;

    void Update()
    {
        RenderTexture  rgbTexture = NuitrackManager.ColorFrame.ToRenderTexture();
        rawImage.texture = rgbTexture;
    }
}
```

**Depth frame viewer (with override default gradient)**

To protect against memory leaks when processing textures every frame, there is a `TextureCache` structure that stores the result of the transformation without creating a new texture. Create a `TextureCache` before using it, and then release with `Dispose`.

```csharp
using UnityEngine;
using UnityEngine.UI;

using  NuitrackSDK.Frame;

public class SampleFrameViewer : MonoBehaviour
{
    [SerializeField] RawImage rawImage;

    TextureCache depthCache = new TextureCache();

    Gradient depthGradient = new Gradient()
    {
        colorKeys = new GradientColorKey[]
        {
            new GradientColorKey(Color.white, 1),
            new GradientColorKey(Color.black, 0)
        }
    };

    void Update()
    {
        RenderTexture depthTexture = NuitrackManager.DepthFrame.ToRenderTexture(depthGradient, depthCache);
        rawImage.texture = depthTexture;
    }

    void OnDisable()
    {
        if (depthCache != null)
            depthCache.Dispose();
    }
}
```

#### FrameUtils

The component allows you to get extended access to Nuitrack frame processing functions, for example, to get the **vFOV** or **hFOV** of the depth sensor.

**Examples**

An example of leveling the field of view of a camera with a depth sensor. An example of aligning the field of view of a camera with a depth sensor, as well as the position of the cube to the maximum depth of the sensor (set manually on the `DepthToTexture` component, depending on the sensor used).

```csharp
camera.fieldOfView = FrameUtils.DepthToTexture.VFOV;
cube.transform.localPosition = Vector3.forward * FrameUtils.DepthToTexture.MaxSensorDepth;

Color userColor = FrameUtils.SegmentToTexture.GetColorByID(1);
```

#### TextureUtils

The component contains a set of methods for processing Unity textures. Operations on textures are performed on the **GPU**, which ensures high speed of operations. However, if you want to process the result in your own scripts on the **CPU**, you will need to transfer the texture from the **GPU** to the **CPU** using Copy methods.

| Methods | Type | Ref value (return) | Description |
| ------------ | ------------ | ------------ | ------------ |
| Cut | `Texture` <br/>`Texture` | `RenderTexture` | Cut images by the alpha channel of the mask by removing the background. A hard transition of the alpha channel is used (alpha > 0) |
| ReverseCut | `Texture` <br/>`Texture`  | `RenderTexture` | Cut the images by the alpha channel of the mask leaving the background. A hard transition of the alpha channel is used (alpha > 0) |
| Mul | `Texture` <br/>`Texture` | `RenderTexture` | Mix textures by multiplying them |
| MixMask | `Texture` <br/>`Texture` | `RenderTexture` |  Blend textures by mask by getting the average value. A hard transition of the alpha channel is used (alpha > 0) |
| Copy | `Texture2D` | `RenderTexture` | Copy Texture2D to RenderTexture |
| Copy | `RenderTexture` | `Texture2D` | Copy RenderTexture to Texture2D |

**Examples**

Example of a user cut from a color image by segment.

```csharp
RenderTexture renderTexture = null;

[SerializeField] RawImage rawImage;

void Update()
{
    RenderTexture  rgbTexture = NuitrackManager.ColorFrame.ToRenderTexture();
    RenderTexture  segmentTexture = NuitrackManager.UserFrame.ToRenderTexture();

    FrameUtils.TextureUtils.Cut(rgbTexture, segmentTexture, ref renderTexture);

    rawImage.texture = renderTexture;
}

```

---

### NuitrackSDK.Avatar

  * **BaseAvatar (abstract class)** - Base type providing simple functions for obtaining data about the skeleton. If you want to write your own Avatar controller, it is recommended to inherit all avatars from it. Inherits `TrackedUser`.
  
| Properties | Access level | Value type |Description |
| ------------ | ------------ | ------------ | ------------ |
| JointConfidence | get | `float` | Confidence threshold for detected joints |

| Methods | Return value | Description |
| ------------ | ------------ | ------------ |
| GetJoint(nuitrack.JointType jointType) | `UserData.SkeletonData.Joint` |Get a shell object for the specified joint |

Inherits **BaseAvatar**:
  * NuitrackAvatar
  * SkeletonAvatar
  * UIAvatar

---

### NuitrackSDK.Poses

#### NuitrackPose

Use poses in your scripts, for example, to check at a certain point in the game that the user used a defense or tilt pose.

| Methods | Args type | Ref value (return) | Description |
| ------------ | ------------ | ------------ | ------------ |
| NuitrackPose | `UserData.SkeletonData` | `NuitrackPose` | Create Pose from Skeleton reference |
| NuitrackPose | `NuitrackPose` | `NuitrackPose` | Create Pose from Pose reference |
| Match | `UserData.SkeletonData` | `float` | Match of the skeleton pose with the sample of pose |
| AbsoluteMatch | `UserData.SkeletonData` | `float` | Absolute match with the pose (the torso rotation is taken into account) |
| RelativeMatch | `UserData.SkeletonData` | `float` | Relative match with the pose (torso rotation is not taken into account) |

Get an instance of `PointReference` (class describing the joint pattern in the pose pattern.) using the indexer `[nuitrack.JointType]`.

#### PoseDetector

Manage poses during the game mode, create new poses, check the match of the custom pose with the sample.

| Properties | Access level | Value type |Description |
| ------------ | ------------ | ------------ | ------------ |
| CountPoses | get | `int` | Count of poses |
| Matches | get | `Dictionary<NuitrackPose, Dictionary<int, float>>` | Pose matches. The nested dictionary contains user IDs and the matching value. |

| Methods | Type | Return value | Description |
| ------------ | ------------ | ------------ | ------------ |
| AddPose | `UserData.SkeletonData` | `NuitrackPose` | Add a new pose |
| AddPose | `NuitrackPose` | `NuitrackPose` | Add a new pose |
| RemovePose | `NuitrackPose` | `bool` | Remove pose from PoseDetector. Return `true` - if the pose is removed from the PoseDetector, otherwise - `false` |
| AddListener | `NuitrackPose`  <br/>`UnityAction<NuitrackPose, int, float>` | `void` | Add a listener for a pose |
| RemoveListener | `NuitrackPose` <br/>`UnityAction<NuitrackPose, int, float>` | `void` | Remove a listener for a pose |

**Examples**

Example of adding a pose during play mode.

```csharp
using UnityEngine;
using UnityEngine.UI;

using NuitrackSDK;
using NuitrackSDK.Poses;

public class PoseExample : TrackedUser
{
    [SerializeField] PoseDetector poseDetector;
    [SerializeField] Slider poseMatch;

    NuitrackPose customPose = null;

    // Call from UI
    void SavePose()
    {
        if (ControllerUser != null && ControllerUser.Skeleton != null)
        {
            customPose = poseDetector.AddPose(ControllerUser.Skeleton, "New pose");
            poseDetector.AddListener(customPose, PoseDetectorProcess);
        }
    }

    public void PoseDetectorProcess(NuitrackPose pose, int userID, float match)
    {
        if (userID == UserID)
            poseMatch.value = match;
    }
}
```

