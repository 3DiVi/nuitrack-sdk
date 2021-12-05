# PyNuitrack (beta)

PyNuitrack is a python wrapper for Nuitrack. You can this wrapper to detect skeletons and faces of users on frame. The Skeleton is represented as a set of joints, each of which has its position and orientation.

## PyNuitrack Installation

### Ubuntu Linux

1. Install Python 3.6 or newer:
   - for Ubuntu 14.04/16.04:
     ```
     sudo apt-get update
     sudo apt-get install -y software-properties-common
     sudo add-apt-repository ppa:deadsnakes/ppa
     sudo apt-get update
     sudo apt-get install -y python3.6
     ```
   - for Ubuntu 18.04/20.04:
     ```
     sudo apt-get update
     sudo apt-get install -y python3
     ```
2. Download and install Nuitrack follow the [instructions](/doc/Install.md#ubuntu-linux).
3. Activate Nuitrack with our [Trial, Perpetual, or Online license](https://nuitrack.com/#pricing).
4. Install numpy: `pip3 install numpy`.
5. Download [PyNuitrack package](/PythonNuitrack-beta/pip_packages/dist/linux).
6. Install package using pip (`pip3 install py_nuitrack.whl`)

**Note: If you have multiple python version, please install package using this command: `python_version -m pip install package_name` or use python venv.**

### Windows Installation

1. Download and install [Python for Windows 64.](https://www.python.org/downloads/)
2. Download and install nuitrack follow the [instructions](/doc/Install.md#windows).
3. Activate Nuitrack with our [Trial, Perpetual, or Online license](https://nuitrack.com/#pricing).
4. Install numpy: `pip install numpy`.
5. Download [PyNuitrack package](/PythonNuitrack-beta/pip_packages/dist/windows) depending on your python version.
6. Install package using pip (`pip install py_nuitrack.whl`).

**Note: If you have multiple python version, please install package using this command: `python_version -m pip install package_name` or use python venv.**

## PyNuitrack Usage

See example, covering all PyNuitrack features. Before run it, you need to install OpenCV: `pip3 install opencv-python`. 
Press space if you want to switch between color/depth mode:

<details>
<summary><b>Click to see code example</b></summary>

```py
from PyNuitrack import py_nuitrack
import cv2
from itertools import cycle
import numpy as np


def draw_face(image):
	if not data_instance:
		return
	for instance in data_instance["Instances"]:
		line_color = (59, 164, 225)
		text_color = (59, 255, 255)
		if 'face' in instance.keys():
			bbox = instance["face"]["rectangle"]
		else:
			return
		x1 = (round(bbox["left"]), round(bbox["top"]))
		x2 = (round(bbox["left"]) + round(bbox["width"]), round(bbox["top"]))
		x3 = (round(bbox["left"]), round(bbox["top"]) + round(bbox["height"]))
		x4 = (round(bbox["left"]) + round(bbox["width"]), round(bbox["top"]) + round(bbox["height"]))
		cv2.line(image, x1, x2, line_color, 3)
		cv2.line(image, x1, x3, line_color, 3)
		cv2.line(image, x2, x4, line_color, 3)
		cv2.line(image, x3, x4, line_color, 3)
		cv2.putText(image, "User {}".format(instance["id"]), 
		x1, cv2.FONT_HERSHEY_SIMPLEX, 1, text_color, 2, cv2.LINE_AA)
		cv2.putText(image, "{} {}".format(instance["face"]["gender"],int(instance["face"]["age"]["years"])), 
		x3, cv2.FONT_HERSHEY_SIMPLEX, 1, text_color, 2, cv2.LINE_AA)

def draw_skeleton(image):
	point_color = (59, 164, 0)
	for skel in data.skeletons:
		for el in skel[1:]:
			x = (round(el.projection[0]), round(el.projection[1]))
			cv2.circle(image, x, 8, point_color, -1)

nuitrack = py_nuitrack.Nuitrack()
nuitrack.init()

# ---enable if you want to use face tracking---
# nuitrack.set_config_value("Faces.ToUse", "true")
# nuitrack.set_config_value("DepthProvider.Depth2ColorRegistration", "true")

devices = nuitrack.get_device_list()
for i, dev in enumerate(devices):
	print(dev.get_name(), dev.get_serial_number())
	if i == 0:
		#dev.activate("ACTIVATION_KEY") #you can activate device using python api
		print(dev.get_activation())
		nuitrack.set_device(dev)


print(nuitrack.get_version())
print(nuitrack.get_license())

nuitrack.create_modules()
nuitrack.run()

modes = cycle(["depth", "color"])
mode = next(modes)
while 1:
	key = cv2.waitKey(1)
	nuitrack.update()
	data = nuitrack.get_skeleton()
	data_instance=nuitrack.get_instance()
	img_depth = nuitrack.get_depth_data()
	if img_depth.size:
		cv2.normalize(img_depth, img_depth, 0, 255, cv2.NORM_MINMAX)
		img_depth = np.array(cv2.cvtColor(img_depth,cv2.COLOR_GRAY2RGB), dtype=np.uint8)
		img_color = nuitrack.get_color_data()
		draw_skeleton(img_depth)
		draw_skeleton(img_color)
		draw_face(img_depth)
		draw_face(img_color)
		if key == 32:
			mode = next(modes)
		if mode == "depth":
			cv2.imshow('Image', img_depth)
		if mode == "color":
			if img_color.size:
				cv2.imshow('Image', img_color)
	if key == 27:
		break

nuitrack.release()

```

</details>

1. Create object nuitrack by runnnig `nuitrack = py_nuitrack.Nuitrack()`
2. It's necessary to init Nuitrack with command `nuitrack.init()`. 
3. You can enable face tracking by calling this metonds:
    ```py
        nuitrack.set_config_value("Faces.ToUse", "true")
        nuitrack.set_config_value("DepthProvider.Depth2ColorRegistration", "true")
    ```
4. You can iterate all your connected devices and choose wich one you want to use by calling `nuitrack.set_device(dev)`.
5. Create models with `nuitrack.create_modules()`.
6. Run `nuitrack.run()`.
7. In a loop call `nuitrack.update()` first, after that you can get `depth image`,`color image` , `skeletons` and `instances`.
8. At the end call `nuitrack.release()`.

### GET_SKELETON

This method returns data which contains the following fields:
- timestamp - frame timestamp in microseconds
- skeletons_num - number of skeletons detected on frame
- skeletons - list of skeletons on frame

You can retrieve skeleton joint and user id by loop through data.skeletons:

```py
for skeleton in data.skeletons:
    print(skeleton.user_id)
    print(skeleton.left_hand)
    print(skeleton.right_hand.projection)
```

Using `skeleton` you can also get access to other joints of the skeleton:
<details>
<summary>Click to see joints</summary>

```
head
neck
torso
waist
left_collar
left_shoulder
left_elbow
left_wrist
left_hand
right_collar
right_shoulder
right_elbow
right_wrist
right_hand
left_hip
left_knee
left_ankle
right_hip
right_knee
right_ankle
```
</details>

Each `joint field` has:

```
type
confidence
real
projection
orientation
```

### GET_INSTANCE

This method return dictionary which сontains information about faces of users with detected skeletons. You can convert it to JSON data.
Here is an example of JSON output.

<details>

<summary>JSON example of detected face</summary>

```
{
   "Timestamp":1636619547706618,
   "Instances":[
      {
         "id":1,
         "class":"human",
         "face":{
            "rectangle":{
               "left":220.0,
               "top":55.0,
               "width":194.0,
               "height":194.0
            },
            "landmark":[
               {
                  "x":0.42078638076782227,
                  "y":0.274656742811203
               },
               {
                  "x":0.4336216449737549,
                  "y":0.25765836238861084
               },
               {
                  "x":0.45662862062454224,
                  "y":0.25839850306510925
               },
              ...
            ],
            "left_eye":{
               "x":0.45123791694641113,
               "y":0.2969283163547516
            },
            "right_eye":{
               "x":0.5217143297195435,
               "y":0.26434293389320374
            },
            "angles":{
               "yaw":-22.729164123535156,
               "pitch":-7.3662333488464355,
               "roll":-20.351110458374023
            },
            "emotions":{
               "angry":0.3902933895587921,
               "neutral":0.46033039689064026,
               "surprise":0.13632416725158691,
               "happy":0.013052115216851234
            },
            "age":{
               "type":"kid",
               "years":14.538444519042969
            },
            "gender":"female",
            "quality":-1081.7933349609375,
            "recognizer":{
               "angry":-1
            }
         }
      }
   ]
}
```

</details>


You can read more about Faces Instances [here](https://github.com/3DiVi/nuitrack-sdk/blob/master/doc/Instance-based_API.md#getting-information-about-instances).

