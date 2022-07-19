cmake_minimum_required (VERSION 2.6)  

project(glstu)  

find_package(OpenGL REQUIRED)  
include_directories(${OPENGL_INCLUDE_DIR})  

find_package(GLUT REQUIRED)  
include_directories(${GLUT_INCLUDE_DIR})  

set(CMAKE_CXX_FLAGS "-g -Wall")  

link_libraries(${GLUT_LIBRARY} ${OPENGL_LIBRARY})

add_executable(draw draw.cpp)
add_executable(simple simple.c)
add_executable(simple2 simple2.c)
add_executable(robot_move robot_move.cpp)
add_executable(squareRotate squareRotate.cc)