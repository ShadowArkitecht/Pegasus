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
set(SPARKY_VERSION
    ${SPARKY_MAJOR_VERSION}.${SPARKY_MINOR_VERSION}.${SPARKY_PATCH_VERSION})

################################################################################
# Include directories
include_directories("${CMAKE_SOURCE_DIR}/include") # Sparky engine includes
include_directories("${CMAKE_SOURCE_DIR}/lib/pugixml/src") # Pugixml includes

################################################################################
# Libraries

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
                      ${CMAKE_SOURCE_DIR}/tests/test_asset_factory.cpp)

################################################################################
# Sparky executable
# This is temporary, until the lib is linked to an .exe/game.
add_executable(sparky ${TEMP_SOURCE_FILES}) 

# Set linker language to C++
set_target_properties(sparky PROPERTIES LINKER_LANGUAGE CXX) 
# Link libraries to executable.
target_link_libraries(sparky pugixml sparky_core sparky_utilities)

################################################################################
# Test executable.
add_executable(sparky_test ${TEST_SOURCE_FILES})

# Set linker language to C++.
set_target_properties(sparky_test PROPERTIES LINKER_LANGUAGE CXX)
# Link the libraries to test executable.
target_link_libraries(sparky_test catch pugixml sparky_core sparky_utilities)

enable_testing(true)
add_test(NAME sparky_test COMMAND sparky_tests)
