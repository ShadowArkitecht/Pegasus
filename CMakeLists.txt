# Pegasus Engine
# 2017 - Benjamin Carter (bencarterdev@outlook.com)
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented;
#    you must not claim that you wrote the original software.
#    If you use this software in a product, an acknowledgement
#    in the product documentation would be appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such,
#    and must not be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.

################################################################################
# Initial setup

# Minimum cmake verion required to function.
cmake_minimum_required(VERSION 3.1.0) 

# Sets the project name.
project(Pegasus)

# Set the project versions.
set(PEGASUS_MAJOR_VERSION 0)
set(PEGASUS_MINOR_VERSION 1)
set(PEGASUS_PATCH_VERSION 0)
set(PEGASUS_VERSION ${PEGASUS_MAJOR_VERSION}.${PEGASUS_MINOR_VERSION}.${PEGASUS_PATCH_VERSION})

# Include any additional cmake files.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set some compile/macro flags.
# Disable the irritating msvc flag for "unsafe" c functions.
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

################################################################################
# Include directories
include_directories("${CMAKE_SOURCE_DIR}/include")         # Pegasus engine includes
include_directories("${CMAKE_SOURCE_DIR}/lib/pugixml/src") # Pugixml includes
include_directories("${CMAKE_SOURCE_DIR}/lib/sol2/single") # sol2 includes
include_directories("${CMAKE_SOURCE_DIR}/lib/glm")         # OpenGL mathematics includes

################################################################################
# Libraries

########################################
# SDL2 (window and input) library.
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
	# The library has been found, include the files and link the libraries.
	message(STATUS "SDL2 found. Linking to Pegasus Engine.")
	include_directories(${SDL2_INCLUDE_DIR})
	link_libraries(${SDL2_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. SDL2 could not be found.")
endif()

########################################
# SDL2 image (Image-processing) library.
# SDL2 image has been found, include the library.
find_package(SDL2_IMAGE REQUIRED)
if (SDL2_IMAGE_FOUND)
    message(STATUS "SDL2 image found. Linking to Pegasus Engine.")
    # Link the library.
    link_libraries(${SDL2_IMAGE_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. SDL2_image could not be found.")
endif()

########################################
# OpenGL (graphics) library.
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	message(STATUS "OpenGL found. Linking to Pegasus Engine.")
	link_libraries(${OPENGL_gl_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. OpenGL could not be found.")
endif()

########################################
# Glew (OpenGL extensions) library.
find_package(JGLEW REQUIRED)
if (JGLEW_FOUND)
	message(STATUS "GLEW found. Linking to Pegasus Engine.")
	include_directories(${JGLEW_INCLUDE_DIR})
	link_libraries(${JGLEW_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. GLEW count not be found.")
endif()

########################################
# Lua (scripting) library.
if (NOT LUA_FOUND AND NOT LUA51_FOUND)
	find_package(Lua51 REQUIRED)
	include_directories("${LUA_INCLUDE_DIR}")
	link_libraries(${LUA_LIBRARIES})
	message(STATUS "Lua found. Linking to Pegasus Engine.")
else()
	message(FATAL_ERROR "CMake build failed. Lua could not be found.")
endif()

########################################
# Catch (Unit-test) library.
set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/catch/include)
# Create the library.
add_library(catch INTERFACE)
# Link the catch header files.
target_include_directories(catch INTERFACE ${CATCH_INCLUDE_DIR})

################################################################################
# Source directories
add_subdirectory("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/pugixml")

################################################################################
# Variables
set(TEMP_SOURCE_FILES ${CMAKE_SOURCE_DIR}/main.cpp)
# Unit test source files.
set(TEST_SOURCE_FILES ${CMAKE_SOURCE_DIR}/tests/test_main.cpp
	                  ${CMAKE_SOURCE_DIR}/tests/test_asset_factory.cpp
                      ${CMAKE_SOURCE_DIR}/tests/test_lua_serializable_service.cpp)

################################################################################
# Pegasus executable
# This is temporary, until the lib is linked to an .exe/game.
add_executable(pegasus ${TEMP_SOURCE_FILES}) 

# Set linker language to C++
set_target_properties(pegasus PROPERTIES LINKER_LANGUAGE CXX) 
# Link libraries to executable.
target_link_libraries(pegasus pugixml pegasus_core pegasus_graphics pegasus_scripting pegasus_utilities)

################################################################################
# Test executable.
add_executable(pegasus_test ${TEST_SOURCE_FILES})

# Set linker language to C++.
set_target_properties(pegasus_test PROPERTIES LINKER_LANGUAGE CXX)
# Link the libraries to test executable.
target_link_libraries(pegasus_test catch pugixml pegasus_core pegasus_graphics pegasus_scripting pegasus_utilities)

enable_testing(true)
add_test(NAME pegasus_test COMMAND pegasus_tests)
