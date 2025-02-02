cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME nuitrack_multisensor_sample)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

include(../cmake/DetectPlatform.cmake)
if(UNIX)
	# Default path for Nuitrack library installation: /usr/local/lib/nuitrack 
	set(OpenCV_LIBS /usr/local/lib/nuitrack/libopencv_core.so.3.4
					/usr/local/lib/nuitrack/libopencv_imgcodecs.so.3.4
					/usr/local/lib/nuitrack/libopencv_imgproc.so.3.4
					/usr/local/lib/nuitrack/libopencv_highgui.so.3.4)
	set(OpenCV_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include)
	file(ARCHIVE_EXTRACT
		INPUT ${CMAKE_CURRENT_LIST_DIR}/opencv_3.4_headers.zip
		DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/
	)
elseif(WIN32)
	find_package(OpenCV REQUIRED)
	link_directories(${OpenCV_LIB_DIR})
endif()

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include
	${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} nuitrack ${OpenCV_LIBS})
