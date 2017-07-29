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
# File directories
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/pegasus/core")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/core")

################################################################################
# Header and source files
set(HEADER_FILES "${INCLUDE_DIR}/asset.hpp" 
                 "${INCLUDE_DIR}/config_file.hpp"
                 "${INCLUDE_DIR}/context.hpp"
                 "${INCLUDE_DIR}/resource_handle.hpp"
                 "${INCLUDE_DIR}/resource_manager.hpp"
                 "${INCLUDE_DIR}/resources.hpp"
                 "${INCLUDE_DIR}/window.hpp")
             
set(SOURCE_FILES "${SOURCE_DIR}/asset.cpp"
                 "${SOURCE_DIR}/config_file.cpp"
                 "${SOURCE_DIR}/resource_manager.cpp"
                 "${SOURCE_DIR}/resources.cpp"
                 "${SOURCE_DIR}/window.cpp")

################################################################################
# Library creation
add_library(pegasus_core ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(pegasus_core PROPERTIES LINKER_LANGUAGE CXX)
