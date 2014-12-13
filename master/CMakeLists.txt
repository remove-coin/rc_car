cmake_minimum_required(VERSION 2.8.3)
project(master)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

include(FindBoost)
find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)

find_package(Qt4 REQUIRED)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES master
  CATKIN_DEPENDS roscpp rospy std_msgs
  DEPENDS system_lib
)

###########
## Build ##
###########
set(sources src/Qtnode/main_window.cpp 
		src/Qtnode/qnode.cpp
		src/Qtnode/main.cpp )
		
set(headers src/Qtnode/main_window.hpp 
		src/Qtnode/qnode.hpp)
set(forms src/Qtnode/main_window.ui)

qt4_wrap_cpp(MOC_SOURCES ${headers})
qt4_wrap_ui(UIC_FILES ${forms})

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}
${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR} 
  ${QT_INCLUDE_DIRS}
  )
  
  INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#############
## Targets ##
#############



ADD_EXECUTABLE(qtnode ${sources} 
    ${MOC_SOURCES}
    ${UIC_FILES})
TARGET_LINK_LIBRARIES(qtnode ${QT_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies(qtnode ${catkin_EXPORTED_TARGETS})

add_executable(srv_publisher src/srv_publisher.cpp)
target_link_libraries(srv_publisher ${catkin_LIBRARIES})
add_dependencies(srv_publisher ${catkin_EXPORTED_TARGETS})

