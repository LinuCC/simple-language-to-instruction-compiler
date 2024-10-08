cmake_minimum_required(VERSION 3.30.2)
project(slicc)

set(CXX "clang++")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-Wc++11-extensions -Wall -W  -g")
set(CMAKE_CXX_FLAGS "-Wc++11-extensions -O3 -Wall -W -pedantic")

# add_executable(slicc src/main.cpp)
add_subdirectory(src/)
