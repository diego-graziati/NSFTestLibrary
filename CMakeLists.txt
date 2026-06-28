cmake_minimum_required(VERSION 3.10)
project(NSFTestLibary LANGUAGES C CXX)
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
set(BASE_SOURCES
    src/nsftl_test_subscriber.c
    src/nsftl_test_init.c
    src/nsftl_test_execute.c
    src/nsftl_test_destroy.c
    src/nsftl_test_utils.c 
)


if(WIN32)
    set(TIME_SOURCES src/windows/nsftl_time.c)
    message(STATUS "Configurazione target: Windows")
elseif(APPLE)
    set(TIME_SOURCES src/apple/nsftl_time.c)
    message(STATUS "Configurazione target: macOS")
else()
    set(TIME_SOURCES src/posix/nsftl_time.c)
    message(STATUS "Configurazione target: Linux/POSIX")
endif()

add_library(nsftl STATIC
    ${BASE_SOURCES}
    ${TIME_SOURCES}
)

target_include_directories(nsftl PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
)

#Compiler sanitizers
## GCC
option(ENABLE_SANITIZERS "Adress and Undefined sanitizers Activation" ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_SANITIZERS)
    if(WIN32)
        message(STATUS "Sanitizers DISATTIVATI automaticamente su Windows (Non supportati da MinGW)")
    else()
        message(STATUS "Sanitizers are active (Address & Undefined)")
        set(SAN_FLAGS -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)

        target_compile_options(nsftl PUBLIC ${SAN_FLAGS})
        target_link_options(nsftl PUBLIC ${SAN_FLAGS})
    endif()
else()
    message(STATUS "Sanitizers NOT ACTIVE")
endif()

if(BUILD_TESTING)
    message(STATUS "Building Unit Tests and documentation...")

    #Library unit test creation
    add_executable(test_main
        "test/src/main.cpp"
        "test/src/Test.cpp"
        "test/src/tests/Test_init.cpp"
        "test/src/tests/Test_submit.cpp"
        "test/src/tests/Test_subscribe.cpp"
        "test/src/tests/Test_execute.cpp"
    )

    target_link_libraries(test_main PRIVATE nsftl)
    target_include_directories(test_main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test/inc")

    #Setting ctest
    add_test(NAME unit_tests COMMAND test_main)

    if(NOT WIN32 AND NOT APPLE)
        find_program(MEMORYCHECK_COMMAND valgrind)
        if(MEMORYCHECK_COMMAND)
            set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --track-origins=yes --error-exitcode=1")
        endif() 
    endif()
endif()

option(BUILD_DOCS "Generate Doxygen documentation" OFF)

if(BUILD_DOCS)
    #Code documentation creation
    find_package(Doxygen REQUIRED)

    if(DOXYGEN_FOUND)
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

        set(DOXYGEN_PROJECT_NAME "The Not So Fabolous Test Library - API")
        set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/api/)
        doxygen_add_docs(
            api_docs
            ${CMAKE_CURRENT_SOURCE_DIR}/inc
            ${PROJECT_SOURCE_DIR}/mainpage.dox
            COMMENT "Doxygen api documentation generation"
        )

        set(DOXYGEN_PROJECT_NAME "The Not So Fabolous Test Library - COMPLETE")
        set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/complete/)
        doxygen_add_docs(
            complete_docs
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/inc
            ${PROJECT_SOURCE_DIR}/mainpage.dox
            COMMENT "Doxygen complete documentation generation"
        )
    else()
        message(WARNING "Doxygen not found!")
    endif()
endif()

install(TARGETS nsftl
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY inc/ DESTINATION inc)