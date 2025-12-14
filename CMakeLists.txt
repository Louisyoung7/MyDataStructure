cmake_minimum_required(VERSION 3.14)
project(MyDataStructure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(slList tests/dataStructures/single_linked_list_test.cpp)

target_include_directories(slList PRIVATE ${PROJECT_SOURCE_DIR}/src)

