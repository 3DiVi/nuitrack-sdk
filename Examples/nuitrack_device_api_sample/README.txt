Demonstrate NuitrackDevice API. Might be used for Nuitrack activation.

=============================================================
	Ubuntu
=============================================================

Dependencies:

	sudo apt-get install cmake

Build sample:

	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_device_api_sample
	mkdir build
	cd build
	cmake ..
	make


Run sample:
	./nuitrack_device_api_sample


=============================================================
    Windows
=============================================================


- Install cmake https://cmake.org/download/

- Run CMake and set source code directory to "nuitrack_device_api_sample" folder, build directory to "nuitrack_device_api_sample/build"

- Press Configure button, then select Visual Studio generator

- Press Configure, then Generate

- Open solution "nuitrack_device_api_sample.sln" in Visual Studio and use its instruments to build solution

