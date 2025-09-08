cmake_minimum_required(VERSION 3.15)
project(Euclid LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4 /EHsc)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")
endif()

add_library(Euclid INTERFACE)

target_include_directories(Euclid INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

option(BUILD_EUCLID_TESTS "Build Euclid tests" ON)

if(${BUILD_EUCLID_TESTS})
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "Disable GTest installation" FORCE)

    add_subdirectory(third/googletest)
    enable_testing()

    file(GLOB_RECURSE test_sources "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

    foreach(test_source ${test_sources})
        get_filename_component(test_name ${test_source} NAME_WE)
        if(TARGET ${test_name})
            continue()
        endif()

        add_executable(
            ${test_name}
            ${test_source}
        )

        add_test(
            NAME ${test_name}
            COMMAND ${test_name}
        )

        target_link_libraries(
            ${test_name}
            PRIVATE
            GTest::gtest_main
            Euclid
        )
        message(STATUS "Added test: ${test_name}")
        
    endforeach()
endif()