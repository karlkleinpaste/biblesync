# Accepted options
# - BUILD_SHARED_LIBS (default FALSE) - set to true to build shared libraries
# - CMAKE_INSTALL_PREFIX (default "/usr/local") - set to directory where you want libs installed
# - LIBDIR (default "CMAKE_INSTALL_PREFIX/lib") - set to directory where binaries should be installed
# - INCLUDEDIR (default "CMAKE_INSTALL_PREFIX/include") - set to directory where header files should be installed to
PROJECT(libbiblesync CXX)
SET(BIBLESYNC_VERSION 1.0.0)
# A required CMake line
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Where our custom Find* files are located
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Just a variable so if we expand to more files we only have to edit one place
SET(biblesync_sources src/biblesync.cc)
SET(biblesync_headers            include/biblesync.hh
    "${CMAKE_CURRENT_BINARY_DIR}/include/biblesync-version.hh")

# Set a library to build (the fact that it is "biblesync" and matches the name
# in the PROJECT declaration above is purely a matter of choice and convention and
# need not be the case. We can also add additional libraries if we wanted to have
# multiple products from this build process
IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(biblesync SHARED ${biblesync_sources})
ELSE(BUILD_SHARED_LIBS)
    ADD_LIBRARY(biblesync STATIC ${biblesync_sources})
ENDIF(BUILD_SHARED_LIBS)

# Set the default headers location
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}/include")
ADD_DEFINITIONS(-DBUILDING)

# System defines
IF(WIN32)
    MESSAGE(STATUS "Building for Win32")
    ADD_DEFINITIONS(-DWIN32)
ELSE(WIN32)
    # Headers and linkage from libuuid
    FIND_PACKAGE(UUID REQUIRED)
    INCLUDE_DIRECTORIES("${UUID_INCLUDE_DIRS}")
    TARGET_LINK_LIBRARIES(biblesync "${UUID_LIBRARIES}")
ENDIF(WIN32)

# Allow build systems to specify non-standard install locations
IF(NOT CMAKE_INSTALL_PREFIX)
    SET(PREFIX "/usr/local")
ELSE(NOT CMAKE_INSTALL_PREFIX)
    SET(PREFIX "${CMAKE_INSTALL_PREFIX}")
ENDIF(NOT CMAKE_INSTALL_PREFIX)

MESSAGE(STATUS "Will install to: ${PREFIX}")

SET(LIBDIR "${PREFIX}/lib" CACHE STRING 
    "Object code library install directory. Defaults to CMAKE_INSTALL_PREFIX/lib")
SET(INCLUDEDIR "${PREFIX}/include/biblesync" CACHE STRING 
    "Header library install directory. Defaults to CMAKE_INSTALL_PREFIX/include/biblecync")

##########################################################################################
# Copied from Sword's code to handle the setting of version numbers
##########################################################################################
# Post-processing of variables
MACRO(PROCESS_VERSION LEVEL VALUE)
    SET(BIBLESYNC_VERSION_${LEVEL} ${VALUE})
    IF(${VALUE} LESS 10)
        SET(${LEVEL} "00${VALUE}")
    ELSEIF(${VALUE} LESS 100)
        SET(${LEVEL} "0${VALUE}")
    ELSE()
        SET(${LEVEL} "${VALUE}")
    ENDIF()
ENDMACRO()

STRING(REGEX MATCHALL "^([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.?([0-9]+)?$"
    BIBLESYNC_VERSION_PARTS "${BIBLESYNC_VERSION}")
# We don't always have a nano version
IF("${CMAKE_MATCH_4}" STREQUAL "")
    SET(CMAKE_MATCH_4 "0")
ENDIF("${CMAKE_MATCH_4}" STREQUAL "")

SET(BIBLESYNC_VERSION_MAJOR ${CMAKE_MATCH_1}) # No post-processing on this, so it's not octal
PROCESS_VERSION("MINOR" ${CMAKE_MATCH_2})
PROCESS_VERSION("MICRO" ${CMAKE_MATCH_3})
PROCESS_VERSION("NANO"  ${CMAKE_MATCH_4})

SET(BIBLESYNC_VERSION_STR "${BIBLESYNC_VERSION}")
SET(BIBLESYNC_VERSION_NUM "${BIBLESYNC_VERSION_MAJOR}${MINOR}${MICRO}${NANO}")
##########################################################################################
# End of copy from Sword's code
##########################################################################################

# Set the variables in the .in file
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/biblesync-version.hh.in 
    ${CMAKE_CURRENT_BINARY_DIR}/include/biblesync-version.hh @ONLY)

# Install both the library and its headers
INSTALL(TARGETS biblesync
    DESTINATION "${LIBDIR}")
INSTALL(FILES ${biblesync_headers}
    DESTINATION "${INCLUDEDIR}")
