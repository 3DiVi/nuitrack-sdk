# Nuitrack Multi-Sensor sample
## Ubuntu
- Before build
  - Extract `opencv_3.4_header.zip` in `Nuitrack/include` 
	
- Build sample:

	```
	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_multisensor_sample
	mkdir build
	cd build
	cmake ..
	make
	```

- Run sample:
	- `./nuitrack_multisensor_sample`

## Windows
- Install cmake https://cmake.org/download/
- Download OpenCV and install from https://github.com/opencv/opencv/releases
- Run CMake and set a source code directory to `nuitrack_multisensor_sample` folder, build a directory to `nuitrack_multisensor_sample/build`
- Set OpenCV_DIR in CMake, for example `C:\opencv\build`
- Press Configure button, then select Visual Studio generator
- Press Configure, then Generate
- Open solution `nuitrack_multisensor_sample.sln` in Visual Studio 
- Use Visual Studio instruments to build solution
- Copy opencv_world*.dll in your build directory 
