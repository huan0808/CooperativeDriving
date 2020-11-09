cmake_minimum_required(VERSION 3.0.2)
project(localization C CXX)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")


find_package(catkin  REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)
find_package( Threads REQUIRED)


add_message_files(
   FILES
   gps.msg
)
generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(

   CATKIN_DEPENDS message_generation roscpp std_msgs message_runtime
)




include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(_localization src/localization_main.cpp src/gps_read.cpp)
target_link_libraries (_localization ${catkin_LIBRARIES} Threads::Threads)



#if(THREADS_HAVE_PTHREAD_ARG)
#    target_compile_options(_localization PUBLIC ${catkin_LIBRARIES} "-pthread")
#endif()
#if(CMAKE_THREAD_LIBS_INIT)
#    target_link_libraries(_localization ${catkin_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
#endif()
