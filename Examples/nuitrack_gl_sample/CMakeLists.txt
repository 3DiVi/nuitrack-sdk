cmake_minimum_required(VERSION 3.14)
project(nuitrack_gl_sample)

set(CMAKE_CXX_STANDARD 11)

include(../cmake/DetectPlatform.cmake)

list(APPEND INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)
set(LIBRARY_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR})

if(UNIX)
    list(APPEND LIBS glut GL)
elseif(WIN32)
    cmake_policy(SET CMP0135 NEW)
    include(FetchContent)
    FetchContent_Declare(
        freeglut
        URL https://github.com/freeglut/freeglut/releases/download/v3.8.0/freeglut-3.8.0.tar.gz)
    FetchContent_MakeAvailable(freeglut)
    list(APPEND INCLUDE_PATH ${freeglut_SOURCE_DIR}/include)
    list(APPEND LIBS freeglut glu32 opengl32)
endif()

add_executable(nuitrack_gl_sample src/NuitrackGLSample.cpp src/main.cpp)

target_include_directories(nuitrack_gl_sample PRIVATE ${INCLUDE_PATH})
target_link_directories(nuitrack_gl_sample PRIVATE ${LIBRARY_PATH})
target_link_libraries(nuitrack_gl_sample PRIVATE ${LIBS} nuitrack)
target_compile_definitions(nuitrack_gl_sample PRIVATE HPP)

if(WIN32)
    add_custom_command(TARGET nuitrack_gl_sample POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:freeglut> $<TARGET_FILE_DIR:nuitrack_gl_sample>)
endif()