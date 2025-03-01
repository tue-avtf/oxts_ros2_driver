cmake_minimum_required(VERSION 3.8)
project(oxts_ins VERSION 0.1.0)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_kdl REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(oxts_msgs REQUIRED)


add_executable(oxts_ins 
               src/conversions/convert.cpp 
               src/conversions/convert_node.cpp
               src/conversions/wrapper.cpp
               src/lib/NComRxC.c
               src/lib/nav_conversions.cpp
)

ament_target_dependencies(oxts_ins 
                          rclcpp
                          std_msgs
                          sensor_msgs
                          geometry_msgs
                          nav_msgs
                          tf2
                          tf2_kdl
                          tf2_geometry_msgs
                          oxts_msgs)
target_include_directories(oxts_ins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${Boost_INCLUDE_DIRS}
  $<INSTALL_INTERFACE:include>)


install(TARGETS oxts_ins
        DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY 
        config urdf rviz
        DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
