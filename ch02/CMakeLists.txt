cmake_minimum_required(VERSION 3.5)

project(ch02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(fig_2_03 fig_2_03.cpp)
target_link_libraries(fig_2_03 tbb)

add_executable(fig_2_04 fig_2_04.cpp)
target_link_libraries(fig_2_04 tbb)

add_executable(fig_2_05 fig_2_05.cpp)
target_link_libraries(fig_2_05 tbb)

add_executable(fig_2_06 fig_2_06.cpp)
target_link_libraries(fig_2_06 tbb)

add_executable(fig_2_07 fig_2_07.cpp)
target_link_libraries(fig_2_07 tbb)

add_executable(fig_2_08 fig_2_08.cpp)
target_link_libraries(fig_2_08 tbb)

add_executable(fig_2_10 fig_2_10.cpp)
target_link_libraries(fig_2_10 tbb)

