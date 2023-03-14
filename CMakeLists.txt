cmake_minimum_required(VERSION 3.11.0)

project(spp-alloctor VERSION 0.1.0)

configure_file(CMakeLists.txt.in download/CMakeLists.txt)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -g3 -fno-omit-frame-pointer -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 23)

IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
ENDIF(CMAKE_BUILD_TYPE MATCHES RELEASE)

add_library(spp-alloctor ${SOURCE_FILES})

include_directories(spp-alloctor include)