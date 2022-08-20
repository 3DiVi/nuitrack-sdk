# Person Re-identification

Nuitrack is now able to recognize the same users if they left the frame and returned back in a single runtime session.

**_Disclaimer:_**  
_For this feature to work Nuitrack SDK uses facial/body features to be able to recognize person on reappearance._  
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
    ```cpp
    Nuitrack::init();
    Nuitrack::setConfigValue("Reidentification.ToUse", "true");
    ```
2. Create `SkeletonTracker` module, connect it to the callback function and start Nuitrack:
    ```cpp
    void onSkeletonUpdate(SkeletonData::Ptr userSkeletons) { /* your SkeletonData processing */ }

    ...

    auto skeletonTracker = SkeletonTracker::create();
    skeletonTracker->connectOnUpdate(onSkeletonUpdate);
    Nuitrack::run();
    ```
3. After you run Nuitrack you can start getting it's data in JSON format like this:
    ```cpp
    while (true)
    {
        Nuitrack::waitUpdate(skeletonTracker);
        auto jsonData = Nuitrack::getInstancesJson();
    }
    ```
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
      - _**id** from the JSON above matches with id provided by `UserTracker` and `SkeletonTracker`_  
      - _**uuid** is a unique user identifier_  
  
4. Before exiting your program don't forget to release Nuitrack:
    ```cpp
    Nuitrack::release();
    ```
