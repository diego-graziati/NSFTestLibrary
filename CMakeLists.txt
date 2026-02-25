cmake_minimum_required(VERSION 3.10)
project(MyTest LANGUAGES C CXX)

add_library(mytest STATIC 
    src/test_subscriber.c
)

target_include_directories(mytest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#Test
add_executable(test_main
    "test/src/main.cpp"
    "test/src/Test.cpp"
)

target_link_libraries(test_main mytest)
target_include_directories(test_main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test/inc")