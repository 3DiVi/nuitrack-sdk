Nuitrack OpenGL Sample with OpenNI-1.5 API

=============================================================
	Android
=============================================================

Please check ./android/README.txt


=============================================================
	Ubuntu
=============================================================

Dependencies:

	sudo apt-get install freeglut3-dev

Dependencies for Ubuntu 14.04:

	sudo apt-get install libgl1-mesa-dri

Build sample:

	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_ni_gl_sample
	mkdir build
	cd build
	cmake .. -DOPENNI_LIBRARY=/usr/local/lib/nuitrack/libOpenNI.so
	make


=============================================================
	Windows
=============================================================

- Install cmake https://cmake.org/download/

- Run CMake and set source code directory to "nuitrack_ni_gl_sample" folder, build directory to "nuitrack_ni_gl_sample/build"

- Press Configure button, then select Visual Studio generator

- Set OPENNI_LIBRARY value to OpenNI.lib or OpenNI64.lib file location (by default it's "C:/Program Files (x86)/OpenNI/Lib/openNI.lib" or "C:/Program Files/OpenNI/Lib64/openNI64.lib")

- Press Configure, then Generate

- Open solution "nuitrack_ni_gl_sample.sln" in Visual Studio and use its instruments to build solution
