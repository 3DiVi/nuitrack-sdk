cmake_minimum_required(VERSION 3.14)
project(nuitrack_sample LANGUAGES C CXX OBJC OBJCXX)

set(CMAKE_SYSTEM_NAME                       iOS)
set(CMAKE_OSX_SYSROOT                       iphoneos)
set(CMAKE_OSX_DEPLOYMENT_TARGET             "12.1")
set(CMAKE_OSX_ARCHITECTURES                 "arm64")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_STYLE   Automatic)
set(CMAKE_CXX_STANDARD                      11)
set(BUILD_WITH_INSTALL_RPATH                ON)

set(SOURCES
    nuitrack_sample/main.m
    nuitrack_sample/AppDelegate.m
    nuitrack_sample/AppDelegate.m
    nuitrack_sample/ImageConversions.mm
    nuitrack_sample/ImageConversions.h
    nuitrack_sample/NuitrackDrawing.mm
    nuitrack_sample/NuitrackDrawing.h
    nuitrack_sample/NuitrackModules.h
    nuitrack_sample/NuitrackModules.cpp
    nuitrack_sample/NuitrackModules.h
    nuitrack_sample/StructureCallbackReceiver.mm
    nuitrack_sample/StructureCallbackReceiver.h
    nuitrack_sample/ViewController.h
    nuitrack_sample/ViewController.mm
    )


set(NUITRACK_FRAMEWORK  "${CMAKE_SOURCE_DIR}/nuitrack.framework")
set(STRUCTURE_FRAMEWORK "${CMAKE_SOURCE_DIR}/Structure.framework")


set(RESOURCES
    nuitrack_sample/Assets.xcassets
    nuitrack_sample/Base.lproj/Main.storyboard
    )

set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

add_executable(nuitrack_sample MACOSX_BUNDLE ${SOURCES} ${RESOURCES})

target_include_directories(nuitrack_sample PRIVATE ${NUITRACK_FRAMEWORK})

set_target_properties(nuitrack_sample PROPERTIES
    XCODE_EMBED_FRAMEWORKS "${NUITRACK_FRAMEWORK};${STRUCTURE_FRAMEWORK}"
    XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY ON

    MACOSX_BUNDLE TRUE
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER   "com.nuitrack.sample"
    MACOSX_BUNDLE_GUI_IDENTIFIER                "com.nuitrack.sample"
    MACOSX_BUNDLE_BUNDLE_VERSION                "1.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING          "1.0"

    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/nuitrack_sample/Info.plist"

    XCODE_ATTRIBUTE_ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES "YES"
    XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/Frameworks"
    )

target_compile_options(nuitrack_sample PRIVATE "-fobjc-arc")

target_link_libraries(nuitrack_sample
    "-framework UIKit"
    "-framework Foundation"
    "-framework CoreGraphics"
    "-framework QuartzCore"
    "-framework AVFoundation"
    "-F${CMAKE_SOURCE_DIR}"
    "-framework nuitrack"
    "-framework Structure"
    )