cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME nuitrack_gl_sample)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/include/middleware)
include(../cmake/DetectPlatform.cmake)

if(UNIX)
	set(LIBS glut GL)
	set(OPENGL_LIBS glut GL)
elseif(WIN32)
	cmake_policy(SET CMP0135 NEW)
	include(FetchContent)
	FetchContent_Declare(
		freeglut 
		URL https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC.zip)
	FetchContent_MakeAvailable(freeglut)
	set(INCLUDE_PATH ${INCLUDE_PATH} ${freeglut_SOURCE_DIR}/include)
	set(LIBRARY_PATH ${freeglut_SOURCE_DIR}/lib/${FREEGLUT_ARCH})
	set(LIBS freeglut glu32 opengl32)
endif()

set(LIBRARY_PATH ${LIBRARY_PATH} ${CMAKE_CURRENT_LIST_DIR}/../../Nuitrack/lib/${PLATFORM_DIR}) 

include_directories(${INCLUDE_PATH})
link_directories(${LIBRARY_PATH})

add_executable(${PROJECT_NAME} src/NuitrackGLSample.cpp src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBS} nuitrack)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${freeglut_SOURCE_DIR}/bin/${FREEGLUT_ARCH}/freeglut.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()