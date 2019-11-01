Simple skeleton console sample (writes the position of the right hand of the first found user in the console)

=============================================================
	Ubuntu
=============================================================

Dependencies:

	sudo apt-get install cmake

Build sample:

	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_console_sample
	mkdir build
	cd build
	cmake ..
	make


Run sample:
	./nuitrack_console_sample [path/to/nuitrack.config]


=============================================================
    Windows
=============================================================


- Install cmake https://cmake.org/download/

- Run CMake and set source code directory to "nuitrack_console_sample" folder, build directory to "nuitrack_console_sample/build"

- Press Configure button, then select Visual Studio generator

- Press Configure, then Generate

- Open solution "nuitrack_console_sample.sln" in Visual Studio and use its instruments to build solution

