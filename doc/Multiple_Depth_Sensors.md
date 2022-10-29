# Using Nuitrack with Multiple Depth Sensors

Nuitrack now could process data from multiple depth sensors simultaneously.  
This opens up a wide range of opportunities for room-space tracking, 360-degrees tracking without blind spots, etc.

Here are the few important things to know for getting started:
1. Licensing:
   * This feature works with **Perpetual** and **Trial** licenses.
   * Licensing works the same as with a single sensor, i.e. you need to have a separate license for each sensor. This is not applicable for a trial license.
2. Recommended sensors: Kinect v2, Orbbec Astra+, Orbbec Astra PRO+, Intel RealSense. For more details, visit [nuitrack.com](https://nuitrack.com/#sensors).
3. Supported platforms: desktop platforms (Windows x64/x86 or Linux x64). If you use [AI Skeleton Tracking](Nuitrack_AI.md#nuitrack-ai-skeleton-tracking) with a multi-sensor, you need to have 3-4 CPU cores for each sensor.
4. To test your multisensor setup, run `nuitrack_multicam_sample` from the command line.
5. To learn how to use Nuitrack with multiple depth sensors, see our [nuitrack_multisensor_sample](/Examples/nuitrack_multisensor_sample/).

<p align="center"><a href="https://nuitrack.com/"><img width="480" src="img/multisensore.gif"></a></p>

To start using Nuitrack with multiple depth sensors, follow the steps below.

1. After you initialized Nuitrack, get a list of available sensors via `Nuitrack::getDeviceList()`
2. Use `Nuitrack::setDevice(NuitrackDevice::Ptr device)` function every time before you create any Nuitrack related instances (`DepthSensor`, `SkeletonTracker`, etc.) to associate them with the sensor of your choice.

For example:

```
Nuitrack::init();

DepthSensor::Ptr depthSensor = DepthSensor::create();
depthSensor->connectOnNewFrame(depthCallback);

ColorSensor::Ptr colorSensor = ColorSensor::create();
colorSensor->connectOnNewFrame(colorCallback);

SkeletonTracker::Ptr skeletonTracker = SkeletonTracker::create();
skeletonTracker->connectOnUpdate(skeletonUpdateCallback);

Nuitrack::run();

while(true)
{
    Nuitrack::waitUpdate(skeletonTracker);
}
Nuitrack::release();
```

You should change the code above to:

```
Nuitrack::init();

// get all connected sensor
auto devices = Nuitrack::getDeviceList();

// creating vectors in which we will save the created modules
std::vector<DepthSensor::Ptr> depthSensorVec;
std::vector<ColorSensor::Ptr> colorSensorVec;
std::vector<SkeletonTracker::Ptr> skeletonTrackerVec;

for (int i = 0; i < devices.size(); i++)
{
    // set device and create the necessary modules and save them in a vector
    Nuitrack::setDevice(devices[i]);
    depthSensorVec.push_back(DepthSensor::create());
    colorSensorVec.push_back(ColorSensor::create());
    skeletonTrackerVec.push_back(SkeletonTracker::create());

    // connect the created modules to the callback
    depthSensorVec[i]->connectOnNewFrame(depthCallback);
    colorSensorVec[i]->connectOnNewFrame(colorCallback);
    skeletonTrackerVec[i]->connectOnUpdate(skeletonCallback);
}

Nuitrack::run();

while(true)
{
    // wait and update Nuitrack data for one type created modules, for example Skeleton Tracker
    for(const auto& skel : skeletonTrackerVec)
    {
        Nuitrack::waitUpdate(skel);
    }
}
Nuitrack::release();
```  
