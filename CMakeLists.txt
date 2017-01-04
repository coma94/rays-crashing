cmake_minimum_required(VERSION 2.8.9)
project(rays-crashing)
set (CMAKE_CXX_STANDARD 11)
 
#Bring the headers, such as Student.h into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")


FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

 
add_executable(rays-crashing ${SOURCES})

target_link_libraries(rays-crashing X11)
target_link_libraries(rays-crashing pthread)
