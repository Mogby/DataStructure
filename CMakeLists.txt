cmake_minimum_required(VERSION 3.6)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

link_directories(lib)

set(SOURCE_FILES src/data_structure.cpp src/treap.cpp src/split_predicate.cpp src/split_predicate.hpp)
set(TEST_FILES src/main.cpp src/tests.cpp)
set(TASK_FILES src/task.cpp)

add_library(data_structure ${SOURCE_FILES})
#add_executable(tests ${TEST_FILES})
add_executable(task ${TASK_FILES})

#target_link_libraries(tests data_structure libgtest_main.a libgtest.a pthread)
target_link_libraries(task data_structure)
