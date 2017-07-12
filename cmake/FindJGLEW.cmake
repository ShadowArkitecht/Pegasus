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
#    if  you use this software in a product, an acknowledgement
#    in the product documentation would be appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such,
#    and must not be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.

################################################################################
# Find GLEW

# Glew search paths.
set(JGLEW_SEARCH_PATHS ~/Library/Frameworks
	                  /Library/Frameworks
                	  /usr/local
                	  /usr
                	  /sw # Fink
                	  /opt/local # DarwinPorts
                	  /opt/csw # Blastwave
                	  /opt)

# Find the path to the include files.
find_path(JGLEW_INCLUDE_DIR NAMES GL/glew.h 
	                        HINTS $ENV{GLEWDIR}
                            PATH_SUFFIXES include
                            PATHS ${JGLEW_SEARCH_PATHS})

# Find the glew libraries.
find_library(JGLEW_LIBRARY_LOCATION NAMES glew32
                                    HINTS $ENV{GLEWDIR}
	                                PATH_SUFFIXES lib lib/Release lib/Release/Win32
	                                PATHS ${JGLEW_SEARCH_PATHS})

if (JGLEW_LIBRARY_LOCATION)
	set(JGLEW_LIBRARY ${JGLEW_LIBRARY_LOCATION} CACHE STRING "Where the GLEW Library can be found")
	set(JGLEW_LIBRARY "${JGLEW_LIBRARY_LOCATION}" CACHE INTERNAL "")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JGLEW REQUIRED_VARS JGLEW_LIBRARY JGLEW_INCLUDE_DIR)