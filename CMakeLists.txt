cmake_minimum_required(VERSION 3.15)

project(root)

include(CTest)

add_subdirectory(lib)
add_subdirectory(bin)

if(BUILD_TESTING)
    add_subdirectory(test)
endif(BUILD_TESTING)
