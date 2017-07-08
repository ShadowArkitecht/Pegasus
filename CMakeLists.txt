# Sparky Engine
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
project(Sparky)

# Set the project versions.
set(SPARKY_MAJOR_VERSION 0)
set(SPARKY_MINOR_VERSION 1)
set(SPARKY_PATCH_VERSION 0)
set(SPARKY_VERSION ${SPARKY_MAJOR_VERSION}.${SPARKY_MINOR_VERSION}.${SPARKY_PATCH_VERSION})

# Include any additional cmake files.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################################################################
# Include directories
include_directories("${CMAKE_SOURCE_DIR}/include") # Sparky engine includes
include_directories("${CMAKE_SOURCE_DIR}/lib/pugixml/src") # Pugixml includes
include_directories("${CMAKE_SOURCE_DIR}/lib/sol2/single")

################################################################################
# Libraries

########################################
# SDL2 image (Image-processing) library.
# SDL2 image has been found, include the library.
if (NOT SDL2_IMAGE_FOUND)
    find_package(SDL2_IMAGE REQUIRED)
    message(STATUS "SDL2 image found. Linking to Sparky.")
    # Link the library.
    link_libraries(${SDL2_IMAGE_LIBRARY})
endif()

########################################
# Lua (scripting) library.
if (NOT LUA_FOUND AND NOT LUA51_FOUND)
	find_package(Lua51 REQUIRED)
	include_directories("${LUA_INCLUDE_DIR}")
	link_libraries(${LUA_LIBRARIES})
	message(STATUS "Lua found. Linking to Sparky.")
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
# Sparky executable
# This is temporary, until the lib is linked to an .exe/game.
add_executable(sparky ${TEMP_SOURCE_FILES}) 

# Set linker language to C++
set_target_properties(sparky PROPERTIES LINKER_LANGUAGE CXX) 
# Link libraries to executable.
target_link_libraries(sparky pugixml sparky_core sparky_utilities sparky_scripting)

################################################################################
# Test executable.
add_executable(sparky_test ${TEST_SOURCE_FILES})

# Set linker language to C++.
set_target_properties(sparky_test PROPERTIES LINKER_LANGUAGE CXX)
# Link the libraries to test executable.
target_link_libraries(sparky_test catch pugixml sparky_core sparky_utilities sparky_scripting)

enable_testing(true)
add_test(NAME sparky_test COMMAND sparky_tests)
