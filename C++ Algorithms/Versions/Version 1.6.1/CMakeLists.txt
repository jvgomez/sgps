cmake_minimum_required(VERSION 2.6)

PROJECT(readdir)

#INCLUDE_DIRECTORIES( )

#It could be necessary to change this path
LINK_DIRECTORIES(/usr/lib/)

SET(readdir_SRCS	main.cpp diranalyzer.cpp file.cpp)

ADD_EXECUTABLE(readdir ${readdir_SRCS})

TARGET_LINK_LIBRARIES(readdir boost_filesystem)

