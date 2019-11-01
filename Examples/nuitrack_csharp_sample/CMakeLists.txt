cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(CSharp)
include(UseCSharp)
include(FindMono)

set (SOURCES ${CMAKE_CURRENT_LIST_DIR}/Program.cs)
set (PROJECT_NAME nuitrack_csharp_sample)

CSHARP_ADD_EXECUTABLE(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_NAME} " " "${SOURCES}" "System.Drawing.dll;System.Windows.Forms.dll;${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/csharp/nuitrack.net.dll" )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe DESTINATION ${CMAKE_CURRENT_LIST_DIR})
