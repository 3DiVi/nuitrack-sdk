Nuitrack GL Sample.


ANDROID BUILD.

Dependencies:
	- Android SDK
	- Android NDK >= v. r9d

Android (build command line):
	- cd android/
	- android update project -n NuitrackGLSample -t <target> -p .
			where <target> is target Id from "android list targets" which have API level greater than 14
	- cd arm64-v8a/jni (armeabi-v7a/jni for 32-bit ARM-based CPUs)
	- ndk-build
	- cd ../../
	- ant debug
	- adb install -r bin/NuitrackGLSample-debug.apk