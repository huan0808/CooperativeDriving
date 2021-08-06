cmake_minimum_required(VERSION 3.0.2)
project(adrc_pid_control C CXX)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")


find_package(catkin  REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  canbus
  localization
)
find_package( Threads REQUIRED)


catkin_package(

   CATKIN_DEPENDS message_generation roscpp std_msgs message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(_AdrcPidControl src/control_main.cpp src/control_sender.cpp src/lat_controller.cpp src/math_utils.cpp src/lon_controller.cpp src/pid_controller.cpp src/ADRC.cpp src/FuzzyPID.cpp)
target_link_libraries(_AdrcPidControl ${catkin_LIBRARIES} Threads::Threads)


add_dependencies(_AdrcPidControl ${catkin_EXPORTED_TARGETS})
