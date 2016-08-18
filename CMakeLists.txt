cmake_minimum_required(VERSION 2.6)

project (occ_airconics)

# Project Version
set (occ_airconics_VERSION_MAJOR 0)
set (occ_airconics_VERSION_MINOR 1)

# detect operating system
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_definitions(-DSYSTEM_DARWIN)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "AIX")
    add_definitions(-DSYSTEM_AIX)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()

# build flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11")

set (AIRCONICS_INCLUDE "include")

include_directories(${AIRCONICS_INCLUDE})

# The source files
add_subdirectory(src)
# add_subdirectory(doc)
# add_subdirectory(test)

