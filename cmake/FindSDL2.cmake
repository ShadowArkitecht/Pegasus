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
# Find SD2

# SDL2 search paths
set(SDL2_SEARCH_PATHS ~/Library/Frameworks
	                  /Library/Frameworks
                	  /usr/local
                	  /usr
                	  /sw # Fink
                	  /opt/local # DarwinPorts
                	  /opt/csw # Blastwave
                	  /opt)

# Find the path that SDL2 includes are installed to.
find_path(SDL2_INCLUDE_DIR NAMES SDL2/SDL.h 
	                       HINTS $ENV{SDL2DIR}
                           PATH_SUFFIXES include
                           PATHS ${SDL2_SEARCH_PATHS})

# Find the path that SDL2 libraries are installed to.
find_library(SDL2_LIBRARY_LOCATION NAMES SDL2
                                   HINTS $ENV{SDL2DIR}
	                               PATH_SUFFIXES lib lib/x86
	                               PATHS ${SDL2_SEARCH_PATHS})

if (NOT SDL2_BUILDING_LIBRARY)
	if  (NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")
		find_library(SDL2MAIN_LIBRARY NAMES SDL2main
			                          HINTS $ENV{SDL2DIR}
			                          PATH_SUFFIXES lib lib/x86
			                          PATHS ${SDL2_SEARCH_PATHS})

	endif()
endif()

if (NOT APPLE)
	find_package(Threads)
endif()

if (MINGW)
	set(MINGW32_LIBRARY mingw32 "-mwindows" CACHE STRING "mwindows for MinGW")
endif()

if (SDL2_LIBRARY_LOCATION)
	if (NOT SDL2_BUILDING_LIBRARY)
		if (SDL2MAIN_LIBRARY)
			set(SDL2_LIBRARY_LOCATION ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_LOCATION})
		endif()
	endif()

	if (NOT APPLE)
		set(SDL2_LIBRARY_LOCATION ${SDL2_LIBRARY_LOCATION} ${CMAKE_THREAD_LIBS_INIT})
	endif()

	if (MINGW)
		set(SDL2_LIBRARY_LOCATION ${MINGW32_LIBRARY} ${SDL2_LIBRARY_LOCATION})
	endif()

	set(SDL2_LIBRARY ${SDL2_LIBRARY_LOCATION} CACHE STRING "Where the SDL2 Library can be found")
	set(SDL2_LIBRARY_LOCATION "${SDL2_LIBRARY_LOCATION}" CACHE INTERNAL "")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)