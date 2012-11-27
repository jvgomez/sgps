cmake_minimum_required(VERSION 2.6)

PROJECT(SGPSProject)

SET(CMAKE_BUILD_TYPE Debug)

INCLUDE_DIRECTORIES(../include/)

#It could be necessary to change this path
#LINK_DIRECTORIES(/usr/lib/ )

SET(SGPSProject_SRCS    SGPS_test.cpp 
                        astroalg.cpp
                        celestialmodel.cpp
                        day.cpp
                        diranalyzer.cpp
                        file.cpp
                        logger.cpp
                        noaafile.cpp 
                        sgps.cpp 
                        )

ADD_EXECUTABLE(sgps ${SGPSProject_SRCS})

TARGET_LINK_LIBRARIES(sgps boost_filesystem m)

