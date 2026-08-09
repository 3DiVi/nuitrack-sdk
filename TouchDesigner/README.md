# TouchDesigner Plugin

Nuitrack integration for TouchDesigner!  
Get lightweight skeleton with any depth sensor. 

## Supported platform
- Windows x64

## Supported sensors
- A complete list of supported sensors can be found on the [website](https://nuitrack.notion.site/87e45f2fb76c4456973f826dc1583ebc?v=c5bce550492145f4b4c7335f24f819fd).

## Licensing
- The plugin **only** works with a **Nuitrack AI Creative** license. You could purchase one on the [Interactive Art page](https://nuitrack.com/interactive-art) → fill out the form at the bottom of the page

## How to add the Nuitrack plugin to TouchDesigner
1. Download either the NuitrackTOP.dll or NuitrackCHOP.dll.  
2. Create a folder named NuitrackPlugin in `C:\Users\<user-name>\Documents\Derivative\Plugins\` and copy the downloaded dll file into this folder.   
  _If you don't have this directory, create it._  
  _If you faced any issues, create a topic at our [Community Forum](https://community.nuitrack.com/)_. 

3. When you start TouchDesigner with a new plugin for the first time, you will need to confirm its usage.  

4. If you are working on a new project, press **Tab** (or right-click → "_Add Operator_") → custom → select Nuitrack (CHOP is green, TOP is purple)   
   From CHOP operator you can get:
    - Skeleton Tracking - provides 19 joints.  
      Joints list: head* neck* torso* waist* collar* shoulder* elbow* wrist* hand* collar* hip* knee* ankle*   

   From TOP operator you can get:
    - Color, Depth, Point Cloud 

   _The data provided is compatible with TouchDesigner nodes, such as math, threshold, transformation, etc._
5. See our [Examples](/TouchDesigner/Examples/)
