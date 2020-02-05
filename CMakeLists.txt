cmake_minimum_required(VERSION 3.5)

#FIND_PACKAGE(tbb REQUIRED)
#
#if (tbb_FOUND)
#    message(STATUS "Found tbb ${tbb_LIBRARIES}")
#endif()

#INCLUDE_DIRECTORIES(/usr/local/Cellar/tbb/2019_U9/include)
#LINK_DIRECTORIES(/usr/local/Cellar/tbb/2019_U9/lib)

INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

add_subdirectory(ch01)
