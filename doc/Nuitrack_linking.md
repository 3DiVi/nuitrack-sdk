# Linking Nuitrack to your application (Windows/Linux)

Please follow the steps below to link Nuitrack to your application. 

1. Copy the following directories from the Nuitrack installation folder to an application directory `<app_dir>`:
   * Windows
     * `%NUITRACK_HOME%\nuitrack\nuitrack\bin`
     * `%NUITRACK_HOME%\nuitrack\nuitrack\data`
     * `%NUITRACK_HOME%\nuitrack\nuitrack\middleware`
   * Linux
     * `/usr/etc/nuitrack/data`
     * `/usr/etc/nuitrack/middleware`
     * `/usr/local/lib/nuitrack`
1. Edit the configuration file `nuitrack.config`:
   * add the parameter `"ConfigurationDirectory": "<app_dir>/data"`
   * set the parameter `"LicenseFile": "<app_dir>/data/license.json"`
   * set the parameter `"DynamicModules.Path"` to `<app_dir>/middleware`
1. In the source code of your application, use the Nuitrack initialization function and specify the path to the `nuitrack.config` file: 
   * С++ `Nuitrack::init("<app_dir>/data/nuitrack.config");`
   * C# `Nuitrack.Init("<app_dir>/data/nuitrack.config");`