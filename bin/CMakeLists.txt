cmake_minimum_required(VERSION 3.15)

project(cyber_breach)

find_package(Boost REQUIRED COMPONENTS graph)
find_package(OpenCV REQUIRED COMPONENTS core dnn imgcodecs imgproc ml text)

set(Boost_USE_MULTITHREADED ON)

include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

set(${PROJECT_NAME}_sources
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OpenCV_LIBS} cyber)

if(CYBER_BUNDLE_TESSDATA)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/modules/tessdata_best/script/Latin.traineddata"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/tessdata/Latin.traineddata"
    )
endif(CYBER_BUNDLE_TESSDATA)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
