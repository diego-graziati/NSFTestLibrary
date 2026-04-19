cmake_minimum_required(VERSION 3.10)
project(MyTest LANGUAGES C CXX)
include(CTest)

#Setting gcc sanitizers for both C and CPP
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fanalyzer)
endif()

find_program(CPPCHECK_PATH cppcheck)
if(CPPCHECK_PATH)
    set(CMAKE_C_CPPCHECK ${CPPCHECK_PATH} --enable=all --suppress=missingInclude)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK_PATH} --enable=all --suppress=missingInclude)
endif()

#Library creation
add_library(mytest STATIC
    src/test_subscriber.c
    src/test_init.c
    src/test_execute.c
    src/test_destroy.c
    src/test_utils.c
)

target_include_directories(mytest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#Compiler sanitizers
## GCC
option(ENABLE_SANITIZERS "Adress and Undefined sanitizers Activation" ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_SANITIZERS)
    message(STATUS "Sanitizers are active (Address & Undefined)")
    set(SAN_FLAGS -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)

    target_compile_options(mytest PUBLIC ${SAN_FLAGS})
    target_link_options(mytest PUBLIC ${SAN_FLAGS})
else()
    message(STATUS "Sanitizers NOT ACTIVE")
endif()

#Library unit test creation
add_executable(test_main
    "test/src/main.cpp"
    "test/src/Test.cpp"
    "test/src/tests/Test_init.cpp"
    "test/src/tests/Test_submit.cpp"
    "test/src/tests/Test_subscribe.cpp"
    "test/src/tests/Test_execute.cpp"
)

target_link_libraries(test_main PRIVATE mytest)
target_include_directories(test_main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test/inc")

#Setting ctest
enable_testing()
add_test(NAME unit_tests COMMAND test_main)

find_program(MEMORYCHECK_COMMAND valgrind)
if(MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --track-origins=yes --error-exitcode=1")
endif()

#Code documentation creation
find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYGEN_PROJECT_NAME "MyTest")
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX YES)
    set(DOXYGEN_LATEX_OUTPUT "latex")
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_SOURCE_BROWSER YES)
    set(DOXYGEN_RECURSIVE YES)

    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_CALLER_GRAPH YES)

    set(DOXYGEN_DIRECTORY_GRAPH YES)
    set(DOXYGEN_INCLUDE_GRAPH YES)
    set(DOXYGEN_INCLUDE_BY_GRAPH YES)

    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
    set(DOXYGEN_INTERACTIVE_SVG YES)

    doxygen_add_docs(
        docs
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        COMMENT "Doxygen documentation generation"
    )
else()
    message(WARNING "Doxygen not found!")
endif()