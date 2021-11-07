cmake_minimum_required(VERSION 3.29)

project(cyber)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS graph)
find_package(OpenCV REQUIRED COMPONENTS core dnn imgcodecs imgproc ml text)

find_path(TERMCOLOR_INCLUDE_DIRS "termcolor/termcolor.hpp")

set(Boost_USE_MULTITHREADED ON)

include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

set(${PROJECT_NAME}_headers
    include/cyber/common.hpp
    include/cyber/detect.hpp
    include/cyber/init.hpp
    include/cyber/layout.hpp
    include/cyber/parse.hpp
    include/cyber/solve.hpp
    include/cyber/term.hpp
)

set(${PROJECT_NAME}_sources
    src/cyber/detect.cpp
    src/cyber/init.cpp
    src/cyber/parse.cpp
    src/cyber/solve.cpp
)

if(WIN32)
    list(APPEND ${PROJECT_NAME}_headers
        include/cyber/capture.hpp
        include/cyber/clicker.hpp
        include/cyber/mouse.hpp
    )
    list(APPEND ${PROJECT_NAME}_sources
        src/cyber/capture.cpp
        src/cyber/clicker.cpp
        src/cyber/mouse.cpp
    )
endif(WIN32)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC ${TERMCOLOR_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC ${OpenCV_LIBS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${${PROJECT_NAME}_headers}"
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
