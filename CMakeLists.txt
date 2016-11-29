cmake_minimum_required(VERSION 2.8.9)
project(rays-crashing)
 
#Bring the headers, such as Student.h into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(rays-crashing ${SOURCES})

target_link_libraries(rays-crashing X11)
target_link_libraries(rays-crashing pthread)