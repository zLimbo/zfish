cmake_minimum_required(VERSION 3.15)
project(faceswap)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(faceswap main.cpp convexHull.cpp)
target_link_libraries(faceswap ${OpenCV_LIBS})