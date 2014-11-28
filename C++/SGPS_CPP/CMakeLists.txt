# This is the main CMake configuration file, you should always do "cmake ." from here and not from subdirs
# Main project declaration


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)



PROJECT(SGPS CXX C)


# Useful declaration for avoiding relative path
SET(SGPS_CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build_tools/cmake")
SET(SGPS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE(${SGPS_CMAKE_MODULE_PATH}/prettymessage.cmake)
INCLUDE(${SGPS_CMAKE_MODULE_PATH}/utils.cmake)


# Disable in-source builds
IF("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	MESSAGE(FATAL_ERROR "In-source builds are not allowed.")
ENDIF("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")


# Verbose or not verbose
IF($ENV{VERBOSE})
	info("Verbose mode on")
ELSE($ENV{VERBOSE})
	info("Verbose mode off (type 'VERBOSE=1 cmake .' to enable it)")
ENDIF($ENV{VERBOSE})

# Needed by CMake versione 2.6 or later (Run "cmake --help-policy CMP0003" for more information.)"
# specifically, we are using full-path when possible for linking libraries
# this should be mandatory for packages found using ROOT directive
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Version
#SET(SGPS_V_MAJOR 0)
#SET(SGPS_V_MINOR 0)
#SET(SGPS_V_PATCH 1)

# Optional flags and configurable stuff in ccmake
# Replacement for manual.cmake
SET(COMPILATION_FLAGS "-W -Wall -O2 -ggdb" CACHE STRING "CMake compilation flags")
SET(CMAKE_BUILD_TYPE "Debug")

# Operating System specific behaviors and switches
INCLUDE(${SGPS_CMAKE_MODULE_PATH}/os.cmake)
# Find and configure switches for external libraries and applications
INCLUDE(${SGPS_CMAKE_MODULE_PATH}/deps.cmake)

# Creation of config.h
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.cmake" "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h")


info("")
info("..:: Variables ::..")
info("SGPS_DIR=${SGPS_DIR}")

info("")

INCLUDE_DIRECTORIES("${SGPS_DIR}/src/include/*")

FILE(GLOB_RECURSE BASE_SRC "src/base/src/*")

SET(SOURCES ${BASE_SRC})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_LIBRARY(sgps STATIC ${SOURCES})
TARGET_LINK_LIBRARIES(sgps boost_system boost_filesystem m)


# Subdirectories
ADD_SUBDIRECTORY(src/apps)
#ADD_SUBDIRECTORY(src/base)


INSTALL(PROGRAMS ${PROJECT_BINARY_DIR}/bin/sgps_sgpstest ${PROJECT_BINARY_DIR}/bin/sgps_plotday
  DESTINATION bin)


INSTALL(TARGETS sgps
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)


INSTALL(FILES src/base/include/sgps.h 
          src/base/include/astroalg.h 
          src/base/include/coordinates.h 
          src/base/include/celestialmodel.h 
          src/base/include/console.h 
          src/base/include/day.h 
          src/base/include/diranalyzer.h 
          src/base/include/file.h 
          src/base/include/noaafile.h 
          src/base/include/gnuplot_i.h 
          src/base/include/logger.h 
          src/base/include/options.h 
          src/base/include/plotter.h
          src/base/include/huefile.h
          src/base/include/filedec.h
  DESTINATION include/sgps)


#SET(CMAKE_BUILD_TYPE Debug)

#set(EXECUTABLE_OUTPUT_PATH ../bin)
#set(LIBRARY_OUTPUT_PATH ../lib)
#rosbuild_genmsg()
#rosbuild_gensrv()
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#include_directories(../include)

#set(CMAKE_CXX_FLAGS "-g -Wall")
#set(LIBRARY_NAME sgps)

#message(STATUS "LIBRARY_NAME: "  ${LIBRARY_NAME})
#add_library(${LIBRARY_NAME} STATIC 
                        #src/astroalg.cpp
                        #src/celestialmodel.cpp
                        #src/day.cpp
                        #src/diranalyzer.cpp
                        #src/file.cpp
                        #src/logger.cpp
                        #src/noaafile.cpp 
                        #src/sgps.cpp
			#src/console.cpp
			#src/plotter.cpp
			#src/gnuplot_i.cpp
			#src/options.cpp )

#TARGET_LINK_LIBRARIES(${LIBRARY_NAME} boost_filesystem boost_system m)
#add_executable(plotDay apps/plotday.cpp)
#target_link_libraries(plotDay ${LIBRARY_OUTPUT_PATH}/${LIBRARY_NAME} boost_filesystem boost_system m)
#add_executable(binComandos src/comandos.cpp)
#target_link_libraries(binComandos ${LIBRARY_NAME})

#add_executable(binTerminal src/terminal.cpp)
#target_link_libraries(binTerminal ${LIBRARY_NAME})
