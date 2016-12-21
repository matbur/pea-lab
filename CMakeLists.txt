cmake_minimum_required(VERSION 3.3)
project(pea)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ATSP.cpp File.cpp Graph.cpp main.cpp Menu.h Permutation.h
        ATSP.h File.h Graph.h Menu.cpp Permutation.cpp Edge.cpp Edge.h EdgeList.cpp EdgeList.cpp Heap.cpp Heap.h)

add_executable(pro ${SOURCE_FILES})
