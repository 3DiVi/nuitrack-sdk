cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME nuitrack_ni_gl_sample)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

# Add definitions for OpenNI with C++11
include(../cmake/DetectPlatform.cmake)
detect_platform_arch(PLATFORM_DIR)

SET(OPENNI_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/OpenNI/Include" CACHE PATH "Location of OpenNI include directory")
SET(OPENNI_LIBRARY "" CACHE FILEPATH "Path to OpenNI dynamic library")

if(UNIX)
	set(OPENGL_LIBS glut GL)
elseif(WIN32)
	set(OPENGL_LIBS glut32 glu32 opengl32)
endif()

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include
	${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware
	${OPENNI_INCLUDE_PATH}
)

link_directories(${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR})

add_executable(${PROJECT_NAME} src/NiGLSample.cpp src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBS} nuitrack ${OPENNI_LIBRARY})
