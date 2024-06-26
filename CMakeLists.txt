cmake_minimum_required(VERSION 3.22)
project(large_prime_numbers LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_EXTENSIONS ON) # Same as gnu++2a (ON) vs c++2a (OFF): https://cmake.org/cmake/help/latest/prop_tgt/CXX_EXTENSIONS.html
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Source dir ${PROJECT_SOURCE_DIR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti ${COMPILER_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 ${CMAKE_CXX_FLAGS_ADD}")
    set(CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3 ${CMAKE_CXX_FLAGS_ADD}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_FLAGS} ${CMAKE_C_FLAGS_ADD}")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 ${CMAKE_CXX_FLAGS_ADD}")
    set(C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3 ${CMAKE_CXX_FLAGS_ADD}")
endif ()

include(cmake/glob_sources.cmake)

add_subdirectory(contrib)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)
