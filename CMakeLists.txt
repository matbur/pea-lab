cmake_minimum_required(VERSION 3.3)
project(pea-lab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ATSP.cpp FileSupport.cpp Graph.cpp main.cpp Menu.h Permutation.h ATSP.h FileSupport.h Graph.h Menu.cpp Permutation.cpp)

add_executable(pea ${SOURCE_FILES})
