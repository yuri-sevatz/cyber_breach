cmake_minimum_required(VERSION 3.15)

project(cyber_test)

find_package(Boost REQUIRED COMPONENTS graph)
find_package(OpenCV REQUIRED COMPONENTS core dnn imgcodecs imgproc ml text)

option(RUN_TESTING "Run the testing tree." OFF)

set(Boost_USE_MULTITHREADED ON)

include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

set(${PROJECT_NAME}_sources
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OpenCV_LIBS} cyber)

FILE(GLOB ${PROJECT_NAME}_example_images
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "examples/*.png"
)

foreach(example_image ${${PROJECT_NAME}_example_images})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/${example_image}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${example_image}"
    )
endforeach(example_image)

if (RUN_TESTING)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${PROJECT_NAME}
    )
endif(RUN_TESTING)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
