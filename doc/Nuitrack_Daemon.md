# Nuitrack Daemon [Beta]

Nuitrack Daemon is an application which allows you to get data from Nuitrack using REST api.

**_Note:_** _Nuitrack Daemon is currently in Beta so if you are experiencing difficulties using it or couldn't find some of the usual Nuitrack outputs or have suggestions, please write to us on support-nuitrack@3divi.com_

### Supported platforms
- Linux x64
- Windows x64

### Running Daemon
First, connect depth sensor to the machine from which you plan to launch Nuitrack Daemon.\
You can start Nuitrack Daemon application by:
- running `nuitrack_daemon` command  in your terminal on Linux system 
- executing `nuitrack_daemon.exe` from `C:\Program Files\Nuitrack\nuitrack\nuitrack\bin` folder on Windows system

Additionally you can specify port number by adding `-p [ --port ] <port>` argument.\
Press `Ctrl + C` to stop daemon gracefully.

### Getting data
- Send `GET` request on endpoint `<server-ip>:<server-port>/instances` to get JSON with information about users, their faces and detected objects.\
 More information about in the resulting JSON you can find in [Nuitrack Instance-based API [Beta]](Instance-based_API.md) and [Person Re-identification](Person_Reidentification.md) pages
- Nuitrack Daemon is also able to send POST callbacks to your server with information about user entering or leaving the space visible by the sensor.\
To configure endpoints that Nuitrack will call, send `POST` request on endpoint `<server-ip>:<server-port>/endpoints` with the following JSON (you can omit one of the endpoints if you want to):
    ```
    {
        "NewHumanEndpoint": "<your-server-ip>:<your-server-port>/onNewHuman",
        "LostHumanEndpoint": "<your-server-ip>:<your-server-port>/onLostHuman"
    }
    ``` 
    Or change `DaemonSettings.NewHumanEndpoint` and `DaemonSettings.LostHumanEndpoint` inside `nuitrack.config` file which is located in `$NUITRACK_HOME/data/` folder on Linux systems and `C:\Program Files\Nuitrack\nuitrack\nuitrack\data` folder on Windows systems

