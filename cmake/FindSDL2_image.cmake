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
#    if  you use this software in a product, an acknowledgement
#    in the product documentation would be appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such,
#    and must not be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.


################################################################################
# Find SD2 image

# SDL2 image search paths
set(SDL2_SEARCH_PATHS ~/Library/Frameworks
	                  /Library/Frameworks
                	  /usr/local
                	  /usr
                	  /sw # Fink
                	  /opt/local # DarwinPorts
                	  /opt/csw # Blastwave
                	  /opt)

find_library(SDL2_IMAGE_LIBRARY_LOCATION NAMES SDL2_image
                                         HINTS $ENV{SDL2DIR}
	                                     PATH_SUFFIXES lib lib/x86
	                                     PATHS ${SDL2_SEARCH_PATHS})


set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_LIBRARY_LOCATION} CACHE STRING "Where the SDL2 Library can be found")
set(SDL2_IMAGE_LIBRARY_LOCATION "${SDL2_IMAGE_LIBRARY_LOCATION}" CACHE INTERNAL "")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_IMAGE REQUIRED_VARS SDL2_IMAGE_LIBRARY)