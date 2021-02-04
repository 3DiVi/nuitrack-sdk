# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

add_library(nuitrack_gl_sample SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/android_main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NuitrackGLSample.cpp)

set(NUITRACK_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../)

set(ANDROID_ARCH android)
if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(ANDROID_ARCH android-arm64)
endif()

add_library(app-glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library(nuitrack SHARED IMPORTED)
set_target_properties(nuitrack PROPERTIES IMPORTED_LOCATION ${NUITRACK_SDK_PATH}/Nuitrack/lib/${ANDROID_ARCH}/libnuitrack.so)

add_library(middleware SHARED IMPORTED)
set_target_properties(middleware PROPERTIES IMPORTED_LOCATION ${NUITRACK_SDK_PATH}/Nuitrack/lib/${ANDROID_ARCH}/libmiddleware.so)

include_directories(${NUITRACK_SDK_PATH}/Nuitrack/include ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib log)
find_library(android-lib android)
find_library(egl-lib EGL)
find_library(gles-lib GLESv1_CM)

target_link_libraries(nuitrack_gl_sample app-glue ${log-lib} ${android-lib} ${egl-lib} ${gles-lib} nuitrack middleware)