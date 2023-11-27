# Nuitrack Daemon [Beta]

Nuitrack Daemon is an prebuilt executable which provides REST API access to Nuitrack.  
You could think of it as _Nuitrack-as-a-service_.

**_Note:_** Nuitrack Daemon is currently in Beta so if you have any issues or suggestions - please feel free to create a post at our [Community Forum](https://community.nuitrack.com) .

### Supported platforms
- Windows x64
- Linux x64

## Launching Daemon
First, connect depth sensor to the host with a Nuitrack Daemon installed.  
You can start Nuitrack Daemon application by:
- executing `nuitrack_daemon` command  in your terminal on Linux system 
- launching `nuitrack_daemon.exe` from `C:\Program Files\Nuitrack\nuitrack\nuitrack\bin` folder on Windows system

Additionally you can specify port number by adding `-p [ --port ] <port>` argument.\
Press `Ctrl + C` to stop daemon gracefully.

### Running Daemon with Multiple Depth Sensors
To enable Multi-Sensor capabilities run daemon with `--multiSensor` argument.

## Getting Current Data 
To obtain current tracking results:
|| Single-Sensor Daemon | Multi-Sensor Daemon |
|--------| ------ | ------ |
| Data Request | `GET localhost:8080/instances`  | `GET localhost:8080/skeletons` |
| Daemon Response | JSON with information about users, their faces and detected objects. See [Nuitrack Instance-based API [Beta]](Instance-based_API.md) and [Person Re-identification](Person_Reidentification.md) pages | JSON with the current evaluation of skeletons in the space covered by your Multi-Sensor setup |

## Receiving Callbacks
The Nuitrack Daemon can send sparse event callbacks back to your server:
|| Single-Sensor Daemon | Multi-Sensor Daemon |
|--------| ------ | ------ |
| User entering/exiting area | Daemon will send `POST` request to your server with User's ID | Daemon will send `POST` request to your server with information about User's ID, UUID and the coordinates of the space from where the User entered/exited |
| User entering area of observation | Daemon will send `POST` request to your server with `ID` of the User who entered the sensor's observation area  | Daemon will send `POST` request to your server with information about User's `ID` and the `coordinates` of the space where the User entered the space covered by your Multi-Sensor setup |
| User leaving area of observation | Daemon will send `POST` request to your server with `ID` of the User who left the sensor's observation area | Daemon will send `POST` request to your server with information about User's `ID`, `UUID` and the `coordinates` of the space where the User left the space covered by your Multi-Sensor setup |
| User Re-Identification | --- | When the user turns to one of the sensors at a right angle, Nuitrack can [re-identify](Person_Reidentification.md) the same users of the space. On such event Daemon will send `POST` request on your server with User `ID` and the `UUID` assigned to that User, which will stay the same during Daemon execution. This type of event is sent to the same endpoint as User entering area event |

### Setting up Callbacks
Using the Daemon's API, you can configure the endpoints to which the Daemon will send callbacks.

To do that send `POST localhost:8080/endpoints` request with the following body:
```
{
    "NewHumanEndpoint": "<your-server-ip>:<your-server-port>/<endpoint-for-user-entering>",
    "LostHumanEndpoint": "<your-server-ip>:<your-server-port>/<endpoint-for-user-leaving>"
}

```

### Example of using Multi-Sensor Daemon Callbacks

1. Set up callback endpoints to which the daemon will send events:
```
POST localhost:8080/endpoints

{
    "NewHumanEndpoint": "localhost:8081/onNewHuman",
    "LostHumanEndpoint": "localhost:8081/onLostHuman"
}
```

2. User enters the space and Nuitrack Daemon sends you `POST` request on `localhost:8081/onNewHuman`
with:

```
{
    "type": "SpaceInteraction",
    "id": "0",
    "uuid": "",
    "x": "1073",
    "z": "382"
}

```

Meaning that User with ID: 0, has entered space at (1073, 382) and has not been Re-identified yet.

3. User turns to face the sensor and Nuitrack Daemon sends you another `POST` request on `localhost:8081/onNewHuman` with:
```
{
    "type": "UUIDAssignment",
    "id": "0",
    "uuid": "fdf1387f-880b-4c29-b787-f9c85a95cca2"
}

```
Meaning that User with ID: 0 has been Re-identified and was assigned to UUID: `fdf1387f-880b-4c29-b787-f9c85a95cca2`. This UUID, unlike the ID, will be bound to the same user during Daemon execution.

4. User leaves the space and Nuitrack Daemon sends you `POST` request on `localhost:8081/onLostHuman` with:
```
{
    "type": "SpaceInteraction",
    "id": "0",
    "uuid": "fdf1387f-880b-4c29-b787-f9c85a95cca2",
    "x": "183",
    "z": "750"
}

```
Meaning that User with ID: 0 and UUID: `fdf1387f-880b-4c29-b787-f9c85a95cca2` has left space at (183, 750).

### Daemon's Error Reporting Capabilities
Daemon can record the most recent 15 seconds of sensor data to facilitate resolution of any issues with tracking results.  
To use this feature, add `--dump` option to Daemon's startup command, reproduce your issue, send `POST localhost:8080/dump` request to the Daemon and wait until Daemon finish recording.  
Compress recorded data (by default it's located at `%NUITRACK_HOME%\data\NuitrackFrameDump\<your recording>`) and send it to us at support-nuitrack@3divi.com
