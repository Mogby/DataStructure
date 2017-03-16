cmake_minimum_required(VERSION 3.6)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

link_directories(lib)

set(SOURCE_FILES src/main.cpp src/data_structure.cpp src/treap.cpp src/tests.cpp src/split_predicate.cpp src/split_predicate.hpp)
add_executable(DataStructure ${SOURCE_FILES})

target_link_libraries(DataStructure libgtest_main.a libgtest.a pthread)