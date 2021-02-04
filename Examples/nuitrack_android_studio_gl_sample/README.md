## Nuitrack OpenGL Android Studio Sample

### Requirements

* **Android Studio**: `v3.1.0` or higher

### IMPORTANT NOTES

1. We recommend you to use the latest **Android Studio** version.
2. If you are using one of the latest **Android Studio** versions (`v3.5+`), we strongly recommend you to set the **Gradle** and **Gradle Plugin** to a higher version before you open this project in **Android Studio**.
3. The **Gradle Plugin** version depends on your **Android Studio** version. The **Gradle Wrapper** version depends on your **Gradle Plugin** version. You can learn more about the **Gradle**/**Gradle Plugin** version dependency in the [official Android documentation](https://developer.android.com/studio/releases/gradle-plugin#updating-gradle).
4. If you want to change the **Gradle**/**Gradle Plugin** version:
   * Specify the new version of the **Gradle Plugin** in the variable `com.android.tools.build:gradle:3.2.0` in the `{ANDROID_STUDIO_SAMPLE_DIRECTORY}/build.gradle` file;
   * Specify the new **Gradle** version in the variable `distributionUrl=https\://services.gradle.org/distributions/gradle-4.6-bin.zip` in the `{ANDROID_STUDIO_SAMPLE_DIRECTORY}/gradle/wrapper/gradle-wrapper.properties` file.

## Building the Sample

1. Open **Android Studio**.
2. Click `Open an existing Android Studio project`.
3. Select the folder `<NuitrackSDK>/Examples/nuitrack_android_studio_gl_sample` and click `OK`.
4. Wait while **Android Studio** configures the project. You may be prompted to install **Android SDK**/**NDK** and **CMake** if they haven't been installed yet on your PC.
5. \[ optional \] If you see any errors during project configuration, for example: `A problem occurred configuring project ':app'.` or `NDK not configured. Install NDK and sync project` **PLEASE DO NOT PRESS ANY BUTTON!** These errors appear if you have an old **Gradle Plugin** and don't have the **NDK** installed (or **Android Studio** can't find it). Please follow the steps below:
   * Make sure that you're using correct **Gradle**/**Gradle Plugin** versions (see [Important Notes](#important-notes))
   * Set up the **NDK** location in `File` → `Project Structure` → `SDK location`→ `Android NDK location`.
6. Click the `Make project` button (a green hammer in the top right corner)  
   ***Note**: default target architecture is `armeabi-v7a`. If you want to change the architecture, you need to set the `abiFilters` value to `arm64-v8a` in `build.gradle`.*
7. Select your target Android device and click the `Run (app)` button.