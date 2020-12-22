cmake_minimum_required(VERSION 3.15)

project(cyber)

find_package(Boost REQUIRED COMPONENTS graph)
find_package(OpenCV REQUIRED COMPONENTS core dnn imgcodecs imgproc ml text)

set(Boost_USE_MULTITHREADED ON)

include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

set(${PROJECT_NAME}_headers
    include/cyber/parse.hpp
    include/cyber/solve.hpp
)

set(${PROJECT_NAME}_sources
    src/cyber/parse.cpp
    src/cyber/solve.cpp
)

if(WIN32)
    list(APPEND ${PROJECT_NAME}_headers
        include/cyber/capture.hpp
    )
    list(APPEND ${PROJECT_NAME}_sources
        src/cyber/capture.cpp
    )
endif(WIN32)

message("${${PROJECT_NAME}_headers}")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC include)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${${PROJECT_NAME}_headers}"
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
