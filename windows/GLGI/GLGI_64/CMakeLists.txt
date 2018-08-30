cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project (GLGI)
execute_process( COMMAND "make" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/deps/glew/auto)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glew/build/cmake)

set (glfw_DIR ${PROJECT_SOURCE_DIR}/deps/glfw/)
set (glew_DIR ${PROJECT_SOURCE_DIR}/deps/glew/build/cmake)

#find_package (glew)
#find_package (glfw)

# The version number.
set (GLGI_VERSION_MAJOR 1)
set (GLGI_VERSION_MINOR 0)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#file(GLOB INCLUDES ${PROJECT_VERSION}/includes/*)
file(GLOB GENHEADERS ${PROJECT_SOURCE_DIR}/headers/*.h)

	
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_SOURCE_DIR}/include/")
#include_directories("${PROJECT_SOURCE_DIR}/include/GL")
#include_directories($INCLUDES)

include_directories("${PROJECT_SOURCE_DIR}/headers/")
if (MSVC)
	include_directories("${PROJECT_SOURCE_DIR}/MSVCheaders")
	file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/MSVCheaders/*.h)
endif (MSVC)
if (UNIX)
	include_directories("${PROJECT_SOURCE_DIR}/UNIXheaders")
	file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/UNIXheaders/*.h)

			
endif (UNIX)
#link_directories(/lib/libgl)


add_library (GLGI ${GENHEADERS} ${HEADERS} ${SOURCES} )

link_libraries(GLGI glew glfw libjpeg)


