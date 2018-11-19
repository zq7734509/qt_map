cmake_minimum_required(VERSION 2.8.3)
project(qt_map)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
set(EXECUTABLE_OUTPUT_PATH ~/catkin_ws/devel/lib/${PROJECT_NAME})

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  lcm2ros
  nav_msgs
  roscpp
  sensor_msgs
  std_msgs
  cv_bridge
  image_transport
)
set(Qt5WebEngineWidgets_DIR "/opt/Qt/5.11.0/gcc_64/lib/cmake/Qt5WebEngineWidgets")
find_package(Qt5WebEngineWidgets REQUIRED)
find_package(OpenCV REQUIRED )
find_package(Qt5  REQUIRED COMPONENTS  Widgets )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

 

set(SOURCES
  src/qt_map.cpp
  src/qtComponent/qt_googleMap/mainwindow.cpp
  src/qtComponent/qt_googleMap/roscommon.cpp
  src/qtComponent/qt_googleMap/china_shift.cpp
)
set(FORMS
  src/qtComponent/qt_googleMap/mainwindow.ui
)

include_directories(
  include
  src/qtComponent/qt_googleMap
  ${catkin_INCLUDE_DIRS}
  ${Qt5WebEngineWidgets_INCLUDE_DIRS}
)

add_executable(qt_map_node
  ${SOURCES} ${FORMS}
)
add_dependencies(qt_map_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(qt_map_node
  ${catkin_LIBRARIES} Qt5::Widgets ${Qt5WebEngineWidgets_LIBRARIES} ${OpenCV_LIBRARIES}
)
