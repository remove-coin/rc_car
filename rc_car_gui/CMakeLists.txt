cmake_minimum_required(VERSION 2.8.3)
project(rc_car_gui)


include_directories(${GAZEBO_INCLUDE_DIRS})

link_directories(${GAZEBO_LIBRARY_DIRS})
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  roscpp
  rospy 
  std_msgs
  )

## System dependencies are found with CMake's conventions

include(FindBoost)
find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)


find_package(Qt4 REQUIRED)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()


##################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  #INCLUDE_DIRS src
  #LIBRARIES ur5_rqt_force
  CATKIN_DEPENDS roscpp rospy
  DEPENDS system_lib std_msgs
)

###########
## Build ##
###########
set(sources main.cpp rc_car.cpp)
set(headers rc_car.h)
set(forms rc_car.ui)

qt4_wrap_cpp(MOC_SOURCES ${headers})
qt4_wrap_ui(UIC_FILES ${forms})


include_directories(
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR} 
  ${QT_INCLUDE_DIRS}
)


ADD_EXECUTABLE(rc_car ${sources} 
    ${MOC_SOURCES}
    ${UIC_FILES})
TARGET_LINK_LIBRARIES(rc_car ${QT_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies(rc_car ${catkin_EXPORTED_TARGETS})

