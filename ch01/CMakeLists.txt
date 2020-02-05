cmake_minimum_required(VERSION 3.5)

project(ch01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(fig_1_04 fig_1_04.cpp)
target_link_libraries(fig_1_04 tbb)

add_executable(fig_1_05 fig_1_05.cpp)
target_link_libraries(fig_1_05 tbb)

add_executable(fig_1_07 fig_1_07.cpp)
target_link_libraries(fig_1_07 tbb)

add_executable(fig_1_10 fig_1_10.cpp)
target_link_libraries(fig_1_10 tbb)

add_executable(fig_1_11 fig_1_11.cpp)
target_link_libraries(fig_1_11 tbb)

add_executable(fig_1_12 fig_1_12.cpp)
target_link_libraries(fig_1_12 tbb)
