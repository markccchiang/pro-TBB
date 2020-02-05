cmake_minimum_required(VERSION 3.5)

project(ch01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(fig_1_04 fig_1_04.cpp)
target_link_libraries(fig_1_04 tbb)

add_executable(fig_1_05 fig_1_05.cpp)
target_link_libraries(fig_1_05 tbb)