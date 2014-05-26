cmake_minimum_required(VERSION 2.6)

PROJECT(SGPSProject)

SET(CMAKE_BUILD_TYPE Debug)


INCLUDE_DIRECTORIES(/usr/local/include/)

#It could be necessary to change this path
#LINK_DIRECTORIES(/usr/lib/ )

SET(SGPSProject_SRCS    
			plotcoordinates.cpp
                        )

ADD_EXECUTABLE(sgps_plotcoordinates ${SGPSProject_SRCS})

TARGET_LINK_LIBRARIES(sgps_plotcoordinates sgps boost_filesystem boost_system m)

