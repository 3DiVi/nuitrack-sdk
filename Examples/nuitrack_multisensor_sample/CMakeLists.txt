cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME nuitrack_multisensor_sample)
project(${PROJECT_NAME})

add_definitions(-std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0)

set(NUITRACK_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)

if(UNIX)
	IF (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
		set(PLATFORM_DIR linux_arm)
	ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch")
		set(PLATFORM_DIR linux_arm64)
	ELSEIF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64")
		set(PLATFORM_DIR linux64)
	ENDIF()
	
	set(OpenCV_LIBS $ENV{LD_LIBRARY_PATH}/libopencv_core.so.3.4
					$ENV{LD_LIBRARY_PATH}/libopencv_imgcodecs.so.3.4
					$ENV{LD_LIBRARY_PATH}/libopencv_imgproc.so.3.4
					$ENV{LD_LIBRARY_PATH}/libopencv_highgui.so.3.4)
	set(OpenCV_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include)
elseif(WIN32)
	IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(PLATFORM_DIR win32)
	ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(PLATFORM_DIR win64)
	ENDIF()
	find_package(OpenCV REQUIRED)
	link_directories(${OpenCV_LIB_DIR})
endif()

set(NUITRACK_LIBRARY_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR}) 

include_directories(
	.
	${NUITRACK_INCLUDE_PATH}
)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${NUITRACK_LIBRARY_PATH})

set(SOURCES
    src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS  nuitrack ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
