cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

include(../cmake/DetectPlatform.cmake)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include
	${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)

link_directories(${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR})

add_executable(nuitrack_console_sample src/main.cpp)
target_link_libraries(nuitrack_console_sample nuitrack)
