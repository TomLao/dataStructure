# cmake_minimum_required(VERSION <specify CMake version here>)
project(dataStructure)

set(CMAKE_CXX_STANDARD 11)

add_executable(dataStructure graph/main.cpp tree/test.cpp search/test2.cpp Experiment4/header/BinarySortingTree.h Experiment4/BinarySortingTree_main.cpp Experiment4/Sorting_main.cpp)
