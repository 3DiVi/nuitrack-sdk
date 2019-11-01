cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME nuitrack_ni_gl_sample)
project(${PROJECT_NAME})

add_definitions(-std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0)

# Add definitions for OpenNI with C++11
if(UNIX)
	IF(CMAKE_SYSTEM_PROCESSOR MATCHES "^i.86$")
		add_definitions(-Dlinux -Di386)
	ELSEIF (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64")
		add_definitions(-Dlinux -D__x86_64__)
	ELSEIF (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
		add_definitions(-Dlinux -D__arm__)
	ELSE()
		add_definitions(-Dlinux)
	ENDIF()
endif()

set(NUITRACK_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)

SET(OPENNI_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/OpenNI/Include" CACHE PATH "Location of OpenNI include directory")
SET(OPENNI_LIBRARY "" CACHE FILEPATH "Path to OpenNI dynamic library")

if(UNIX)
	set(OPENGL_LIBS glut GL)
	IF (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
		set(PLATFORM_DIR linux_arm)
	ELSEIF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64")
		set(PLATFORM_DIR linux64)
	ENDIF()
elseif(WIN32)
	IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(PLATFORM_DIR win32)
	ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(PLATFORM_DIR win64)
	ENDIF()
	set(OPENGL_LIBS glut32 glu32 opengl32)
endif()

set(NUITRACK_LIBRARY_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR}) 

include_directories(
	.
	${NUITRACK_INCLUDE_PATH}
	${OPENNI_INCLUDE_PATH}
)

link_directories(${NUITRACK_LIBRARY_PATH})

set(SOURCES
    src/NiGLSample.cpp
    src/main.cpp)
    
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS ${OPENGL_LIBS} nuitrack ${OPENNI_LIBRARY}) 

target_link_libraries(${PROJECT_NAME} ${LIBS})
