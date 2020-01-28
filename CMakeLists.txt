cmake_minimum_required(VERSION 2.8.3)
project(seher_support)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  tf_conversions
  geometry_msgs
)


catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    roscpp
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(links_pose_publisher src/links_pose_publisher/links_pose_publisher_node.cpp
                                    src/links_pose_publisher/links_pose_publisher.cpp
                                    )
target_link_libraries(links_pose_publisher ${catkin_LIBRARIES})
add_dependencies(links_pose_publisher  ${catkin_EXPORTED_TARGETS})
install(TARGETS links_pose_publisher DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

