cmake_minimum_required(VERSION 2.6)
#include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# add include search paths
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "CMAKE_MODULE_PATH")
find_package(sgps REQUIRED)
include_directories(${SGPS_INCLUDE_DIRS})
link_directories(${SGPS_LIBRARIES})
#rosbuild_add_executable(bin_control_tray_articulares_off_line src/control_tray_articular_offline.cpp)
#target_link_libraries(bin_control_tray_articulares_off_line pmac)
#rosbuild_add_executable(bin_control_tray_articulares_on_line src/control_tray_articular_online.cpp)
#target_link_libraries(bin_control_tray_articulares_on_line pmac)

add_executable(test src/SGPS_test.cpp)
target_link_libraries(test ${SGPS_LIBRARIES} boost_filesystem boost_system m)

