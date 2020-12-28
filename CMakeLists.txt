cmake_minimum_required(VERSION 3.15)

project(root)

option(BUILD_TESTING "Build the testing tree." ON)
option(RUN_TESTING "Run the testing tree." OFF)

option(CYBER_BUNDLE_TESSDATA "Bundle tessdata in build." OFF)

add_subdirectory(lib)
add_subdirectory(bin)

if(BUILD_TESTING)
    add_subdirectory(test)
endif(BUILD_TESTING)
