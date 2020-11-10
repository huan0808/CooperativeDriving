cmake_minimum_required(VERSION 3.0.2)
project(control C CXX)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")


find_package(catkin  REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  canbus
  localization
)
find_package( Threads REQUIRED)


#add_message_files(
#   FILES
#   frame.msg
#)
#generate_messages(
#   DEPENDENCIES
#   std_msgs
#   canbus
#   localization
#)


catkin_package(

   CATKIN_DEPENDS message_generation roscpp std_msgs message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(_control src/control_main.cpp src/control_sender.cpp)
target_link_libraries(_control ${catkin_LIBRARIES} Threads::Threads)



#if(THREADS_HAVE_PTHREAD_ARG)
#    target_compile_options(_canbus PUBLIC ${catkin_LIBRARIES} "-pthread")
#endif()
#if(CMAKE_THREAD_LIBS_INIT)
#    target_link_libraries(_canbus ${catkin_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
#endif()


add_dependencies(_control ${catkin_EXPORTED_TARGETS})