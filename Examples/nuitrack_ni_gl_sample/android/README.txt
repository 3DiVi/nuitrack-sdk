Nuitrack GL Sample NI.


ANDROID BUILD.

Dependencies:
	- Android SDK
	- Android NDK >= v. r9d

Android (build command line):
	- cd android/
	- android update project -n NuitrackGLSampleNI -t <target> -p .
			where <target> is target Id from "android list targets" which have API level greater than 14
	- cd jni/
	- ndk-build
	- cd ../
	- ant debug
	- adb install -r bin/NuitrackGLSampleNI-debug.apk
