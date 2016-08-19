set(Airconics_LIB "Airconics")

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

# Compile main and link with the compiled libraries
message("QT forms = ${occQt_FORMS}")

# Ensure the resource pngs are carried through to the executable

add_executable (airconics ${APP_SOURCES} ${occQt_FORMS} ${occQt_RESOURCES})

qt5_use_modules(airconics Widgets)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

target_link_libraries (airconics
		# ${QT_LIBRARIES}
		${occQt_LIB}
		${Airconics_LIB}
		${OpenCASCADE_LIBRARIES}
		${OPENGL_LIBRARIES}
		)
