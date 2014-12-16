cmake_minimum_required(VERSION 2.8.3)
project(ros_pi)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

set(RASPRPM_LIBRARIES "-lwiringPi -lpthread")

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate services in the 'srv' folder
add_service_files(
  FILES
  Rpi_car.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_pi
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  #${Boost_INCLUDE_DIR} 
)






add_executable(car_service src/car_service.cpp)
target_link_libraries(car_service ${catkin_LIBRARIES} ${RASPRPM_LIBRARIES})
add_dependencies(car_service ${catkin_EXPORTED_TARGETS} ros_pi_gencpp)
