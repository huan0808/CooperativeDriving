cmake_minimum_required(VERSION 3.0.2)
project(perception C CXX)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")


find_package(catkin  REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)
find_package( Threads REQUIRED)


add_message_files(
   FILES
   frame.msg
   object_frame_station.msg
   object_frame.msg
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

add_executable(_perception src/perception_main.cpp src/perception_reader.cpp)
target_link_libraries (_perception ${catkin_LIBRARIES} Threads::Threads)

add_dependencies(_perception perception_generate_messages_cpp
#canbus_reader.cpp

)

#if(THREADS_HAVE_PTHREAD_ARG)
#    target_compile_options(_canbus PUBLIC ${catkin_LIBRARIES} "-pthread")
#endif()
#if(CMAKE_THREAD_LIBS_INIT)
#    target_link_libraries(_canbus ${catkin_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
#endif()


