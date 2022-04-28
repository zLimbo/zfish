message("\n==== zfish ====")
cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "/home/z/z/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_CXX_STANDARD 17)

project(zfish)

include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(cmakestudy SRC_LIST)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


message("\n== find libraries ==")
find_package(PkgConfig REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
message("= JSONCPP_FOUND: ${JSONCPP_FOUND}")
message("= JSONCPP_INCLUDE_DIR: ${JSONCPP_INCLUDE_DIRS}" )
message("= JSONCPP_LIBRARIES: ${JSONCPP_LIBRARIES}")
message("")

find_package(OpenSSL REQUIRED)
pkg_check_modules(OPENSSL openssl)
message("= OPENSSL_FOUND: ${OPENSSL_FOUND}")
message("= OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}" )
message("= OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")
message("")

find_package(GTest CONFIG REQUIRED)
pkg_check_modules(OPENSSL gtest)
message("= GTEST_FOUND: ${GTEST_FOUND}")
message("= GTEST_INCLUDE_DIR: ${GTEST_INCLUDE_DIR}" )
message("= GTEST_LIBRARIES: ${GTEST_LIBRARIE}")
message("")

foreach(SRC ${SRC_LIST})
    message("src: ${SRC}")
    get_filename_component(FILE_NAME ${SRC} NAME_WE)
    add_executable(${FILE_NAME} ${SRC})
    target_include_directories(
        ${FILE_NAME} PRIVATE 
        # ${JSONCPP_INCLUDE_DIRS}
        hlib
    )
    target_link_libraries(
        ${FILE_NAME} PRIVATE
        # ${GTEST_LIBRARIES}
        # ${JSONCPP_LIBRARIES}
        pthread
        jsoncpp_object jsoncpp_static JsonCpp::JsonCpp
        GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main
    )
endforeach(SRC)

