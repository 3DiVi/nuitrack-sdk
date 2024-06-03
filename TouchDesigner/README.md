# TouchDesigner Plugin

Nuitrack integration for TouchDesigner!  
Get a lightweight skeleton with any depth sensor. 

## Supported platform
- Windows x64

## Supported sensors
- A full list of can be found on the [website](https://nuitrack.notion.site/87e45f2fb76c4456973f826dc1583ebc?v=c5bce550492145f4b4c7335f24f819fd).

## Licensing
- The plugin **only** works with an **Nuitrack AI Subscription**.  You could purchase it in your [licensing dashboard](https://cognitive.3divi.com/app/nuitrack/dashboard/) -> click **Choose a license**

## How to add the Nuitrack plugin to TouchDesigner
1. Download either the NuitrackTOP.dll or NuitrackCHOP.dll. Create a folder named NuitrackPlugin in `C:\Users\<user-name>\Documents\Derivative\Plugins\` and copy the downloaded dll file into this folder.   
  _If you don't have this directory, create it._  
  _If you faced any issues, create a topic at https://community.nuitrack.com/_. 

2. When you first start TD with a new plugin, you need to confirm its usage.  

3. If you are working on a new project, press tab (right mouse button -> Add Operator) ->custom -> select Nuitrack (CHOP is green, TOP is purple)   
   From CHOP operator you can get:
    - Skeleton Tracking - provides 19 joints.  
      Joints list: head* neck* torso* waist* collar* shoulder* elbow* wrist* hand* collar* hip* knee* ankle*   

   From TOP operator you can get:
    - Color, Depth, Point Cloud 

   _Note: At the moment, simultaneous operation of two plugins is not supported_  
   _The data provided is compatible with Touchdesigner nodes, such as math, threshold, transformation, etc._
4. See our Nuitrack_Sample.toe.
