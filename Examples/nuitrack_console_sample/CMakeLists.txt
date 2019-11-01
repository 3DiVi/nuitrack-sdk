cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME nuitrack_console_sample)
project(${PROJECT_NAME})

add_definitions(-std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0)

set(NUITRACK_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)

if(UNIX)
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
endif()

set(NUITRACK_LIBRARY_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR}) 

include_directories(
	.
	${NUITRACK_INCLUDE_PATH}
)

link_directories(${NUITRACK_LIBRARY_PATH})

set(SOURCES
    src/main.cpp)
    
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS nuitrack)

target_link_libraries(${PROJECT_NAME} ${LIBS})
