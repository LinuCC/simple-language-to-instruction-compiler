cmake_minimum_required(VERSION 3.30.2)
project(slicc)

set(CXX "clang++")
# set(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror -pedantic -g")
# set(CMAKE_CXX_FLAGS "-O3 -Wall -W -pedantic")

# add_executable(slicc src/main.cpp)
add_subdirectory(src/)
