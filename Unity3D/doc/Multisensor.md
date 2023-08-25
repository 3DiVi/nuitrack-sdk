# Multisensor

To enable `Multisensor` feature, add the `NuitrackScripts` prefab to the scene (this can be done using the `Nuitrack/Prepare The Scene` menu item) and switch `Multisensor Type -> Multisensor` on `Nuitrack Manager` component.
In this case, it becomes possible to work with several sensors on the same scene. (sensor data is not merged)

To receive data from Nuitrack modules, you need to specify the id of the sensor you want to work with (id is the number of the required sensor in the list of connected sensors(0, 1, 2...).
You can get device list using `nuitrack.Nuitrack.GetDeviceList()` or view it using `NuitrackActivationTool`)

### Data:  
[NuitrackManager.SensorsData[sensorId]] - Getting ColorFrame, DepthFrame, etc from a specific sensor

`GetSensorIdBySerialNumber("Sensor Serial Number", out sensorId)` - The sensor id may change, so if you need to guarantee that a specific sensor will be used in your script, you can get its current id using the serial number. 

You can get acquainted with this feature on the scene `NuitrackSDK/Nuitrack Demos/Multisensor/Multisensor`

# Example:
Let's output an images from several sensors
1. Connect sensors. Launch Unity. Open a new scene. Select `Nuitrack/Prepare The Scene` from the menu
2. Create a `Canvas` and add few `Raw Images` (then an image from a separate sensor will be output to each `Raw Image`)
3. Create a `ShowColorImage` script:

```
using UnityEngine;
using UnityEngine.UI;
using NuitrackSDK.Frame;

public class ShowColorImage : MonoBehaviour
{
    public string sensorSerialNumber;
    TextureCache cache;

    void Awake()
    {
        cache = new TextureCache();
    }

    private void Update()
    {
        int sensorId = -1;
        
        if (NuitrackManager.Instance.GetSensorIdBySerialNumber(sensorSerialNumber, out sensorId))
        {
            nuitrack.ColorFrame frame = NuitrackManager.sensorsData[sensorId].ColorFrame;

            if (frame != null)
                GetComponent<RawImage>().texture = frame.ToTexture2D(cache);
        }
        else
        {
            Debug.LogError("Device not found. SN:" + sensorSerialNumber);
        }
    }
}
```


4. Add this component to all `Raw Images` on scene. In the `Sensor Serial Number` field, specify the sensor serial number from which you want to receive data
5. On the `NuitrackManager` component select `Multisensor` value in the `Multisensor Type` field
6. Play the scene. (If sensors are connected but there is no image, try restarting Unity)
