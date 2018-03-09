cmake_minimum_required(VERSION 3.3)

project(robust_iterator_test)

include(gtest.cmake)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(robust_iterator_test ${PROJECT_SOURCE_DIR}/test/robust_iterator_test.cpp)

target_link_libraries(robust_iterator_test gtest pthread)
