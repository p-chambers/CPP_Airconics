
set (APP_SOURCES
	main.cpp
	)

set (SOURCES
	AirconicsFuselage.cpp
	AirconicsBase.cpp)

# set (HEADERS
# 	${AIRCONICS_INCLUDE}/AirconicsFuselage.hpp)

# Compile libraries
add_library(Airconics STATIC ${SOURCES})

# print include directories for debugging
get_property(test_LINK_DIRECTORIES DIRECTORY PROPERTY LINK_DIRECTORIES)
message("LINK_DIRECTORIES = ${test}")

message("HELLO, SOURCES ARE: ${SOURCES}")

# QT package setup:
find_package(Qt5Widgets REQUIRED)
set (QT_LIB Qt5::Widgets)

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
        TKG3d TKG2d TKMath TKernel TKService TKMesh
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

# print the include directories to ensure they are all present
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

message("The opencascade libraries are: ${OpenCASCADE_LIBRARIES}")

# Compile main and link with the compiled libraries
add_executable (airconics ${APP_SOURCES})
target_link_libraries (airconics
		Airconics
		${QT_LIB}
		${OpenCASCADE_LIBRARIES}
		)
