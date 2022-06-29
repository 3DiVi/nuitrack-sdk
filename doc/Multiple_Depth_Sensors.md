# Using Nuitrack with Multiple Depth Sensors

To test your Multiple Depth Sensors setup you can run `nuitrack_multicam_sample` from the command line

Please follow the steps below to start using Nuitrack with multiple Depth Sensors.

1. After you initialized Nuitrack, get list of available sensors via `Nuitrack::getDeviceList()`
2. Use `Nuitrack::setDevice(NuitrackDevice::Ptr device)` function every time before you create any Nuitrack related instances (`DepthSensor`, `SkeletonTracker`, etc.) to assotiate them with the sensor of your choice.

For example if you had code like below:
```
Nuitrack::init();

DepthSensor::Ptr depthSensor = DepthSensor::create();
depthSensor->connectOnNewFrame(depthCallback);

Nuitrack::run();
```
You should change it to:
```
Nuitrack::init();

auto availableSensors = Nuitrack::getDeviceList();

Nuitrack::setDevice(availableSensors[0]);
DepthSensor::Ptr depthSensor = DepthSensor::create();
depthSensor->connectOnNewFrame(depthCallback);

// If you want to run more sensors, set another sensor here and create Nuitrack instances you need as shown above

Nuitrack::run();
```  

### Troubleshooting
__Q:__ I don't see outputs from one or more sensors
<br />__A:__ Multiple Depth Sensors setups require more attention to the bandwidth of your computer's USB ports. In case your program doesn't provide output from one or more depth sensors try to reconnect sensors to different USB ports.
To test your Multiple Depth Sensors setup you can run `nuitrack_multicam_sample` from the command line
