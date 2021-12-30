message("\n==== zfish ====")
cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "/home/z/z/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_CXX_STANDARD 17)

project(zfish)

include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(test SRC_LIST)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

foreach(SRC ${SRC_LIST})
    message("src: ${SRC}")
    get_filename_component(FILE_NAME ${SRC} NAME_WE)
    add_executable(${FILE_NAME} ${SRC})
    target_include_directories(${FILE_NAME} PRIVATE hlib)
    target_link_libraries(${FILE_NAME} gtest pthread)
endforeach(SRC)

