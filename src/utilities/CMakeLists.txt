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
# File directories
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/sparky/utilities")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/utilities")

################################################################################
# Header and source files
set(HEADER_FILES "${INCLUDE_DIR}/exceptions/no_factory_found_exception.hpp"
                 "${INCLUDE_DIR}/exceptions/no_resource_exception.hpp"
                 "${INCLUDE_DIR}/exceptions/not_implemented_exception.hpp"
                 "${INCLUDE_DIR}/console_policy.hpp"
                 "${INCLUDE_DIR}/factory.hpp"
                 "${INCLUDE_DIR}/file_policy.hpp"
                 "${INCLUDE_DIR}/file_reader.hpp"
                 "${INCLUDE_DIR}/iasset_factory.hpp"
                 "${INCLUDE_DIR}/ipolicy.hpp"
                 "${INCLUDE_DIR}/iserializable_service.hpp"
                 "${INCLUDE_DIR}/logger.hpp"
                 "${INCLUDE_DIR}/logger_factory.hpp"
                 "${INCLUDE_DIR}/lua_serializable_service.hpp"
                 "${INCLUDE_DIR}/non_copyable.hpp"
                 "${INCLUDE_DIR}/reader.hpp"
                 "${INCLUDE_DIR}/singleton.hpp"
                 "${INCLUDE_DIR}/stream_reader.hpp"
                 "${INCLUDE_DIR}/string_utils.hpp"
                 "${INCLUDE_DIR}/xml_serializable_service.hpp")

set(SOURCE_FILES "${SOURCE_DIR}/exceptions/no_factory_found_exception.cpp"
                 "${SOURCE_DIR}/exceptions/no_resource_exception.cpp"
                 "${SOURCE_DIR}/exceptions/not_implemented_exception.cpp"
                 "${SOURCE_DIR}/console_policy.cpp"
                 "${SOURCE_DIR}/file_policy.cpp"
                 "${SOURCE_DIR}/file_reader.cpp"
                 "${SOURCE_DIR}/iasset_factory.cpp"
                 "${SOURCE_DIR}/logger.cpp"
                 "${SOURCE_DIR}/logger_factory.cpp"
                 "${SOURCE_DIR}/lua_serializable_service.cpp"
                 "${SOURCE_DIR}/reader.cpp"
                 "${SOURCE_DIR}/stream_reader.cpp"
                 "${SOURCE_DIR}/string_utils.cpp"
                 "${SOURCE_DIR}/xml_serializable_service.cpp")

################################################################################
# Library creation
add_library(sparky_utilities ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(sparky_utilities PROPERTIES LINKER_LANGUAGE CXX)
