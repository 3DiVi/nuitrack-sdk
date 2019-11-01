Nuitrack OpenGL Sample

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

	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_gl_sample
	mkdir build
	cd build
	cmake ..
	make


Run sample:
	./nuitrack_gl_sample [path/to/nuitrack.config]


=============================================================
    Windows
=============================================================


- Install cmake https://cmake.org/download/

- Run CMake and set source code directory to "nuitrack_gl_sample" folder, build directory to "nuitrack_gl_sample/build"

- Press Configure button, then select Visual Studio generator

- Press Configure, then Generate

- Open solution "nuitrack_gl_sample.sln" in Visual Studio and use its instruments to build solution

