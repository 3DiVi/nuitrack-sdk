Demonstrate NuitrackDevice API. Might be used for Nuitrack activation.

=============================================================
	Ubuntu
=============================================================

Dependencies:

	sudo apt-get install mono-utils monodevelop

Build sample:

	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_csharp_device_api_sample
	mkdir build
	cd build
	cmake ..
	make install

Run sample:
	cd ..
	chmod +x nuitrack_csharp_device_api_sample.exe
	./nuitrack_csharp_device_api_sample.exe


=============================================================
    Windows
=============================================================


- Install cmake https://cmake.org/download/

- Run CMake and set source code directory to "nuitrack_csharp_device_api_sample" folder, build directory to "nuitrack_csharp_device_api_sample/build"

- Press Configure button, then select Visual Studio generator

- Press Configure, then Generate

- Open solution "Project.sln" in Visual Studio and use its instruments to build solution

- copy .exe binary from "build" directory to its parent folder (or build target INSTALL) and run sample from "nuitrack_csharp_device_api_sample" directory

