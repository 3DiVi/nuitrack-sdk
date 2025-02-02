# Nuitrack OpenGL Sample

## Android
Please check [README.md](./android/README.md)

## Ubuntu
- Dependencies:
```bash
	sudo apt-get install freeglut3-dev
```
- Dependencies for Ubuntu 14.04:

```bash
	sudo apt-get install libgl1-mesa-dri
```

#### Build sample:

```bash
	cd <path_to_NuitrackSDK_folder>/Examples/nuitrack_gl_sample
	mkdir build
	cd build
	cmake ..
	make
```

#### Run sample:  
- ./nuitrack_gl_sample [path/to/nuitrack.config]

## Windows
- Install cmake https://cmake.org/download/
- Run CMake and set source code directory to "nuitrack_gl_sample" folder, build directory to "nuitrack_gl_sample/build"
  - Сmake will automatically download  freeglut for Visual Studio from https://www.transmissionzero.co.uk/software/freeglut-devel/ and unpack
- Press Configure button, then select Visual Studio generator, then Generate
- Open solution "nuitrack_gl_sample.sln" in Visual Studio 
- Use Visual Studio instruments to build solution
