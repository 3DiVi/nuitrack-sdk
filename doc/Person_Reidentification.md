# Person Re-identification

Nuitrack is now able to recognize the same users if they left the frame and returned back in a single runtime session.

**_Disclaimer:_**  
_For this feature to work Nuitrack SDK uses facial / body features to be able to recognize person on reappearance._  
_This data is processed in RAM only through a single runtime session and isn't kept / stored / transmitted anyhow anywhere._  

### Supported platforms
- Linux x64
- Windows x64/x86

### Try out Re-identification feature

To try the person re-identification:
- launch the Nuitrack application 
- make sure that the `Reidentification` checkbox is checked 
- start visualization via `Try Nuitrack!` button

You will see unique person identifier next to person skeleton, as well as time of first appearance and number of seconds spent in a frame.

<p align="center"><a href="https://nuitrack.com/"><img src="img/reid.gif" width="70%" /></a></p>

### Getting Re-identification data using SDK

Follow these steps to get Re-identification data from Nuitrack.
1. Enable Re-identification feature after initializing Nuitrack:
    <details open><summary>C++</summary>
    
    ```cpp
    #include <nuitrack/Nuitrack.h>
    using namespace tdv::nuitrack;
    ...

    Nuitrack::init();
    Nuitrack::setConfigValue("Reidentification.ToUse", "true");
    ```
    
    </details>

    <details><summary>C#</summary>
    
    ```cs
    using nuitrack;
    ...

    Nuitrack.Init("");
    Nuitrack.SetConfigValue("Reidentification.ToUse", "true");
    ```
    
    </details>
2. Create `SkeletonTracker` module, connect it to the callback function and start Nuitrack:
    <details open><summary>C++</summary>
    
    ```cpp
    void onSkeletonUpdate(SkeletonData::Ptr userSkeletons) { /* your SkeletonData processing */ }

    ...

    auto skeletonTracker = SkeletonTracker::create();
    skeletonTracker->connectOnUpdate(onSkeletonUpdate);
    Nuitrack::run();
    ```
    
    </details>

    <details><summary>C#</summary>
    
    ```cs
    void onSkeletonUpdate(SkeletonData skeletonData) { /* your SkeletonData processing */ }
    
    ...
    
    SkeletonTracker skeletonTracker = SkeletonTracker.Create();
    skeletonTracker.OnSkeletonUpdateEvent += onSkeletonUpdate;
    Nuitrack.Run();
    ```
    
    </details>
3. After you run Nuitrack you can start getting it's data in JSON format like this:
    <details open><summary>C++</summary>
    
    ```cpp
    while (true)
    {
        Nuitrack::waitUpdate(skeletonTracker);
        auto jsonData = Nuitrack::getInstancesJson();
    }
    ```
    
    </details>

    <details><summary>C#</summary>
    
    ```cs
    while (true)
    {
        Nuitrack.Update(skeletonTracker);
        string json = Nuitrack.GetInstancesJson();
    }
    ```
    
    </details>
    
    Example of JSON file:
    ```json
    {
        "Timestamp": "1659084464875886",
        "Instances": [
            {
                "id": "1",
                "class": "human",
                "uuid": "2a6de0bd-5ed8-4b57-aedb-f38135f87c14"
            }
        ]
    }
    ```
    **_Note:_** 
      - _**id** is a unique identifier of a person until he leaves the frame. After re-entering the frame, a new ID is assigned. Corresponds to a person ID contained in data received from other Nuitrack modules. This is necessary, for example, so that you can link a person skeleton and its long-term unique identifier._  
      - _**uuid** is a long-term unique identifier provided by the reidentification function. This ID will remain the same even if you leave the frame and come back again. But be careful to get it for the first time and restore it after re-entry, you need to turn your face towards the camera once._  
  
4. Before exiting your program don't forget to release Nuitrack:
    <details open><summary>C++</summary>
    
    ```cpp
    Nuitrack::release();
    ```
    
    </details>

    <details><summary>C#</summary>
    
    ```cs
    skeletonTracker.OnSkeletonUpdateEvent -= onSkeletonUpdate;

    Nuitrack.Release();
    ```
    
    </details>
