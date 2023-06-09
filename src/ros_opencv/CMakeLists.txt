cmake_minimum_required(VERSION 3.0.2)
project(ros_opencv)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  sensor_msgs
)

find_package(OpenCV REQUIRED)

catkin_package(
  # INCLUDE_DIRS include
  #LIBRARIES ros_opencv
  CATKIN_DEPENDS cv_bridge roscpp sensor_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(sub_pub_image src/sub_pub_image.cpp src/image_class.cpp)
target_link_libraries(sub_pub_image ${catkin_LIBRARIES})