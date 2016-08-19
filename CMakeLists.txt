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

# Open Cascade setup
# required opencascade libraries
# please don't change the order of libraries as this can cause linking problems
set (OCC_LIBS 
        TKIGES TKSTL TKSTEP 
        TKSTEPAttr TKOffset TKMesh 
        TKSTEP209 TKFillet TKSTEPBase 
        TKBool TKXSBase TKShHealing 
        TKBO TKPrim TKTopAlgo
        TKGeomAlgo TKBRep TKGeomBase
        TKG3d TKG2d TKMath TKernel TKService TKMesh TKOpenGl
)
find_package(OCE 0.16 REQUIRED COMPONENTS ${OCC_LIBS})
if(OCE_FOUND)
  set(OpenCASCADE_LIBRARIES ${OCC_LIBS})
  set(OpenCASCADE_INCLUDE_DIR ${OCE_INCLUDE_DIRS})
  # get opencascade version
  IF(EXISTS "${OpenCASCADE_INCLUDE_DIR}/Standard_Version.hxx")
    FILE(STRINGS "${OpenCASCADE_INCLUDE_DIR}/Standard_Version.hxx" occ_version_str REGEX "^#define[\t ]+OCC_VERSION_COMPLETE[\t ]+\".*\"")
    STRING(REGEX REPLACE "^#define[\t ]+OCC_VERSION_COMPLETE[\t ]+\"([^\"]*)\".*" "\\1" OCC_VERSION_STRING "${occ_version_str}")
    UNSET(occ_version_str)
  ENDIF()
  # get directory of shared libs
  get_target_property(TKERNEL_LOCATION TKernel LOCATION)
  get_filename_component(OpenCASCADE_DLL_DIRECTORY ${TKERNEL_LOCATION} PATH)
else(OCE_FOUND)
  message("OCE not found! Searching for OpenCASCADE.")
  find_package(OpenCASCADE 6.6.0 REQUIRED COMPONENTS ${OCC_LIBS})
endif(OCE_FOUND)
include_directories(${OpenCASCADE_INCLUDE_DIR})

# QT package setup:
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)


# OpenGL setup
set(QT_USE_QTOPENGL TRUE)
find_package(GLUT)
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
   include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
   MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)


# build flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11")

# Setup include directories
set (AIRCONICS_INCLUDE "include")
include_directories(${AIRCONICS_INCLUDE})

# Need to include both the src header directory and the relative output created
# by cmake to ensure the created ui_occqt header is found
set (occQt_INCLUDE thirdparty/occQt)
set (occQt_UI_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/occQt)
include_directories(${occQt_INCLUDE} ${occQt_UI_INCLUDE})

# set some occqt variables needed by several libraries
set (occQt_LIB "occQt")

set(occQt_RESOURCES ${CMAKE_SOURCE_DIR}/thirdparty/occQt/occqt.qrc)

# The source files
add_subdirectory(thirdparty)
add_subdirectory(src)

# add_subdirectory(doc)
# add_subdirectory(test)

