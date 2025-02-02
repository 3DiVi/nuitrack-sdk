cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME nuitrack_csharp_sample)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(CSharp)
include(UseCSharp)
include(FindMono)

set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/Program.cs)

CSHARP_ADD_EXECUTABLE(${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_NAME}
    " "
    "/unsafe"
    "${SOURCES}"
    "System.Drawing.dll;System.Windows.Forms.dll;${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/csharp/nuitrack.net.dll" )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe DESTINATION ${CMAKE_CURRENT_LIST_DIR})
# copying nuitrack.net.dll to the build directory
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_LIST_DIR}/nuitrack.net.dll
        ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()