cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp hashTable.cpp hashTable.h UnorderedArray.h UnorderedArray.cpp orderedArray.cpp orderedArray.h BSTree.h BSTree.cpp AVLtree.h AVLtree.cpp)

